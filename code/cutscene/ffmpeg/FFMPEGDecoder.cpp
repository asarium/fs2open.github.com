
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

#include <libavutil/imgutils.h>
#include <libavutil/error.h>
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

            AVCodecContext* codecCtx = nullptr;

            AVCodec* codec = nullptr;
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
            for (uint i = 0; i < ctx->nb_streams; ++i)
            {
                if (ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
                {
                    // Found the video stream (we only support one)
                    videoStream = i;
                    break;
                }
            }

            if (videoStream < 0)
            {
                return nullptr;
            }

            status->videoStreamIndex = videoStream;
            status->videoStream = ctx->streams[videoStream];

            status->codecCtx = ctx->streams[videoStream]->codec;
            
            status->codec = avcodec_find_decoder(status->codecCtx->codec_id);
            if (!status->codec)
            {
                mprintf(("FFMPEG: Codec isn't supported!\n"));
                return nullptr;
            }

            AVDictionary *optionsDict = nullptr;
            auto err = avcodec_open2(status->codecCtx, status->codec, &optionsDict);
            if (err < 0)
            {
                char errorStr[512];
                av_strerror(err, errorStr, sizeof(errorStr));
                mprintf(("FFMPEG: Failed to open codec! Error: %s\n", errorStr));
                return nullptr;
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
            props.size.width = m_status->codecCtx->width;
            props.size.height = m_status->codecCtx->height;

            props.fps = static_cast<float>(av_q2d(m_status->videoStream->avg_frame_rate));

            return props;
        }

        void FFMPEGDecoder::startDecoding()
        {
            AVFrame* frame = av_frame_alloc();
            auto swsCtx =
                sws_getContext
                (
                m_status->codecCtx->width,
                m_status->codecCtx->height,
                m_status->codecCtx->pix_fmt,
                m_status->codecCtx->width,
                m_status->codecCtx->height,
                PIX_FMT_YUV420P,
                SWS_BILINEAR,
                nullptr,
                nullptr,
                nullptr
                );
            
            int frameId = 0;

            AVPacket packet;
            while (isDecoding() && av_read_frame(m_input->context, &packet) >= 0)
            {
                if (packet.stream_index == m_status->videoStreamIndex)
                {
                    int finishedFrame = 0;
                    avcodec_decode_video2(m_status->codecCtx, frame, &finishedFrame, &packet);

                    if (finishedFrame)
                    {
                        // Allocate a picture to hold the YUV data
                        AVPicture yuvPicture;
                        auto err = avpicture_alloc(&yuvPicture, PIX_FMT_YUV420P, m_status->codecCtx->width, m_status->codecCtx->height);
                        if (err < 0)
                        {
                            char errorStr[512];
                            av_strerror(err, errorStr, sizeof(errorStr));
                            mprintf(("FFMPEG: Failed to allocate yuv frame! Error: %s\n", errorStr));
                            return;
                        }

                        // Convert frame to YUV
                        sws_scale(
                            swsCtx,
                            (uint8_t const * const *)frame->data,
                            frame->linesize,
                            0,
                            m_status->codecCtx->height,
                            yuvPicture.data,
                            yuvPicture.linesize
                            );

                        auto videoFrame = std::make_shared<FFMPEGVideoFrame>();
                        videoFrame->id = ++frameId;
                        videoFrame->frameTime = getFrameTime(av_frame_get_best_effort_timestamp(frame), m_status->videoStream->time_base);
                        videoFrame->picture = yuvPicture; // The class handles deallocating the memory

                        videoFrame->ySize.height = m_status->codecCtx->height;
                        videoFrame->ySize.width = m_status->codecCtx->width;
                        videoFrame->ySize.stride = yuvPicture.linesize[0];

                        videoFrame->uvSize.height = m_status->codecCtx->height;
                        videoFrame->uvSize.width = m_status->codecCtx->width;
                        videoFrame->uvSize.stride = yuvPicture.linesize[1];

                        lockQueue();

                        waitForQueueSignal();

                        pushFrameData(videoFrame);

                        unlockQueue();
                    }
                }

                av_free_packet(&packet);
            }
            stopDecoder();

            sws_freeContext(swsCtx);
            av_frame_free(&frame);
        }

        bool FFMPEGDecoder::hasAudio()
        {
            return false;
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
