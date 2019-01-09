#pragma once
#include <memory>
#include <string>
#include "FFmpegReader.h"

class FFmpegDemuter
{
public:
    FFmpegDemuter();
    ~FFmpegDemuter();

public:
    int CreateMediaStreamSource(const std::string& strFilePath);

public:
    std::shared_ptr<FFmpegReader> m_VideoReader;
    std::shared_ptr<FFmpegReader> m_AudioReader;

};

