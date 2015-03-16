#pragma once

#include <string>

#include "api/libs/libs.h"

#include "api/types/vector.h"
#include "api/types/matrix.h"

namespace api
{
    namespace libs
    {
        class base
        {
        private:
            base() = delete;
            base(const base&) = delete;

        public:
            ~base() {}

            static void print(const char* msg);

            static void warning(const char* msg);

            static void error(const char* msg);

            static types::vector createVector(float, float, float);

            static types::matrix createOrientation(float, float, float, float, float, float, float, float, float);

            static luabind::scope registerScope();
        };
    }
}