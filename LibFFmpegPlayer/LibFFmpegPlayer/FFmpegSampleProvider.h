#pragma once
#include <vector>
extern "C"
{
#include <libavformat/avformat.h>
}

class FFmpegReader;
class FFmpegSampleProvider
{
public:
    FFmpegSampleProvider(FFmpegReader* ffmpegReader);
    virtual ~FFmpegSampleProvider();

public:
    AVPacket GetNextSample();
    void QueuePacket(AVPacket packet);
    AVPacket PopPacket();
private:
    FFmpegReader* m_ffmpegReader;
    int m_streamIndex;
    std::vector<AVPacket> m_packetQueue;
};

