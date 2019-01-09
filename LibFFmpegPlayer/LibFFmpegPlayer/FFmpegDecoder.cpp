#include "FFmpegDecoder.h"


FFmpegDecoder::FFmpegDecoder(FFmpegSampleProvider& SampleProvider) :m_SampleProvider(SampleProvider)
{

}


FFmpegDecoder::~FFmpegDecoder()
{

}


int FFmpegDecoder::startDecode()
{
    while (true)
    {
        if (m_FrameProvider.m_frameQueue.empty())
        {

        }
    }
}