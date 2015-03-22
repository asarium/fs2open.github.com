
#pragma once

#include <memory>

#include <boost/thread/thread.hpp>

#include "globalincs/pstypes.h"

namespace cutscene
{
    class Decoder;
    struct PlayerState;
    
    class Player
    {
    private:
        std::unique_ptr<Decoder> m_decoder;

        std::unique_ptr<boost::thread> m_decoderThread;

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
