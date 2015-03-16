#pragma once

#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace api
{
    namespace types
    {
        class vector;

        class matrix
        {
        public:
            matrix(const ::matrix&);

            matrix();
            matrix(float, float, float);
            matrix(float, float, float,
                float, float, float,
                float, float, float);

            matrix operator*(const matrix&) const;
            vector operator*(const vector&) const;

            float operator[](int) const;
            float operator[](const char*) const;

            void setValue(int, float);
            void setAngle(const char*, float);

            ::matrix content;

            static luabind::scope registerScope();
        };
    }
}