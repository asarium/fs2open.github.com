
#include <limits>

#include <boost/tokenizer.hpp>

#include "cutscene/ffmpeg/FFMPEGDecoder.h"

#include "cfile/cfile.h"

#include "cutscene/ffmpeg/internal.h"

#include "cutscene/ffmpeg/AudioDecoder.h"
#include "cutscene/ffmpeg/VideoDecoder.h"

namespace
{
    using namespace cutscene;

    const size_t AVIO_BUFFER_SIZE = 8192;

    void log_callback_report(void *ptr, int level, const char *fmt, va_list vl)
    {
        va_list vl2;
        char line[1024];
        static int print_prefix = 1;
        
        va_copy(vl2, vl);
        av_log_default_callback(ptr, level, fmt, vl);
        av_log_format_line(ptr, level, fmt, vl2, line, sizeof(line), &print_prefix);
        va_end(vl2);
        
        mprintf(("FFMPEG Log: %s", line)); // no \n, ffmpeg handles that
    }

    void initializeFFMPEG()
    {
        static bool initialized = false;

        if (initialized)
        {
            return;
        }

        av_register_all();
        av_log_set_callback(&log_callback_report);
        av_log_set_level(AV_LOG_ERROR);
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

    double getFrameRate(AVStream* stream)
    {
        // from OpenCV
        double fps = av_q2d(stream->r_frame_rate);

        if (fps < std::numeric_limits<double>::epsilon())
        {
            fps = av_q2d(stream->avg_frame_rate);
        }

        if (fps < std::numeric_limits<double>::epsilon())
        {
            fps = 1.0 / av_q2d(stream->codec->time_base);
        }

        return fps;
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

        namespace
        {
            std::unique_ptr<InputStream> openStream(const SCP_string& name)
            {
                // Only search the root and data/movies
                auto filePtr = cfopen(name.c_str(), "rb", CFILE_NORMAL, CF_TYPE_ROOT);
                if (!filePtr)
                {
                    filePtr = cfopen(name.c_str(), "rb", CFILE_NORMAL, CF_TYPE_MOVIES);
                }

                if (!filePtr)
                {
                    return nullptr;
                }

                auto input = std::make_unique<InputStream>();
                input->filePtr = filePtr;

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
                cfseek(input->filePtr, 0, CF_SEEK_SET);

                // Make sure we don't cause a buffer overrun
                Assert(read <= (int)input->bufferSize);

                AVProbeData probe;
                probe.buf = input->avioBuffer;
                probe.buf_size = read;
                probe.filename = nullptr;
                probe.mime_type = nullptr;

                input->context->iformat = av_probe_input_format(&probe, true);

                input->context->flags |= AVFMT_FLAG_CUSTOM_IO;

                auto ret = avformat_open_input(&input->context, nullptr, input->context->iformat, nullptr);
                if (ret < 0)
                {
                    char errorStr[AV_ERROR_MAX_STRING_SIZE];
                    av_strerror(ret, errorStr, AV_ERROR_MAX_STRING_SIZE);
                    mprintf(("FFMPEG: Could not open movie file! Error: %s\n", errorStr));
                    return nullptr;
                }

                ret = avformat_find_stream_info(input->context, nullptr);
                if (ret < 0)
                {
                    char errorStr[AV_ERROR_MAX_STRING_SIZE];
                    av_strerror(ret, errorStr, AV_ERROR_MAX_STRING_SIZE);
                    mprintf(("FFMPEG: Failed to get stream information! Error: %s\n", errorStr));
                    return nullptr;
                }

                return input;
            }

            std::unique_ptr<DecoderStatus> initializeStatus(std::unique_ptr<InputStream>& stream)
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

            std::unique_ptr<InputStream> openInputStream(const SCP_string& name)
            {
                initializeFFMPEG();

                auto format = av_iformat_next(nullptr);
                while (format != nullptr)
                {
                    // Check all formats that specify extensions
                    if (format->extensions != nullptr)
                    {
                        SCP_string extensions(format->extensions);

                        boost::char_separator<char> sep(",");
                        boost::tokenizer<boost::char_separator<char>,
                            SCP_string::const_iterator,
                            SCP_string> tok(extensions, sep);

                        for (auto ext : tok)
                        {
                            auto fileName = name + "." + ext;

                            auto input = openStream(fileName);

                            if (input)
                            {
                                return input;
                            }
                        }
                    }

                    format = av_iformat_next(format);
                }

                return nullptr;
            }
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

            auto input = openInputStream(movieName);

            if (!input)
            {
                return false;
            }

            auto status = initializeStatus(input);
            if (!status)
            {
                return false;
            }

            // Buffer ~ 2 seconds of video and audio
            initializeQueues(static_cast<size_t>(ceil(getFrameRate(status->videoStream))) * 2);

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

            props.fps = static_cast<float>(getFrameRate(m_status->videoStream));

            return props;
        }

        void FFMPEGDecoder::startDecoding()
        {
            using namespace std::placeholders;

            AVFrame* frame = av_frame_alloc();

            std::unique_ptr<VideoDecoder> videoDecoder = std::make_unique<VideoDecoder>(m_status.get(),
                std::bind(&FFMPEGDecoder::pushFrameData, this, _1));

            std::unique_ptr<AudioDecoder> audioDecoder;

            if (hasAudio())
            {
                audioDecoder = std::make_unique<AudioDecoder>(m_status.get(), std::bind(&FFMPEGDecoder::pushAudioData, this, _1));
            }
            
            AVPacket packet;
            while (isDecoding() && av_read_frame(m_input->context, &packet) >= 0)
            {
                if (packet.stream_index == m_status->videoStreamIndex)
                {
                    videoDecoder->decodePacket(&packet, frame);
                }
                else if (audioDecoder && packet.stream_index == m_status->audioStreamIndex)
                {
                    audioDecoder->decodePacket(&packet, frame);
                }

                av_free_packet(&packet);
            }

            if (isDecoding())
            {
                // If we are still alive read the last frames from the decoders

                // The ffmpeg decoder functions use this packet to return frames
                // if the decoder has a delay
                packet.data = nullptr;
                packet.size = 0;

                videoDecoder->finishDecoding(&packet, frame);

                if (audioDecoder)
                {
                    audioDecoder->finishDecoding(&packet, frame);
                }
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
