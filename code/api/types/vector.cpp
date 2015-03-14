
#include "api/types/vector.h"
#include "math/vecmat.h"

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

namespace api
{
    namespace types
    {
        vector::vector(const vec3d& vec) : content(vec)
        {
        }

        vector::vector(float x, float y, float z)
        {
            content.xyz.x = x;
            content.xyz.y = y;
            content.xyz.z = z;
        }

        vector vector::operator+(const vector& other) const
        {
            vec3d res;
            vm_vec_add(&res, &this->content, &other.content);

            return vector(res);
        }
        vector vector::operator+(float x) const
        {
            vec3d res = content;
            res.xyz.x += x;
            res.xyz.y += x;
            res.xyz.z += x;

            return vector(res);
        }

        vector vector::operator-(const vector& other) const
        {
            vec3d res;
            vm_vec_sub(&res, &this->content, &other.content);

            return vector(res);
        }
        vector vector::operator-(float x) const
        {
            vec3d res = content;
            res.xyz.x -= x;
            res.xyz.y -= x;
            res.xyz.z -= x;

            return vector(res);
        }

        vector vector::operator*(const vector& other) const
        {
            vec3d res;
            res.xyz.x = content.xyz.x * other.content.xyz.x;
            res.xyz.y = content.xyz.y * other.content.xyz.y;
            res.xyz.z = content.xyz.z * other.content.xyz.z;

            return vector(res);
        }
        vector vector::operator*(float x) const
        {
            vec3d res = content;
            vm_vec_scale(&res, x);

            return vector(res);
        }

        vector vector::operator / (const vector& other) const
        {
            vec3d res;
            res.xyz.x = content.xyz.x / other.content.xyz.x;
            res.xyz.y = content.xyz.y / other.content.xyz.y;
            res.xyz.z = content.xyz.z / other.content.xyz.z;

            return vector(res);
        }
        vector vector::operator / (float x) const
        {
            vec3d res = content;
            vm_vec_scale(&res, 1.f / x);

            return vector(res);
        }

        luabind::scope vector::registerScope()
        {
            using namespace luabind;

            return class_<vector>("vector")
                .def(constructor<float, float, float>())

                // Properties
                .property("x", &vector::setX, &vector::getX)
                .property("y", &vector::setY, &vector::getY)
                .property("z", &vector::setZ, &vector::getZ)

                // Operators
                .def(const_self + other<vector>())
                .def(const_self - other<vector>())
                .def(const_self * other<vector>())
                .def(const_self / other<vector>())
                .def(const_self + float())
                .def(const_self - float())
                .def(const_self * float())
                .def(const_self / float());
        }
    }
}
