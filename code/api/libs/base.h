#pragma once

#include "api/types/vector.h"
#include "api/types/matrix.h"
#include "api/types/enum.h"
#include "api/types/gameevent.h"

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

            static const char* getCurrentMPStatus();

            static const char* setControlMode(const types::luaenum& e);
            static const char* setControlMode();

            static const char* setButtonControlMode();
            static const char* setButtonControlMode(const types::luaenum& e);

            static void setTips(bool enable);

            class GameEvents : public library
            {
            public:
                ~GameEvents() {}

                static types::gameevent byName(const char* key);
                static types::gameevent byIndex(int index);

                static size_t len();
            };

            static luabind::scope registerScope();
        };
    }
}