
#include "cutscene/ffmpeg/FFMPEGDecoder.h"

#include "cfile/cfile.h"

// Disable a few warnings that happen in the ffmpeg headers
// TODO: Also do this for other compilers
#pragma warning(push)
#pragma warning(disable: 4244) // conversion from 'int' to '*'

extern "C" {
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
#include <swresample.h>

#include <libavutil/imgutils.h>
#include <libavutil/error.h>
#include <libavutil/opt.h>
}

#pragma warning(pop)

namespace
{
    using namespace cutscene;

    const size_t AVIO_BUFFER_SIZE = 8192;

    void initializeFFMPEG()
    {
        static bool initialized = false;

        if (initialized)
        {
            return;
        }

        av_register_all();
    }

    int cfileRead(void* ptr, uint8_t* buf, int buf_size)
    {
        auto cfile = reinterpret_cast<CFILE*>(ptr);

        auto numRead = cfread(buf, 1, buf_size, cfile);

        if (numRead == 0)
        {
            // Read failed
            return -1;
        }

        return numRead;
    }

    int64_t cfileSeek(void *ptr, int64_t offset, int whence)
    {
        auto cfile = reinterpret_cast<CFILE*>(ptr);

        int op = CF_SEEK_SET;
        switch (whence)
        {
        case SEEK_SET:
            op = CF_SEEK_SET;
            break;
        case SEEK_CUR:
            op = CF_SEEK_CUR;
            break;
        case SEEK_END:
            op = CF_SEEK_END;
            break;
        case AVSEEK_SIZE:
            return cfilelength(cfile);
        }

        cfseek(cfile, static_cast<int>(offset), op);

        // cfseek returns the offset in the archive file (who thought that would be a good idea?)
        return cftell(cfile);
    }

    float getFrameTime(int64_t pts, AVRational time_base)
    {
        return static_cast<float>(pts * av_q2d(time_base));
    }

    SwsContext* getSWSContext(int width, int height, AVPixelFormat fmt)
    {
        return sws_getContext(width, height, fmt, width, height, PIX_FMT_YUV420P,
            SWS_BILINEAR, nullptr, nullptr, nullptr);
    }

    SwrContext* getSWRContext(uint64_t layout, int rate, AVSampleFormat inFmt)
    {
        auto swr = swr_alloc();

        av_opt_set_int(swr, "in_channel_layout", layout, 0);
        av_opt_set_int(swr, "out_channel_layout", layout, 0);
        av_opt_set_int(swr, "in_sample_rate", rate, 0);
        av_opt_set_int(swr, "out_sample_rate", rate, 0);
        av_opt_set_sample_fmt(swr, "in_sample_fmt", inFmt, 0);
        av_opt_set_sample_fmt(swr, "out_sample_fmt", AV_SAMPLE_FMT_S16, 0);

        swr_init(swr);

        return swr;
    }
}

namespace cutscene
{
    namespace ffmpeg
    {
        struct InputStream
        {
            CFILE* filePtr = nullptr;

            AVFormatContext* context = nullptr;
            AVIOContext* ioContext = nullptr;

            uint8_t* avioBuffer = nullptr;
            size_t bufferSize = 0;

            InputStream(const InputStream&) = delete;
            InputStream()
            {}

            ~InputStream()
            {
                if (context)
                {
                    avformat_close_input(&context);
                    context = nullptr;
                }

                if (avioBuffer)
                {
                    av_free(avioBuffer);
                    avioBuffer = nullptr;
                    bufferSize = 0;
                }

                if (ioContext)
                {
                    av_free(ioContext);
                    ioContext = nullptr;
                }

                if (filePtr)
                {
                    cfclose(filePtr);
                    filePtr = nullptr;
                }
            }
        };

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

        class FFMPEGVideoFrame : public VideoFrame
        {
        public:
            FFMPEGVideoFrame()
            {
                memset(&picture, 0, sizeof(picture));
            }
            virtual ~FFMPEGVideoFrame()
            {
                if (picture.data[0] != nullptr)
                {
                    avpicture_free(&picture);
                    memset(&picture, 0, sizeof(picture));
                }
            }

            virtual DataPointers getDataPointers()
            {
                DataPointers ptrs;
                ptrs.y = picture.data[0];
                ptrs.u = picture.data[1];
                ptrs.v = picture.data[2];

                return ptrs;
            }

            AVPicture picture;
        };

        FFMPEGDecoder::FFMPEGDecoder()
        {
        }

        FFMPEGDecoder::~FFMPEGDecoder()
        {
        }

        std::unique_ptr<InputStream> FFMPEGDecoder::openStream(const SCP_string& name)
        {
            auto input = std::make_unique<InputStream>();
            input->filePtr = cfopen(name.c_str(), "rb", CFILE_NORMAL, CF_TYPE_ANY);

            if (!input->filePtr)
            {
                // file does not exist
                return nullptr;
            }

            // Only initialize ffmpeg if we are actually going to use it
            initializeFFMPEG();

            mprintf(("FFMPEG: Opening movie file '%s'...\n", name.c_str()));

            input->context = avformat_alloc_context();

            if (!input->context)
            {
                mprintf(("FFMPEG: Failed to allocate context! Error: %s\n"));
                return nullptr;
            }

            input->avioBuffer = reinterpret_cast<uint8_t*>(av_malloc(AVIO_BUFFER_SIZE));

            if (!input->avioBuffer)
            {
                mprintf(("FFMPEG: Failed to allocate IO buffer!\n"));
                return nullptr;
            }
            input->bufferSize = AVIO_BUFFER_SIZE;

            input->ioContext = avio_alloc_context(input->avioBuffer, input->bufferSize, 0, input->filePtr, cfileRead, nullptr, cfileSeek);
            input->context->pb = input->ioContext;

            if (!input->ioContext)
            {
                mprintf(("FFMPEG: Failed to allocate IO context!\n"));
                return nullptr;
            }

            // Now determine the format
            auto read = cfread(input->avioBuffer, 1, input->bufferSize, input->filePtr);

            // Make sure we don't cause a buffer overrun
            Assert(read <= (int) input->bufferSize);

            AVProbeData probe;
            probe.buf = input->avioBuffer;
            probe.buf_size = read;
            probe.filename = name.c_str();
            probe.mime_type = nullptr;

            input->context->iformat = av_probe_input_format(&probe, true);

            input->context->flags |= AVFMT_FLAG_CUSTOM_IO;

            auto ret = avformat_open_input(&input->context, name.c_str(), nullptr, nullptr);
            if (ret < 0)
            {
                char errorStr[512];
                av_strerror(ret, errorStr, sizeof(errorStr));
                mprintf(("FFMPEG: Could not open movie file! Error: %s\n", errorStr));
                return nullptr;
            }

            ret = avformat_find_stream_info(input->context, nullptr);
            if (ret < 0)
            {
                char errorStr[512];
                av_strerror(ret, errorStr, sizeof(errorStr));
                mprintf(("FFMPEG: Failed to get stream information! Error: %s\n", errorStr));
                return nullptr;
            }

            return input;
        }

        std::unique_ptr<DecoderStatus> FFMPEGDecoder::initializeStatus(std::unique_ptr<InputStream>& stream)
        {
            auto status = std::make_unique<DecoderStatus>();

            auto ctx = stream->context;

            auto videoStream = -1;
            auto audioStream = -1;
            for (uint i = 0; i < ctx->nb_streams; ++i)
            {
                if (videoStream == -1 && ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
                {
                    // Found the video stream (we only support one)
                    videoStream = i;
                }
                else if (audioStream == -1 && ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
                {
                    audioStream = i;
                }
            }

            if (videoStream < 0)
            {
                return nullptr;
            }

            status->videoStreamIndex = videoStream;
            status->videoStream = ctx->streams[videoStream];

            if (audioStream >= 0)
            {
                status->audioStreamIndex = audioStream;
                status->audioStream = ctx->streams[audioStream];
            }

            status->videoCodecCtx = ctx->streams[videoStream]->codec;
            status->videoCodec = avcodec_find_decoder(status->videoCodecCtx->codec_id);

            if (!status->videoCodec)
            {
                mprintf(("FFMPEG: Video codec isn't supported!\n"));
                return nullptr;
            }

            AVDictionary *optionsDict = nullptr;
            auto err = avcodec_open2(status->videoCodecCtx, status->videoCodec, &optionsDict);
            if (err < 0)
            {
                char errorStr[512];
                av_strerror(err, errorStr, sizeof(errorStr));
                mprintf(("FFMPEG: Failed to open video codec! Error: %s\n", errorStr));
                return nullptr;
            }

            // Now initialize audio, if this fails it's not a fatal error
            if (audioStream >= 0)
            {
                status->audioCodecCtx = status->audioStream->codec;
                status->audioCodec = avcodec_find_decoder(status->audioCodecCtx->codec_id);

                if (!status->audioCodec)
                {
                    mprintf(("FFMPEG: No compatible audio decoder found!\n"));
                    status->audioStreamIndex = -1;
                    status->audioStream = nullptr;
                    status->audioCodecCtx = nullptr;
                    status->audioCodec = nullptr;
                }
                else
                {
                    AVDictionary* audioOpts = nullptr;
                    err = avcodec_open2(status->audioCodecCtx, status->audioCodec, &audioOpts);
                    if (err < 0)
                    {
                        char errorStr[512];
                        av_strerror(err, errorStr, sizeof(errorStr));
                        mprintf(("FFMPEG: Failed to open audio codec! Error: %s\n", errorStr));
                        status->audioStreamIndex = -1;
                        status->audioStream = nullptr;
                        status->audioCodecCtx = nullptr;
                        status->audioCodec = nullptr;
                    }
                }
            }

            return status;
        }

        bool FFMPEGDecoder::initialize(const SCP_string& fileName)
        {
            SCP_string movieName = fileName;
            std::transform(movieName.begin(), movieName.end(), movieName.begin(), ::tolower);

            size_t dotPos = movieName.find('.');
            if (dotPos != SCP_string::npos)
            {
                movieName.resize(dotPos);
            }
            
            // Only mp4 is supported for now
            movieName.append(".mp4");

            auto input = openStream(movieName);
            if (!input)
            {
                return false;
            }

            auto status = initializeStatus(input);
            if (!status)
            {
                return false;
            }

            // We're done, now just put the pointer into this
            std::swap(m_input, input);
            std::swap(m_status, status);
            return true;
        }

        MovieProperties FFMPEGDecoder::getProperties()
        {
            MovieProperties props;
            props.size.width = m_status->videoCodecCtx->width;
            props.size.height = m_status->videoCodecCtx->height;

            props.fps = static_cast<float>(av_q2d(m_status->videoStream->avg_frame_rate));

            return props;
        }

        void FFMPEGDecoder::startDecoding()
        {
            AVFrame* frame = av_frame_alloc();

            // Get the scaling context to convert the frame to YUV
            auto swsCtx = getSWSContext(m_status->videoCodecCtx->width, m_status->videoCodecCtx->height,
                m_status->videoCodecCtx->pix_fmt);

            // Get a resampling context used for resampling the data to a format we can use
            auto swrCtx = getSWRContext(m_status->audioCodecCtx->channel_layout, m_status->audioCodecCtx->sample_rate,
                m_status->audioCodecCtx->sample_fmt);
            auto bla = swr_get_delay(swrCtx, m_status->audioCodecCtx->sample_rate);

            auto audioPlanes = av_sample_fmt_is_planar(m_status->audioCodecCtx->sample_fmt) ? m_status->audioCodecCtx->channels : 1;
            
            std::shared_ptr<FFMPEGVideoFrame> videoFramePtr;
            AudioFramePtr audioDataPtr;

            int frameId = 0;

            AVPacket packet;
            while (isDecoding() && av_read_frame(m_input->context, &packet) >= 0)
            {
                if (packet.stream_index == m_status->videoStreamIndex)
                {
                    int finishedFrame = 0;
                    auto result = avcodec_decode_video2(m_status->videoCodecCtx, frame, &finishedFrame, &packet);

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
                            swsCtx,
                            (uint8_t const * const *)frame->data,
                            frame->linesize,
                            0,
                            m_status->videoCodecCtx->height,
                            yuvPicture.data,
                            yuvPicture.linesize
                            );

                        videoFramePtr = std::make_shared<FFMPEGVideoFrame>();
                        videoFramePtr->id = ++frameId;
                        videoFramePtr->frameTime = getFrameTime(av_frame_get_best_effort_timestamp(frame), m_status->videoStream->time_base);
                        videoFramePtr->picture = yuvPicture; // The class handles deallocating the memory

                        videoFramePtr->ySize.height = m_status->videoCodecCtx->height;
                        videoFramePtr->ySize.width = m_status->videoCodecCtx->width;
                        videoFramePtr->ySize.stride = yuvPicture.linesize[0];

                        videoFramePtr->uvSize.height = m_status->videoCodecCtx->height;
                        videoFramePtr->uvSize.width = m_status->videoCodecCtx->width;
                        videoFramePtr->uvSize.stride = yuvPicture.linesize[1];
                    }
                }
                else if (packet.stream_index == m_status->audioStreamIndex)
                {
                    int finishedFrame = 0;
                    //avcodec_decode_audio4(m_status->audioCodecCtx, frame, &finishedFrame, &packet);

                    if (finishedFrame)
                    {
                        /*uint8_t *output;
                        int out_samples = av_rescale_rnd(swr_get_delay(swr, 48000) +
                            in_samples, 44100, 48000, AV_ROUND_UP);
                        av_samples_alloc(&output, NULL, 2, out_samples,
                            AV_SAMPLE_FMT_S16, 0);
                        out_samples = swr_convert(swr, &output, out_samples,
                            input, in_samples);
                        handle_output(output, out_samples);
                        av_freep(&output);*/
                    }
                }

                if (canPushVideoData() && videoFramePtr)
                {
                    pushFrameData(videoFramePtr);
                    videoFramePtr = nullptr;
                }

                if (canPushAudioData() && audioDataPtr)
                {
                    pushAudioData(audioDataPtr);
                    audioDataPtr = nullptr;
                }

                av_free_packet(&packet);
            }
            stopDecoder();

            swr_free(&swrCtx);
            sws_freeContext(swsCtx);
            av_frame_free(&frame);
        }

        bool FFMPEGDecoder::hasAudio()
        {
            return m_status->audioStreamIndex >= 0;
        }

        void FFMPEGDecoder::close()
        {
            if (m_status)
            {
                m_status = nullptr;
            }

            if (m_input)
            {
                // This will delete the InputStream pointer and free all data
                m_input = nullptr;
            }
        }
    }
}
