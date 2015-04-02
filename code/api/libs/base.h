#pragma once

#include <string>

#include "api/libs/libs.h"

#include "api/types/vector.h"
#include "api/types/matrix.h"
#include "api/types/enum.h"

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

                static const char* getByName(const char* key);
                static const char* getByIndex(int index);
            };

            static luabind::scope registerScope();
        };
    }
}