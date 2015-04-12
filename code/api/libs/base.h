#pragma once

#include "api/types/vector.h"
#include "api/types/matrix.h"
#include "api/types/enum.h"
#include "api/types/gameevent.h"
#include "api/types/gamestate.h"
#include "api/types/player.h"

namespace api
{
    namespace libs
    {
        class base : public library
        {
        public:
            ~base() {}

            static void print(const char* msg);

            static void warning(const char* msg);

            static void error(const char* msg);

            static types::vector createVector(float, float, float);

            static types::matrix createOrientation(float, float, float, float, float, float, float, float, float);

            static float getFrametime(bool adjustForTimeCompression);

            static types::gamestate getCurrentGameState(int depth);

            static const char* getCurrentMPStatus();

            static const char* setControlMode(const types::luaenum& e);
            static const char* setControlMode();

            static const char* setButtonControlMode();
            static const char* setButtonControlMode(const types::luaenum& e);

            static void setTips(bool enable);

            static bool postGameEvent(const types::gameevent& event);

            static types::player getCurrentPlayer();

            class GameEvents : public library
            {
            public:
                ~GameEvents() {}

                static types::gameevent get(const char* key);
                static types::gameevent get(int index);

                static size_t count();
            };

            class GameStates : public library
            {
            public:
                ~GameStates() {}

                static types::gamestate get(const char* key);
                static types::gamestate get(int index);

                static size_t count();
            };

            static luabind::scope registerScope();
        };
    }
}