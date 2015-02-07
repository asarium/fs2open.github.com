
#pragma once

#include <memory>

#include "globalincs/pstypes.h"

#include "SDL_thread.h"
#include "SDL_mutex.h"

namespace cutscene
{
    class Decoder;
    struct PlayerState;
    
    class Player
    {
    private:
        std::unique_ptr<Decoder> m_decoder;

        SDL_Thread *m_decoderThread;

        void processDecoderData(PlayerState* state);

    private:
        Player(const Player&) = delete;

    public:
        Player();
        ~Player();

        void startPlayback();

        void decoderThread();

        static std::unique_ptr<Player> newPlayer(const SCP_string& name);
    };
}
