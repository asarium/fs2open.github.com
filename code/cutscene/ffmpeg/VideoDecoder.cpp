
#include "cutscene/ffmpeg/VideoDecoder.h"

namespace
{
    SwsContext* getSWSContext(int width, int height, AVPixelFormat fmt)
    {
        return sws_getContext(width, height, fmt, width, height, PIX_FMT_YUV420P,
            SWS_BILINEAR, nullptr, nullptr, nullptr);
    }

    float getFrameTime(int64_t pts, AVRational time_base)
    {
        return static_cast<float>(pts * av_q2d(time_base));
    }
}

namespace cutscene
{
    namespace ffmpeg
    {
        VideoDecoder::VideoDecoder(DecoderStatus* status, std::function<void(std::shared_ptr<VideoFrame>)> push) : FFMPEGStreamDecoder(status, push),
            m_frameId(0)
        {
            m_swsCtx = getSWSContext(m_status->videoCodecCtx->width, m_status->videoCodecCtx->height, m_status->videoCodecCtx->pix_fmt);
        }

        VideoDecoder::~VideoDecoder()
        {
            sws_freeContext(m_swsCtx);
        }

        void VideoDecoder::decodePacket(AVPacket* packet, AVFrame* frame)
        {
            int finishedFrame = 0;
            auto result = avcodec_decode_video2(m_status->videoCodecCtx, frame, &finishedFrame, packet);

            if (result < 0)
            {
                mprintf(("FFMPEG: Decoding frame failed!\n"));
            }

            if (finishedFrame)
            {
                // Allocate a picture to hold the YUV data
                AVPicture yuvPicture;
                avpicture_alloc(&yuvPicture, PIX_FMT_YUV420P, m_status->videoCodecCtx->width, m_status->videoCodecCtx->height);

                // Convert frame to YUV
                sws_scale(
                    m_swsCtx,
                    (uint8_t const * const *)frame->data,
                    frame->linesize,
                    0,
                    m_status->videoCodecCtx->height,
                    yuvPicture.data,
                    yuvPicture.linesize
                    );

                auto videoFramePtr = std::make_shared<FFMPEGVideoFrame>();
                videoFramePtr->id = ++m_frameId;
                videoFramePtr->frameTime = getFrameTime(av_frame_get_best_effort_timestamp(frame), m_status->videoStream->time_base);
                videoFramePtr->picture = yuvPicture; // The class handles deallocating the memory

                videoFramePtr->ySize.height = m_status->videoCodecCtx->height;
                videoFramePtr->ySize.width = m_status->videoCodecCtx->width;
                videoFramePtr->ySize.stride = yuvPicture.linesize[0];

                // 420P means that the UV channels have half the with and height
                videoFramePtr->uvSize.height = m_status->videoCodecCtx->height / 2;
                videoFramePtr->uvSize.width = m_status->videoCodecCtx->width / 2;
                videoFramePtr->uvSize.stride = yuvPicture.linesize[1];

                m_pushFunction(videoFramePtr);
            }
        }
    }
}
