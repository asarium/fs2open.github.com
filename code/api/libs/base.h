#pragma once

#include <string>

#include "api/libs/libs.h"
#include "api/types/vector.h"

namespace api
{
    namespace libs
    {
        class base
        {
        public:
            static void print(const char* msg);

            static void warning(const char* msg);

            static void error(const char* msg);

            static types::vector createVector(float a, float b, float c);

            static luabind::scope registerScope();
        };
    }
}