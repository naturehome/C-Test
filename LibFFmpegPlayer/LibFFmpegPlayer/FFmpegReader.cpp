#include "FFmpegReader.h"


FFmpegReader::FFmpegReader(int streamIndex, const std::string& strFilePath) :
                            m_streamIndex(streamIndex), m_strFilePath(strFilePath), m_SampleProvider(nullptr)
{

}


FFmpegReader::~FFmpegReader()
{

}

int FFmpegReader::ReadPacket()
{
    int ret;
    AVPacket avPacket;
    av_init_packet(&avPacket);
    avPacket.data = NULL;
    avPacket.size = 0;

    ret = av_read_frame(m_pAvFormatCtx, &avPacket);
    if (ret < 0)
    {
        return ret;
    }

    // Push the packet to the appropriate
    if (avPacket.stream_index == m_streamIndex && m_SampleProvider != nullptr)
    {
        m_SampleProvider->QueuePacket(avPacket);
    }
    else
    {
        av_packet_unref(&avPacket);
    }

    return ret;
}