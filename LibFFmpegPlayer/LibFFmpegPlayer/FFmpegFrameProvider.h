#pragma once
#include <vector>
extern "C"
{
#include <libavformat/avformat.h>
}


class FFmpegFrameProvider
{
    friend class FFmpegDecoder;
public:
    FFmpegFrameProvider();
    virtual ~FFmpegFrameProvider();

public:

    std::vector<AVFrame> m_frameQueue;
};

