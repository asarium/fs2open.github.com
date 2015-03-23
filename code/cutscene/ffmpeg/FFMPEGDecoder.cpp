
#include "cutscene/ffmpeg/FFMPEGDecoder.h"

#include "cfile/cfile.h"

#include "cutscene/ffmpeg/internal.h"

#include "cutscene/ffmpeg/AudioDecoder.h"
#include "cutscene/ffmpeg/VideoDecoder.h"

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

            initializeQueues(static_cast<size_t>(ceil(av_q2d(status->videoStream->avg_frame_rate))));

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
            using namespace std::placeholders;

            AVFrame* frame = av_frame_alloc();

            VideoDecoder videoDecoder(m_status.get(), std::bind(&FFMPEGDecoder::pushFrameData, this, _1));
            AudioDecoder audioDecoder(m_status.get(), std::bind(&FFMPEGDecoder::pushAudioData, this, _1));
                        
            AudioFramePtr audioDataPtr;
            
            AVPacket packet;
            while (isDecoding() && av_read_frame(m_input->context, &packet) >= 0)
            {
                if (packet.stream_index == m_status->videoStreamIndex)
                {
                    videoDecoder.decodePacket(&packet, frame);
                }
                else if (packet.stream_index == m_status->audioStreamIndex)
                {
                    audioDecoder.decodePacket(&packet, frame);
                }

                av_free_packet(&packet);
            }
            stopDecoder();

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
