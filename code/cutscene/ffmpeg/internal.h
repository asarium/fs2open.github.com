
#pragma once

#include <functional>

// Disable a few warnings that happen in the ffmpeg headers
// TODO: Also do this for other compilers
#pragma warning(push)
#pragma warning(disable: 4244) // conversion from 'int' to '*'

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>

#include <libavutil/imgutils.h>
#include <libavutil/error.h>
#include <libavutil/opt.h>
}

#pragma warning(pop)

#include "cutscene/Decoder.h"

namespace cutscene
{
    namespace ffmpeg
    {
        struct DecoderStatus
        {
            int videoStreamIndex = -1;
            AVStream* videoStream = nullptr;
            AVCodecContext* videoCodecCtx = nullptr;
            AVCodec* videoCodec = nullptr;

            int audioStreamIndex = -1;
            AVStream* audioStream = nullptr;
            AVCodecContext* audioCodecCtx = nullptr;
            AVCodec* audioCodec = nullptr;
        };

        template<typename Frame>
        class FFMPEGStreamDecoder
        {
        protected:
            typedef Frame frame_type;

            std::function<void(std::shared_ptr<frame_type>)> m_pushFunction;
            DecoderStatus* m_status;

        public:
            FFMPEGStreamDecoder(DecoderStatus* status, std::function<void(std::shared_ptr<frame_type>)> push)
                : m_pushFunction(push), m_status(status) {}
            virtual ~FFMPEGStreamDecoder() {}

            virtual void decodePacket(const AVPacket* packet, AVFrame* preallocated) = 0;

            virtual void finishDecoding(const AVPacket* nullPacket, AVFrame* preallocated) = 0;
        };
    }
}
