
#include "cutscene/Decoder.h"

namespace
{
    const size_t DEFAULT_MAX_QUEUE_SIZE = 10;

    const Uint32 DEFAULT_WAIT_TIMEOUT = 100;
}

namespace cutscene
{
    Decoder::Decoder() : m_waitTimeout(DEFAULT_WAIT_TIMEOUT), m_maxQueueSize(DEFAULT_MAX_QUEUE_SIZE)
    {
        m_queueLock = SDL_CreateMutex();
        m_queueAvailableSignal = SDL_CreateCond();
    }

    Decoder::~Decoder()
    {
        if (m_queueAvailableSignal)
        {
            SDL_DestroyCond(m_queueAvailableSignal);
        }

        if (m_queueLock)
        {
            SDL_DestroyMutex(m_queueLock);
        }
    }

    bool Decoder::audioDataAvailable()
    {
        return !m_audioQueue.empty();
    }

    std::shared_ptr<AudioData> Decoder::popAudioData()
    {
        lockQueue();

        auto data = m_audioQueue.front();
        m_audioQueue.pop();

        // The size of the queue decreased, notify waiting threads
        SDL_CondSignal(m_queueAvailableSignal);

        unlockQueue();

        return data;
    }


    bool Decoder::videoFrameAvailable()
    {
        return !m_videoQueue.empty();
    }

    std::shared_ptr<VideoFrame> Decoder::popVideoFrame()
    {
        lockQueue();

        auto data = m_videoQueue.front();
        m_videoQueue.pop();

        // The size of the queue decreased, notify waiting threads
        sendQueueSignal(false);

        unlockQueue();

        return data;
    }

    void Decoder::sendQueueSignal(bool lock)
    {
        if (lock)
        {
            lockQueue();
        }

        SDL_CondSignal(m_queueAvailableSignal);

        if (lock)
        {
            unlockQueue();
        }
    }

    void Decoder::lockQueue()
    {
        SDL_LockMutex(m_queueLock);
    }
    void Decoder::unlockQueue()
    {
        SDL_UnlockMutex(m_queueLock);
    }

    bool Decoder::canPushAudioData()
    {
        return m_audioQueue.size() < m_maxQueueSize;
    }
    void Decoder::pushAudioData(const std::shared_ptr<AudioData>& data)
    {
        Assertion(data, "Invalid audio data passed!");

        m_audioQueue.push(data);
    }

    bool Decoder::canPushVideoData()
    {
        return m_videoQueue.size() < m_maxQueueSize;
    }
    void Decoder::pushFrameData(const std::shared_ptr<VideoFrame>& frame)
    {
        Assertion(frame, "Invalid video data passed!");

        m_videoQueue.push(frame);
    }

    void Decoder::waitForQueueSignal()
    {
        while (!(canPushVideoData() || (hasAudio() && canPushAudioData())) && m_decoding)
        {
            if (SDL_CondWaitTimeout(m_queueAvailableSignal, m_queueLock, m_waitTimeout) == 0)
            {
                // Signal was signaled
                return;
            }
        }
    }
}
