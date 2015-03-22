
#pragma once

#include <memory>

#include "globalincs/pstypes.h"

#include <boost/thread/sync_bounded_queue.hpp>

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
    typedef std::shared_ptr<VideoFrame> VideoFramePtr;

    struct MovieProperties
    {
        FrameSize size;

        float fps;
    };

    struct AudioFrame
    {
        SCP_vector<short> audioData;

        int channels;

        long rate;
    };
    typedef std::shared_ptr<AudioFrame> AudioFramePtr;

    class Decoder
    {
    private:
        std::shared_ptr<boost::sync_bounded_queue<VideoFramePtr>> m_videoQueue;
        std::shared_ptr<boost::sync_bounded_queue<AudioFramePtr>> m_audioQueue;

        bool m_decoding = true;

        Decoder(const Decoder&) = delete;
        Decoder& operator=(const Decoder&) = delete;

    public:
        Decoder();
        virtual ~Decoder();

        virtual bool initialize(const SCP_string& fileName) = 0;

        virtual MovieProperties getProperties() = 0;

        virtual void startDecoding() = 0;

        virtual bool hasAudio() = 0;

        virtual void close() = 0;

        size_t getAudioQueueSize() { return m_audioQueue->size(); }
        bool isAudioFrameAvailable() { return !m_audioQueue->empty(); }
        bool tryPopAudioData(AudioFramePtr&);

        size_t getVideoQueueSize() { return m_videoQueue->size(); }
        bool isVideoFrameAvailable() { return !m_videoQueue->empty(); }
        bool tryPopVideoFrame(VideoFramePtr&);
        
        void stopDecoder();
        bool isDecoding() { return m_decoding; }

    protected:
        void initializeQueues(size_t queueSize);

        bool canPushAudioData();
        void pushAudioData(const AudioFramePtr& data);
        
        bool canPushVideoData();
        void pushFrameData(const VideoFramePtr& frame);
    };
}
