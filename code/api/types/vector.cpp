
#include <ostream>
#include <exception>

#include "api/types/vector.h"
#include "math/vecmat.h"

#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>

namespace
{
    using namespace api::types;

    std::ostream& operator<<(std::ostream& out, const vector& v)
    {
        out << "(" << v.content.xyz.x << "," << v.content.xyz.y << "," << v.content.xyz.z << ")";
        return out;
    }

    int translateAxisName(const char* name)
    {
        if (name == nullptr)
        {
            throw std::runtime_error("Invalid axis name!");
        }

        if (std::strlen(name) <= 0)
        {
            throw std::runtime_error("Invalid axis name!");
        }

        switch (*name)
        {
        case 'x':
            return 1;
        case 'y':
            return 2;
        case 'z':
            return 3;
        default:
            throw std::runtime_error("Invalid axis name!");
        }
    }

    float getVectorInt(const vector& v, int i)
    {
        return v[i];
    }
    float getVectorStr(const vector& v, const char* name)
    {
        return v[name];
    }

    void setVectorInt(vector& v, int i, float newVal)
    {
        v[i] = newVal;
    }
    void setVectorStr(vector& v, const char* name, float newVal)
    {
        v[name] = newVal;
    }
}

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

        float vector::operator[](const char* name) const
        {
            return (*this)[translateAxisName(name)];
        }
        float& vector::operator[](const char* name)
        {
            return (*this)[translateAxisName(name)];
        }

        float vector::operator[](int i) const
        {
            if (i < 1 || i > 3)
            {
                throw std::runtime_error("Invalid axis index!");
            }

            return content.a1d[i - 1];
        }
        float& vector::operator[](int i)
        {
            if (i < 1 || i > 3)
            {
                throw std::runtime_error("Invalid axis index!");
            }

            return content.a1d[i - 1];
        }

        luabind::scope vector::registerScope()
        {
            using namespace luabind;

            return class_<vector>("vector")
                .def(constructor<float, float, float>())

                .defaultGet(&getVectorInt)
                .defaultGet(&getVectorStr)

                .defaultSet(&setVectorInt)
                .defaultSet(&setVectorStr)

                // Operators
                .def(const_self + other<vector>())
                .def(const_self - other<vector>())
                .def(const_self * other<vector>())
                .def(const_self / other<vector>())
                .def(const_self + float())
                .def(const_self - float())
                .def(const_self * float())
                .def(const_self / float())
                
                .def(tostring(const_self));
        }
    }
}
