#pragma once

#include "globalincs/pstypes.h"

#include "api/types/types.h"
#include "api/types/vector.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class vector;

        class matrix
        {
        public:
            explicit matrix(const ::matrix&);

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

            matrix getInterpolated(const matrix& final, float factor) const;

            matrix getTranspose() const;

            vector rotateVector(const vector& v) const;
            vector unrotateVector(const vector& v) const;

            vector getUvec() const;
            vector getFvec() const;
            vector getRvec() const;

            ::matrix content;

            static luabind::scope registerScope();
        };
    }
}