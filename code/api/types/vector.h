
#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace api
{
    namespace types
    {
        class vector
        {
            vec3d content;

        public:
            vector(const vec3d& vec);
            vector(float x, float y, float z);

            float getX() const { return content.xyz.x; }
            void setX(float x) { content.xyz.x = x; }

            float getY() const { return content.xyz.y; }
            void setY(float y) { content.xyz.y = y; }

            float getZ() const { return content.xyz.z; }
            void setZ(float z) { content.xyz.z = z; }

            vector operator+(const vector&) const;
            vector operator+(float) const;

            vector operator-(const vector&) const;
            vector operator-(float) const;

            vector operator*(const vector&) const;
            vector operator*(float) const;

            vector operator/(const vector&) const;
            vector operator/(float) const;

            static luabind::scope registerScope();
        };
    }
}