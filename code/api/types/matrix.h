#pragma once

#include "globalincs/pstypes.h"

namespace api
{
    namespace types
    {
        class matrix
        {
        public:
            matrix(const ::matrix&);

            matrix();
            matrix(float, float, float);
            matrix(float, float, float,
                float, float, float,
                float, float, float);

        private:
            ::matrix content;
        };
    }
}