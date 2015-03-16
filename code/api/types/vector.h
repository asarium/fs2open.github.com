
#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace api
{
    namespace types
    {
        class vector
        {
        public:
            explicit vector(const vec3d& vec);
            vector(float x, float y, float z);

            vector operator+(const vector&) const;
            vector operator+(float) const;

            vector operator-(const vector&) const;
            vector operator-(float) const;

            vector operator*(const vector&) const;
            vector operator*(float) const;

            vector operator/(const vector&) const;
            vector operator/(float) const;

            float operator[](const char*) const;
            float& operator[](const char*);

            float operator[](int) const;
            float& operator[](int);

            vec3d content;

            static luabind::scope registerScope();
        };
    }
}