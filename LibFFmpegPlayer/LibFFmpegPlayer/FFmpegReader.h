#pragma once
#include "FFmpegSampleProvider.h"
#include <string>
extern "C"
{
    #include "libavformat/avformat.h"
};

class FFmpegSampleProvider;

class FFmpegReader
{
public:
    FFmpegReader(int streamIndex, const std::string& strFilePath);
    ~FFmpegReader();

protected:
    int ReadPacket();

public:
    std::string           m_strFilePath;
    AVFormatContext*      m_pAvFormatCtx;
    FFmpegSampleProvider*  m_SampleProvider;
    int                   m_streamIndex;
};

