
#include "cutscene/player.h"

#include "cutscene/Decoder.h"
#include "cutscene/ogg/OggDecoder.h"
#include "cutscene/ffmpeg/FFMPEGDecoder.h"

#include "osapi/osapi.h"

#include "sound/openal.h"

#include "io/key.h"
#include "io/timer.h"

#include "globalincs/def_files.h"

#include "graphics/gropengl.h"
#include "graphics/gropengltexture.h"
#include "graphics/gropenglextension.h"
#include "graphics/gropenglshader.h"
#include "graphics/gropenglstate.h"

// video externs from API graphics functions
extern void opengl_tcache_get_adjusted_texture_size(int w_in, int h_in, int *w_out, int *h_out);

namespace cutscene
{
    struct PlayerState
    {
        MovieProperties props;
        Decoder* decoder;

        bool playing = true;

        bool doSleep = true;

        bool playbackHasBegun = false;

        int lastDisplayTimestamp = -1;

        // Timing state
        longlong baseTime = -1;

        // Audio state
        bool audioInited = false;
        ALuint audioSid = 0;
        SCP_vector<ALuint> audioBuffers;
        SCP_queue<ALuint> unqueuedAudioBuffers;

        // Graphics state following
        bool videoInited = false;

        VideoFramePtr currentFrame;
        
        GLfloat glVertices[4][4];

        // GPU accelerated decoding
        bool useShaders = true;

        GLuint ytex = 0;
        GLuint utex = 0;
        GLuint vtex = 0;

        // CPU only decoding
        GLuint GLtex = 0;
        ubyte* pixelbuf = nullptr;

        bool scaleVideo = false;
    };
}

namespace
{
    using namespace cutscene;

    const int MAX_AUDIO_BUFFERS = 15;

    Decoder* findDecoder(const SCP_string& name)
    {
        {
            auto ffmpeg = new ffmpeg::FFMPEGDecoder();
            if (ffmpeg->initialize(name))
            {
                return ffmpeg;
            }
            delete ffmpeg;
        }
        {
            auto ogg = new ogg::OggDecoder();
            if (ogg->initialize(name))
            {
                return ogg;
            }
            delete ogg;
        }

        return nullptr;
    }

    // get relative time since beginning playback, compensating for A/V drift
    double playbackGetTime(PlayerState* state)
    {
#ifdef SCP_UNIX
        longlong now;
        struct timeval tv;

        gettimeofday(&tv, NULL);
        now = tv.tv_sec * 1000 + tv.tv_usec / 1000;

        if (state->baseTime == -1)
            state->baseTime = now;

        return (now - state->baseTime) * 0.001;
#else
        if (state->baseTime == -1)
        {
            state->baseTime = timer_get_milliseconds();
        }

        return (timer_get_milliseconds() - state->baseTime) * 0.001;
#endif
    }

    void videoPlaybackInit(PlayerState* state)
    {
        float scale_by = 0.0f;

        GLhandleARB shader_id = 0;

        if (state->videoInited)
            return;

        Assert(state != NULL);

        int wp2;
        int hp2;

        if (gr_screen.mode == GR_OPENGL) {
            opengl_set_texture_target(GL_TEXTURE_2D);
            opengl_tcache_get_adjusted_texture_size(state->props.size.width, state->props.size.height, &wp2, &hp2);

            if (!Use_GLSL)
                state->useShaders = false;

            if (state->useShaders) {
                glGenTextures(1, &state->ytex);
                glGenTextures(1, &state->utex);
                glGenTextures(1, &state->vtex);

                Assert(state->ytex != 0);
                Assert(state->utex != 0);
                Assert(state->vtex != 0);


                if (state->ytex + state->utex + state->vtex == 0) {
                    nprintf(("MOVIE", "ERROR: Can't create a GL texture"));
                    state->videoInited = 1;
                    return;
                }

                char *vert = NULL, *frag = NULL;
                opengl_shader_t new_shader;

                // choose appropriate files
                char *vert_name = "video-v.sdr";
                char *frag_name = "video-f.sdr";

                mprintf(("Compiling video-processing shader ... \n"));

                // read vertex shader
                CFILE *cf_shader = cfopen(vert_name, "rt", CFILE_NORMAL, CF_TYPE_EFFECTS);

                if (cf_shader != NULL) {
                    int len = cfilelength(cf_shader);
                    vert = (char*)vm_malloc(len + 1);
                    cfread(vert, len + 1, 1, cf_shader);
                    cfclose(cf_shader);
                }
                else {
                    mprintf(("   Loading built-in default shader for: %s\n", vert_name));
                    vert = defaults_get_file(vert_name);
                }

                if (!vert)
                    state->useShaders = false;

                // read fragment shader
                cf_shader = cfopen(frag_name, "rt", CFILE_NORMAL, CF_TYPE_EFFECTS);

                if (cf_shader != NULL) {
                    int len = cfilelength(cf_shader);
                    frag = (char*)vm_malloc(len + 1);
                    cfread(frag, len + 1, 1, cf_shader);
                    cfclose(cf_shader);
                }
                else {
                    mprintf(("   Loading built-in default shader for: %s\n", frag_name));
                    frag = defaults_get_file(frag_name);
                }

                if (!vert)
                    state->useShaders = false;
                Verify(vert != NULL);
                Verify(frag != NULL);

                shader_id = opengl_shader_create(vert, frag);
                vglUseProgramObjectARB(shader_id);
                if (!shader_id)
                    state->useShaders = false;
            }

            if (!state->useShaders) {
                glGenTextures(1, &state->GLtex);

                Assert(state->GLtex != 0);

                if (state->GLtex == 0) {
                    nprintf(("MOVIE", "ERROR: Can't create a GL texture"));
                    state->videoInited = 1;
                    return;
                }
            }

            gr_set_lighting(false, false);
            GL_state.Texture.DisableAll();

            if (!state->useShaders) {
                GL_state.Texture.SetActiveUnit(0);
                GL_state.Texture.SetTarget(GL_texture_target);
                GL_state.Texture.Enable(state->GLtex);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_RGB8, wp2, hp2, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);
            }
            GL_state.SetTextureSource(TEXTURE_SOURCE_DECAL);
            GL_state.SetAlphaBlendMode(ALPHA_BLEND_NONE);
            GL_state.SetZbufferType(ZBUFFER_TYPE_NONE);

            if (state->useShaders) {
                GL_state.Texture.SetActiveUnit(0);
                GL_state.Texture.SetTarget(GL_texture_target);
                GL_state.Texture.Enable(state->ytex);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                // NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
                glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_LUMINANCE8, wp2, hp2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);

                GL_state.Texture.SetActiveUnit(1);
                GL_state.Texture.SetTarget(GL_texture_target);
                GL_state.Texture.Enable(state->utex);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                // NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
                glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_LUMINANCE8, wp2 / 2, hp2 / 2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);

                GL_state.Texture.SetActiveUnit(2);
                GL_state.Texture.SetTarget(GL_texture_target);
                GL_state.Texture.Enable(state->vtex);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                // NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
                glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_LUMINANCE8, wp2 / 2, hp2 / 2, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, NULL);
            }
            float screen_ratio = (float)gr_screen.max_w / (float)gr_screen.max_h;
            float movie_ratio = (float)state->props.size.width / (float)state->props.size.height;

            if (screen_ratio > movie_ratio)
                scale_by = (float)gr_screen.max_h / (float)state->props.size.height;
            else
                scale_by = (float)gr_screen.max_w / (float)state->props.size.width;

            // don't bother setting anything if we aren't going to need it
            if (!Cmdline_noscalevid && (scale_by != 1.0f)) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();

                glScalef(scale_by, scale_by, -1.0f);
                state->scaleVideo = 1;
            }

            // set our color so that we can make sure that it's correct
            GL_state.Color(255, 255, 255, 255);
        }

        if (!state->useShaders) {
            state->pixelbuf = (ubyte *)vm_malloc_q(state->props.size.width * state->props.size.height * 3);

            if (state->pixelbuf == NULL) {
                nprintf(("MOVIE", "ERROR: Can't allocate memory for pixelbuf"));
                state->videoInited = 1;
                return;
            }
            memset(state->pixelbuf, 0, state->props.size.width * state->props.size.height * 3);
        }

        int screenX;
        int screenY;

        if (state->scaleVideo) {
            screenX = ((fl2i(gr_screen.max_w / scale_by + 0.5f) - state->props.size.width) / 2);
            screenY = ((fl2i(gr_screen.max_h / scale_by + 0.5f) - state->props.size.height) / 2);
        }
        else {
            // centers on 1024x768, fills on 640x480
            screenX = ((gr_screen.max_w - state->props.size.width) / 2);
            screenY = ((gr_screen.max_h - state->props.size.height) / 2);
        }

        // set additional values for screen width/height and UV coords
        if (gr_screen.mode == GR_OPENGL) {
            int screenXW = screenX + state->props.size.width;
            int screenYH = screenY + state->props.size.height;

            if (state->useShaders) {
                GL_state.Texture.SetShaderMode(GL_TRUE);
                vglUniform1iARB(vglGetUniformLocationARB(shader_id, "ytex"), 0);
                vglUniform1iARB(vglGetUniformLocationARB(shader_id, "utex"), 1);
                vglUniform1iARB(vglGetUniformLocationARB(shader_id, "vtex"), 2);
            }

            state->glVertices[0][0] = (GLfloat)screenX;
            state->glVertices[0][1] = (GLfloat)screenY;
            state->glVertices[0][2] = 0.0f;
            state->glVertices[0][3] = 0.0f;

            state->glVertices[1][0] = (GLfloat)screenX;
            state->glVertices[1][1] = (GLfloat)screenYH;
            state->glVertices[1][2] = 0.0f;
            state->glVertices[1][3] = 1.0f;

            state->glVertices[2][0] = (GLfloat)screenXW;
            state->glVertices[2][1] = (GLfloat)screenY;
            state->glVertices[2][2] = 1.0f;
            state->glVertices[2][3] = 0.0f;

            state->glVertices[3][0] = (GLfloat)screenXW;
            state->glVertices[3][1] = (GLfloat)screenYH;
            state->glVertices[3][2] = 1.0f;
            state->glVertices[3][3] = 1.0f;

            GL_state.Array.BindArrayBuffer(0);

            GL_state.Array.EnableClientVertex();
            GL_state.Array.VertexPointer(2, GL_FLOAT, sizeof(state->glVertices[0]), state->glVertices);

            GL_state.Array.SetActiveClientUnit(0);
            GL_state.Array.EnableClientTexture();
            GL_state.Array.TexPointer(2, GL_FLOAT, sizeof(state->glVertices[0]), &(state->glVertices[0][2]));
        }
        if (!state->useShaders && state->props.size.height > 450) {
            mprintf(("VIDEO: No shader support and hd video is beeing played this can get choppy."));
        }
        state->videoInited = true;
    }

    void audioPlaybackInit(PlayerState* state)
    {
        if (state->audioInited)
            return;

        OpenAL_ErrorCheck(alGenSources(1, &state->audioSid), return);
        OpenAL_ErrorPrint(alSourcef(state->audioSid, AL_GAIN, 1.0f));

        state->audioBuffers.clear();
        state->audioBuffers.resize(MAX_AUDIO_BUFFERS, 0);

        OpenAL_ErrorCheck(alGenBuffers(state->audioBuffers.size(), state->audioBuffers.data()), return);

        for (auto buffer : state->audioBuffers)
        {
            state->unqueuedAudioBuffers.push(buffer);
        }

        state->audioInited = true;
    }

    void convert_YUV_to_RGB(PlayerState* state)
    {
        int Y1, Y2, U, V;
        int R = 0, G = 0, B = 0;
        int C, D, E;
        uint x, y;
        uint width_2 = state->props.size.width / 2;

        ubyte *pix = &state->pixelbuf[0];

        auto ptrs = state->currentFrame->getDataPointers();
        ubyte *y_ptr = ptrs.y;
        ubyte *u_ptr = ptrs.u;
        ubyte *v_ptr = ptrs.v;

        for (y = 0; y < (uint)state->props.size.height; y++) {
            for (x = 0; x < width_2; x++) {
                // we need two pixels of Y
                Y1 = *y_ptr; y_ptr++;
                Y2 = *y_ptr; y_ptr++;

                // only one pixel of U and V (half the size of Y)
                U = u_ptr[x];
                V = v_ptr[x];

                D = (U - 128);
                E = (V - 128);

                // first pixel
                C = (Y1 - 16) * 298;

                R = ((C + 409 * E + 128) >> 8);
                G = ((C - 100 * D - 208 * E + 128) >> 8);
                B = ((C + 516 * D + 128) >> 8);

                CLAMP(R, 0, 255);
                CLAMP(G, 0, 255);
                CLAMP(B, 0, 255);

                *pix++ = (ubyte)B;
                *pix++ = (ubyte)G;
                *pix++ = (ubyte)R;

                // second pixel (U and V values are resused)
                C = (Y2 - 16) * 298;

                R = ((C + 409 * E + 128) >> 8);
                G = ((C - 100 * D - 208 * E + 128) >> 8);
                B = ((C + 516 * D + 128) >> 8);

                CLAMP(R, 0, 255);
                CLAMP(G, 0, 255);
                CLAMP(B, 0, 255);

                *pix++ = (ubyte)B;
                *pix++ = (ubyte)G;
                *pix++ = (ubyte)R;
            }

            y_ptr += (state->currentFrame->ySize.stride - state->currentFrame->ySize.width);

            // u and v have to be done every other row (it's a 2x2 block)
            if (y % 2) {
                u_ptr += state->currentFrame->uvSize.stride;
                v_ptr += state->currentFrame->uvSize.stride;
            }
        }
    }

    void uploadVideoFrameData(PlayerState* state)
    {
        if (!state->useShaders)
        {
            convert_YUV_to_RGB(state);
        }

        if (gr_screen.mode == GR_OPENGL)
        {
            if (state->useShaders)
            {
                auto ptrs = state->currentFrame->getDataPointers();

                GL_state.Texture.SetActiveUnit(0);
                glPixelStorei(GL_UNPACK_ROW_LENGTH, state->currentFrame->ySize.stride);
                glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0,
                    state->currentFrame->ySize.width, state->currentFrame->ySize.height,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, ptrs.y);

                GL_state.Texture.SetActiveUnit(1);
                glPixelStorei(GL_UNPACK_ROW_LENGTH, state->currentFrame->uvSize.stride);
                glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0,
                    state->currentFrame->uvSize.width, state->currentFrame->uvSize.height,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, ptrs.u);

                GL_state.Texture.SetActiveUnit(2);
                glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0,
                    state->currentFrame->uvSize.width, state->currentFrame->uvSize.height,
                    GL_LUMINANCE, GL_UNSIGNED_BYTE, ptrs.v);

                // Reset this back to default
                glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            }
            else
            {
                glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0, state->props.size.width, state->props.size.height, GL_BGR, GL_UNSIGNED_BYTE, state->pixelbuf);
            }
        }
    }

    void processVideoData(PlayerState* state)
    {
        if (!state->currentFrame)
        {
            // Load the initial frame
            VideoFramePtr firstFrame;
            auto r = state->decoder->tryPopVideoFrame(firstFrame);

            // This shouldn't happen...
            Assertion(r, "Failed to pop frame!");

            state->currentFrame = firstFrame;
            uploadVideoFrameData(state);

            return;
        }

        if (!state->decoder->isVideoFrameAvailable())
        {
            // Nothing to do here...
            return;
        }

        // Make sure playbackGetTime gets called after the first popVideoFrame to make sure
        // the decoder actually started decoding
        auto currentTime = playbackGetTime(state);
        auto newFrame = false;
        VideoFramePtr videoFrame;
        while (currentTime > state->currentFrame->frameTime && state->decoder->tryPopVideoFrame(videoFrame))
        {
            state->currentFrame = videoFrame;
            newFrame = true;
        }

        if (newFrame)
        {
            // Avoid multiple frame uploads
            uploadVideoFrameData(state);
        }
    }

    void processAudioData(PlayerState* state)
    {
        ALint processed;
        OpenAL_ErrorCheck(alGetSourcei(state->audioSid, AL_BUFFERS_PROCESSED, &processed), return);

        // First check for free buffers and push them int the audio queue
        for (int i = 0; i < processed; ++i)
        {
            ALuint buffer;
            OpenAL_ErrorPrint(alSourceUnqueueBuffers(state->audioSid, 1, &buffer));
            state->unqueuedAudioBuffers.push(buffer);
        }

        AudioFramePtr audioData;

        while (!state->unqueuedAudioBuffers.empty() && state->decoder->tryPopAudioData(audioData))
        {
            auto buffer = state->unqueuedAudioBuffers.front();
            state->unqueuedAudioBuffers.pop();

            ALenum format = (audioData->channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;

            OpenAL_ErrorCheck(alBufferData(buffer, format, audioData->audioData.data(), audioData->audioData.size() * sizeof(short), audioData->rate), return);

            OpenAL_ErrorCheck(alSourceQueueBuffers(state->audioSid, 1, &buffer), return);
        }

        ALint status, queued;
        OpenAL_ErrorCheck(alGetSourcei(state->audioSid, AL_SOURCE_STATE, &status), return);

        OpenAL_ErrorCheck(alGetSourcei(state->audioSid, AL_BUFFERS_QUEUED, &queued), return);

        if ((status != AL_PLAYING) && (queued > 0))
            OpenAL_ErrorPrint(alSourcePlay(state->audioSid));
    }

    void audioPlaybackClose(PlayerState* state)
    {
        if (!state->audioInited)
            return;

        ALint p = 0;

        OpenAL_ErrorPrint(alSourceStop(state->audioSid));
        OpenAL_ErrorPrint(alGetSourcei(state->audioSid, AL_BUFFERS_PROCESSED, &p));
        OpenAL_ErrorPrint(alSourceUnqueueBuffers(state->audioSid, p, state->audioBuffers.data()));
        OpenAL_ErrorPrint(alDeleteSources(1, &state->audioSid));

        for (auto buffer : state->audioBuffers)
        {
            // make sure that the buffer is real before trying to delete, it could crash for some otherwise
            if ((buffer != 0) && alIsBuffer(buffer)) {
                OpenAL_ErrorPrint(alDeleteBuffers(1, &buffer));
            }
        }

        state->audioInited = false;
    }

    void videoPlaybackClose(PlayerState* state)
    {
        if (!state->videoInited) {
            return;
        }

        if (gr_screen.mode == GR_OPENGL) {
            GL_state.Array.DisableClientVertex();
            GL_state.Array.DisableClientTexture();

            if (state->scaleVideo) {
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
            }

            GL_state.Texture.Disable();
            if (state->useShaders) {
                GL_state.Texture.Delete(state->ytex);
                GL_state.Texture.Delete(state->utex);
                GL_state.Texture.Delete(state->vtex);
                glDeleteTextures(1, &state->ytex);
                glDeleteTextures(1, &state->utex);
                glDeleteTextures(1, &state->vtex);
            }
            else {
                GL_state.Texture.Delete(state->GLtex);
                glDeleteTextures(1, &state->GLtex);
            }
            opengl_set_texture_target();

            state->ytex = state->utex = state->vtex = 0;
            state->GLtex = 0;
            GL_state.Texture.SetShaderMode(GL_FALSE);
            opengl_shader_set_current(0);
        }

        if (state->pixelbuf != NULL) {
            vm_free(state->pixelbuf);
            state->pixelbuf = NULL;
        }

        state->videoInited = 0;
        state->pixelbuf = NULL;
    }

    void displayVideo(PlayerState* state)
    {
        if (!state->currentFrame)
        {
            return;
        }

        if (gr_screen.mode == GR_OPENGL)
        {
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
    }

    void processEvents(PlayerState* state)
    {
        io::mouse::CursorManager::get()->showCursor(false);
        gr_flip();
        os_poll();

        int k = key_inkey();
        switch (k) {
            case KEY_ESC:
            case KEY_ENTER:
            case KEY_SPACEBAR:
                state->playing = false;
                break;

            case KEY_S:
                state->doSleep = !state->doSleep;
                break;
        }
    }
}

namespace cutscene
{
    Player::Player()
    {
    }

    Player::~Player()
    {
        if (m_decoder)
        {
            m_decoder->close();
        }
    }

    void Player::processDecoderData(PlayerState* state)
    {
        if (!state->playbackHasBegun)
        {
            // Wait until video and audio are available
            // If we don't have audio, don't wait for it (obviously...)
            if (!state->decoder->isVideoFrameAvailable() ||
                !(state->decoder->isAudioFrameAvailable() || !state->decoder->hasAudio()))
            {
                return;
            }

            state->playbackHasBegun = true;
        }

        processVideoData(state);

        processAudioData(state);

        // Set the playing flag if the decoder is still active and there is still data available
        state->playing = m_decoder->isDecoding() ||
            ((m_decoder->isAudioFrameAvailable() || !m_decoder->hasAudio()) ||
            m_decoder->isVideoFrameAvailable());
    }

    void Player::startPlayback()
    {
        m_decoderThread = std::make_unique<boost::thread>(std::bind(&Player::decoderThread, this));

        PlayerState state;
        state.props = m_decoder->getProperties();
        state.decoder = m_decoder.get();

        // Compute the maximum time we will sleep to make sure we can still maintain the movie FPS
        // and not waste too much CPU time
        // We will sleep at most hald the time a frame would be displayed
        auto sleepTime = static_cast<int>((1. / (4. * state.props.fps)) * 1000.);

        videoPlaybackInit(&state);
        audioPlaybackInit(&state);

        while (state.playing)
        {
            processDecoderData(&state);

            displayVideo(&state);

            processEvents(&state);

            auto passed = timer_get_milliseconds() - state.lastDisplayTimestamp;

            if (state.doSleep && passed < sleepTime)
            {
                auto sleep = sleepTime - passed;
                CLAMP(sleep, 0, sleepTime);

                os_sleep(sleep);
            }

            state.lastDisplayTimestamp = timer_get_milliseconds();
        }
        m_decoder->stopDecoder();

        audioPlaybackClose(&state);
        videoPlaybackClose(&state);

        m_decoderThread->join();
    }

    void Player::decoderThread()
    {
        m_decoder->startDecoding();
    }

    std::unique_ptr<Player> Player::newPlayer(const SCP_string& name)
    {
        auto decoder = findDecoder(name);

        if (decoder == nullptr)
        {
            return nullptr;
        }

        auto player = std::make_unique<Player>();
        player->m_decoder.reset(decoder);

        return player;
    }
}
