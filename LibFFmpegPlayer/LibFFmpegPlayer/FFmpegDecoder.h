#pragma once

#include "FFmpegFrameProvider.h"
class FFmpegSampleProvider;
class FFmpegFrameProvider;

class FFmpegDecoder
{
public:
    FFmpegDecoder(FFmpegSampleProvider& SampleProvider);
    virtual ~FFmpegDecoder();

    int startDecode();
public:
    FFmpegSampleProvider& m_SampleProvider;
    FFmpegFrameProvider m_FrameProvider;

};

