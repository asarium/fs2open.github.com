
#include "cutscene/Decoder.h"


namespace cutscene
{
    Decoder::Decoder()
    {
    }

    Decoder::~Decoder()
    {
    }

    bool Decoder::tryPopAudioData(AudioFramePtr& out)
    {
        auto res = m_audioQueue->try_pull_front(out);
        return res == boost::queue_op_status::success;
    }

    bool Decoder::tryPopVideoFrame(VideoFramePtr& out)
    {
        auto res = m_videoQueue->try_pull_front(out);
        return res == boost::queue_op_status::success;
    }

    void Decoder::initializeQueues(size_t queueSize)
    {
        m_videoQueue = std::make_shared<boost::sync_bounded_queue<VideoFramePtr>>(queueSize);
        m_audioQueue = std::make_shared<boost::sync_bounded_queue<AudioFramePtr>>(queueSize);
    }

    void Decoder::stopDecoder()
    {
        m_decoding = false;

        m_videoQueue->close();
        m_audioQueue->close();
    }

    bool Decoder::canPushAudioData()
    {
        return !m_audioQueue->full();
    }
    void Decoder::pushAudioData(const AudioFramePtr& data)
    {
        Assertion(data, "Invalid audio data passed!");
        
        try
        {
            m_audioQueue->push_back(data);
        }
        catch (boost::sync_queue_is_closed&)
        {
            // Ignore
        }
    }

    bool Decoder::canPushVideoData()
    {
        return !m_videoQueue->full();
    }
    void Decoder::pushFrameData(const VideoFramePtr& frame)
    {
        Assertion(frame, "Invalid video data passed!");

        try
        {
            m_videoQueue->push_back(frame);
        }
        catch (boost::sync_queue_is_closed&)
        {
            // Ignore
        }
    }
}
