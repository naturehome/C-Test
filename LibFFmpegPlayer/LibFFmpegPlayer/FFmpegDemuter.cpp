#include "FFmpegDemuter.h"

extern "C"
{
    #include "libavformat/avformat.h"
};



FFmpegDemuter::FFmpegDemuter()
{

}


FFmpegDemuter::~FFmpegDemuter()
{

}


int FFmpegDemuter::CreateMediaStreamSource(const std::string& strFilePath)
{
    AVFormatContext *avFormatCtx = avformat_alloc_context();
    if (avFormatCtx == nullptr)
    {
        return -1;
    }

    if (avformat_open_input(&avFormatCtx, strFilePath.c_str(), NULL, NULL) < 0)
    {
        return -2;
    }

    if (avformat_find_stream_info(avFormatCtx, NULL) < 0)
    {
        avformat_close_input(&avFormatCtx);
        return -3;
    }

    AVCodec* avAudioCodec = nullptr;
    int audioStreamIndex = av_find_best_stream(avFormatCtx, AVMEDIA_TYPE_AUDIO, -1, -1, &avAudioCodec, 0);
    if (audioStreamIndex != AVERROR_STREAM_NOT_FOUND && avAudioCodec)
    {
        m_AudioReader.reset(new FFmpegReader(audioStreamIndex, strFilePath));
    }

    AVCodec* avVideoCodec = nullptr;
    int videoStreamIndex = av_find_best_stream(avFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &avVideoCodec, 0);
    if (videoStreamIndex != AVERROR_STREAM_NOT_FOUND && avVideoCodec)
    {
        m_VideoReader.reset(new FFmpegReader(audioStreamIndex, strFilePath));
    }

    avformat_close_input(&avFormatCtx);

    return 0;
}
