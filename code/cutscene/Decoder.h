
#pragma once

#include <memory>

#include "globalincs/pstypes.h"

#include "SDL_thread.h"
#include "SDL_mutex.h"

namespace cutscene
{
    struct FrameSize
    {
        int width;
        int height;
        int stride;
    };

    class VideoFrame
    {
    protected:
        VideoFrame() {}

    public:
        virtual ~VideoFrame() {}

        double frameTime;
        int id;

        FrameSize ySize;
        FrameSize uvSize;

        struct DataPointers
        {
            ubyte* y;
            ubyte* u;
            ubyte* v;
        };

        virtual DataPointers getDataPointers() = 0;
    };

    struct MovieProperties
    {
        FrameSize size;

        float fps;
    };

    struct AudioData
    {
        SCP_vector<short> audioData;

        int channels;

        long rate;
    };

    class Decoder
    {
    private:
        SDL_mutex* m_queueLock;
        SDL_cond* m_queueAvailableSignal;

        SCP_queue<std::shared_ptr<VideoFrame>> m_videoQueue;
        SCP_queue<std::shared_ptr<AudioData>> m_audioQueue;

        bool m_decoding = true;

        Decoder(const Decoder&) = delete;

    public:
        Decoder();
        virtual ~Decoder();

        virtual bool initialize(const SCP_string& fileName) = 0;

        virtual MovieProperties getProperties() = 0;

        virtual void startDecoding() = 0;

        virtual bool hasAudio() = 0;

        virtual void close() = 0;

        bool audioDataAvailable();
        size_t getAudioQueueSize() { return m_audioQueue.size(); }
        std::shared_ptr<AudioData> popAudioData();

        bool videoFrameAvailable();
        size_t getVideoQueueSize() { return m_videoQueue.size(); }
        std::shared_ptr<VideoFrame> popVideoFrame();

        void sendQueueSignal(bool lock = true);

        void stopDecoder() { m_decoding = false; }
        bool isDecoding() { return m_decoding; }

    protected:
        uint m_waitTimeout;
        uint m_maxQueueSize;

        void lockQueue();

        bool canPushAudioData();
        void pushAudioData(const std::shared_ptr<AudioData>& data);
        
        bool canPushVideoData();
        void pushFrameData(const std::shared_ptr<VideoFrame>& frame);

        void waitForQueueSignal();

        void unlockQueue();
    };
}
