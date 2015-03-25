
#pragma once

#include "cutscene/Decoder.h"

namespace cutscene
{
    namespace ffmpeg
    {
        struct InputStream;

        struct DecoderStatus;

        class FFMPEGDecoder : public Decoder
        {
        private:
            std::unique_ptr<InputStream> m_input;

            std::unique_ptr<DecoderStatus> m_status;

        public:
            FFMPEGDecoder();
            virtual ~FFMPEGDecoder();

            virtual bool initialize(const SCP_string& fileName);

            virtual MovieProperties getProperties();

            virtual void startDecoding();

            virtual bool hasAudio();

            virtual void close();
        };
    }
}
