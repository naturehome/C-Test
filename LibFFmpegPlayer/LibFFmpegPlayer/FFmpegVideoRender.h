#pragma once
class FFmpegSynchronizer;
class FFmpegFrameProvider;

class FFmpegVideoRender
{
public:
    FFmpegVideoRender(FFmpegFrameProvider& FrameProvider, FFmpegSynchronizer& Synchronizer);
    ~FFmpegVideoRender();

private:
    FFmpegFrameProvider& m_FrameProvider;
    FFmpegSynchronizer&  m_Synchronizer;
};

