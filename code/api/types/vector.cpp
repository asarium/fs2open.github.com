
#include <ostream>
#include <exception>

#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>
#include <luabind/out_value_policy.hpp>

#include "api/types/vector.h"
#include "api/types/matrix.h"

#include "math/vecmat.h"
#include "render/3d.h"
#include "render/3dinternal.h"

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
        using namespace luabind;

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

        matrix vector::getOrientation() const
        {
            ::matrix mt = vmd_identity_matrix;
            vec3d v3 = content;

            vm_vec_normalize_safe(&v3);
            vm_vector_2_matrix_norm(&mt, &v3);

            return types::matrix(mt);
        }

        float vector::getMagnitude() const
        {
            return vm_vec_mag(&content);
        }

        float vector::getDistance(const vector& other) const
        {
            return vm_vec_dist(&content, &other.content);
        }

        float vector::getDotProduct(const vector& other) const
        {
            return vm_vec_dotprod(&content, &other.content);
        }

        vector vector::getCrossProduct(const vector& other) const
        {
            vec3d out;
            vm_vec_crossprod(&out, &content, &other.content);

            return vector(out);
        }

        void vector::getScreenCoords(lua_State* L, luabind::object* outX, luabind::object* outY) const
        {            
            vertex vtx;
            bool do_g3 = G3_count < 1;
            if (do_g3)
                g3_start_frame(1);

            g3_rotate_vertex(&vtx, &content);
            g3_project_vertex(&vtx);

            if (do_g3)
                g3_end_frame();

            if (vtx.flags & PF_OVERFLOW)
            {
                *outX = luabind::object(L, false);

                lua_pushnil(L);
                *outY = luabind::object(handle(L, -1));
                lua_pop(L, 1);
            }
            else
            {
                *outX = luabind::object(L, vtx.screen.xyw.x);
                *outY = luabind::object(L, vtx.screen.xyw.y);
            }
        }

        vector vector::getNormalized() const
        {
            vec3d out = content;
            vm_vec_normalize(&out);

            return vector(out);
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
            return class_<vector>("vector")
                .def(constructor<float, float, float>())

                .defaultGet(&getVectorInt)
                .defaultGet(&getVectorStr)

                .defaultSet(&setVectorInt)
                .defaultSet(&setVectorStr)

                // Normal operations
                .def("getOrientation", &vector::getOrientation)
                .def("getMagnitude", &vector::getMagnitude)
                .def("getDistance", &vector::getDistance)
                .def("getDotProduct", &vector::getDotProduct)
                .def("getCrossProduct", &vector::getCrossProduct)
                .def("getScreenCoords", &vector::getScreenCoords, pure_out_value(_3) + pure_out_value(_4))
                .def("getNormalized", &vector::getNormalized)

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
