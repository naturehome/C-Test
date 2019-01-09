#pragma once
class FFmpegSynchronizer;
class FFmpegFrameProvider;

class FFmpegAudioSpeaker
{
public:
    FFmpegAudioSpeaker(FFmpegFrameProvider& FrameProvider, FFmpegSynchronizer& Synchronizer);
    ~FFmpegAudioSpeaker();


private:
    FFmpegFrameProvider& m_FrameProvider;
    FFmpegSynchronizer&  m_Synchronizer; 
};

