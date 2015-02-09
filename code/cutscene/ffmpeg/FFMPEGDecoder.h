
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

            std::unique_ptr<InputStream> openStream(const SCP_string& name);

            std::unique_ptr<DecoderStatus> initializeStatus(std::unique_ptr<InputStream>& stream);

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
