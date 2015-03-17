
#include <luabind/object.hpp>
#include <luabind/lua_state_fwd.hpp>

#include "globalincs/pstypes.h"

#include "api/types/types.h"
#include "api/types/matrix.h"

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

            void getScreenCoords(lua_State* L, luabind::object* outX, luabind::object* outY) const;

            vector getNormalized() const;

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