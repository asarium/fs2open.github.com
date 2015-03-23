#pragma once

#include "cutscene/ffmpeg/internal.h"
#include "cutscene/ffmpeg/FFMPEGDecoder.h"

namespace cutscene
{
    namespace ffmpeg
    {
        class AudioDecoder : public FFMPEGStreamDecoder<AudioFrame>
        {
        private:
            SwrContext* m_swrCtx;

            uint8_t **m_outData;
            int m_outLinesize;

            int m_maxOutNumSamples;
            int m_outNumSamples;

        public:
            AudioDecoder(DecoderStatus* status, std::function<void(std::shared_ptr<AudioFrame>)> push);
            virtual ~AudioDecoder();

            virtual void decodePacket(AVPacket* packet, AVFrame* preallocated) override;
        };
    }
}