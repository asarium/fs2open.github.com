
#include "globalincs/pstypes.h"

#include "api/types/types.h"

namespace api
{
    namespace types
    {
        class matrix;
        class vector
        {
        public:
            explicit vector(const vec3d& vec);
            vector(float x, float y, float z);

            matrix getOrientation() const;

            float getMagnitude() const;

            float getDistance(const vector& other) const;

            float getDotProduct(const vector& other) const;

            vector getCrossProduct(const vector& other) const;

            vector operator+(const vector& other) const;
            vector operator+(float val) const;

            vector operator-(const vector& other) const;
            vector operator-(float val) const;

            vector operator*(const vector& other) const;
            vector operator*(float val) const;

            vector operator/(const vector& other) const;
            vector operator/(float val) const;

            float operator[](const char* axis) const;
            float& operator[](const char* axis);

            float operator[](int axis) const;
            float& operator[](int axis);

            vec3d content;

            static luabind::scope registerScope();
        };
    }
}