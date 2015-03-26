
#include "cutscene/ffmpeg/AudioDecoder.h"

namespace
{
    const int OUT_CH_LAYOUT = AV_CH_LAYOUT_STEREO;
    const int OUT_SAMPLE_RATE = 48000;
    const AVSampleFormat OUT_SAMPLE_FORMAT = AV_SAMPLE_FMT_S16;
    const int OUT_NUM_CHANNELS = av_get_channel_layout_nb_channels(OUT_CH_LAYOUT);

    const int DEFAULT_SRC_NUM_SAMPLES = 1024;

    SwrContext* getSWRContext(uint64_t layout, int rate, AVSampleFormat inFmt)
    {
        auto swr = swr_alloc();

        av_opt_set_int(swr, "in_channel_layout", layout, 0);
        av_opt_set_int(swr, "in_sample_rate", rate, 0);
        av_opt_set_sample_fmt(swr, "in_sample_fmt", inFmt, 0);

        av_opt_set_int(swr, "out_channel_layout", OUT_CH_LAYOUT, 0);
        av_opt_set_int(swr, "out_sample_rate", OUT_SAMPLE_RATE, 0);
        av_opt_set_sample_fmt(swr, "out_sample_fmt", OUT_SAMPLE_FORMAT, 0);

        swr_init(swr);

        return swr;
    }
}

namespace cutscene
{
    namespace ffmpeg
    {
        AudioDecoder::AudioDecoder(DecoderStatus* status, std::function<void(std::shared_ptr<AudioFrame>)> push)
            : FFMPEGStreamDecoder(status, push)
        {
            m_audioBuffer.reserve(OUT_SAMPLE_RATE * OUT_NUM_CHANNELS / 2);

            m_swrCtx = getSWRContext(m_status->audioCodecCtx->channel_layout, m_status->audioCodecCtx->sample_rate,
                m_status->audioCodecCtx->sample_fmt);

            /* 
             * compute the number of converted samples: buffering is avoided
             * ensuring that the output buffer will contain at least all the
             * converted input samples
             */
            m_maxOutNumSamples = m_outNumSamples = static_cast<int>(av_rescale_rnd(DEFAULT_SRC_NUM_SAMPLES,
                OUT_SAMPLE_RATE, m_status->audioCodecCtx->sample_rate, AV_ROUND_UP));

            auto ret = av_samples_alloc_array_and_samples(&m_outData, &m_outLinesize, OUT_NUM_CHANNELS,
                m_outNumSamples, OUT_SAMPLE_FORMAT, 0);

            if (ret < 0)
            {
                mprintf(("FFMPEG: Failed to allocate samples array!\n"));
            }
        }

        AudioDecoder::~AudioDecoder()
        {
            if (m_outData)
                av_freep(&m_outData[0]);
            av_freep(&m_outData);

            swr_free(&m_swrCtx);
        }

        void AudioDecoder::flushAudioBuffer()
        {
            AudioFramePtr audioFrame = std::make_shared<AudioFrame>();
            audioFrame->channels = OUT_NUM_CHANNELS;
            audioFrame->rate = OUT_SAMPLE_RATE;

            audioFrame->audioData.assign(m_audioBuffer.begin(), m_audioBuffer.end());

            m_pushFunction(audioFrame);
            m_audioBuffer.clear();
        }

        void AudioDecoder::handleDecodedFrame(AVFrame* frame)
        {
            /* compute destination number of samples */
            m_outNumSamples = static_cast<int>(av_rescale_rnd(swr_get_delay(m_swrCtx, m_status->audioCodecCtx->sample_rate)
                + frame->nb_samples, OUT_SAMPLE_RATE, m_status->audioCodecCtx->sample_rate, AV_ROUND_UP));

            if (m_outNumSamples > m_maxOutNumSamples)
            {
                av_freep(&m_outData[0]);
                auto ret = av_samples_alloc(m_outData, &m_outLinesize, OUT_NUM_CHANNELS, m_outNumSamples, OUT_SAMPLE_FORMAT, 1);
                if (ret < 0)
                {
                    mprintf(("FFMPEG: Failed to allocate samples!!!"));
                    return;
                }

                m_maxOutNumSamples = m_outNumSamples;
            }

            /* convert to destination format */
            auto ret = swr_convert(m_swrCtx, m_outData, m_outNumSamples, (const uint8_t **)frame->data, frame->nb_samples);
            if (ret < 0)
            {
                mprintf(("FFMPEG: Error while converting audio!\n"));
                return;
            }

            auto outBufsize = av_samples_get_buffer_size(&m_outLinesize, OUT_NUM_CHANNELS, ret, OUT_SAMPLE_FORMAT, 1);
            if (outBufsize < 0)
            {
                mprintf(("FFMPEG: Could not get sample buffer size!\n"));
                return;
            }

            auto begin = reinterpret_cast<short*>(m_outData[0]);
            auto end = reinterpret_cast<short*>(m_outData[0] + outBufsize);

            auto size = std::distance(begin, end);
            auto newSize = m_audioBuffer.size() + size;

            if (newSize <= m_audioBuffer.capacity())
            {
                // We haven't filled the buffer yet
                m_audioBuffer.insert(m_audioBuffer.end(), begin, end);
            }
            else
            {
                flushAudioBuffer();
                m_audioBuffer.assign(begin, end);
            }
        }

        void AudioDecoder::decodePacket(const AVPacket* packet, AVFrame* frame)
        {
            int finishedFrame = 0;
            auto err = avcodec_decode_audio4(m_status->audioCodecCtx, frame, &finishedFrame, packet);

            if (err >= 0 && finishedFrame)
            {
                handleDecodedFrame(frame);
            }
        }

        void AudioDecoder::finishDecoding(const AVPacket* nullPacket, AVFrame* frame)
        {
            // Handle those decoders that have a delay
            while (true)
            {
                int finishedFrame = 1;
                auto err = avcodec_decode_audio4(m_status->audioCodecCtx, frame, &finishedFrame, nullPacket);

                if (err < 0 || !finishedFrame)
                {
                    break;
                }

                handleDecodedFrame(frame);
            }

            if (m_audioBuffer.empty())
            {
                // Nothing to do here anymore
                return;
            }

            // Push the last bits of audio data into the queue
            flushAudioBuffer();
        }
    }
}
