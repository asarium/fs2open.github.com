#pragma once

#include "cutscene/ffmpeg/internal.h"
#include "cutscene/ffmpeg/FFMPEGDecoder.h"

namespace cutscene
{
    namespace ffmpeg
    {
        class VideoDecoder : public FFMPEGStreamDecoder<VideoFrame>
        {
        private:
            int m_frameId;
            SwsContext* m_swsCtx;

            void convertAndPushPicture(const AVFrame* frame);

        public:
            VideoDecoder(DecoderStatus* status, std::function<void(std::shared_ptr<VideoFrame>)> push);
            virtual ~VideoDecoder();

            virtual void decodePacket(const AVPacket* packet, AVFrame* preallocated) override;

            virtual void finishDecoding(const AVPacket* nullPacket, AVFrame* preallocated) override;
        };
    }
}