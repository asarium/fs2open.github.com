
#include <exception>

#include "api/types/matrix.h"
#include "api/types/vector.h"

#include "math/vecmat.h"

#include <luabind/operator.hpp>

namespace
{
    std::ostream& operator<<(std::ostream& out, const api::types::matrix& m)
    {
        const float* a = &m.content.a1d[0];
        out << "[" << a[0] << " " << a[1] << " " << a[2] << " | ";
        out << a[3] << " " << a[4] << " " << a[5] << " | ";
        out << a[6] << " " << a[7] << " " << a[8] << "]";

        return out;
    }

    float getMatrixInt(const api::types::matrix& m, int i)
    {
        return m[i];
    }
    float getMatrixStr(const api::types::matrix& m, const char* name)
    {
        return m[name];
    }
}

namespace api
{
    namespace types
    {
        matrix::matrix(const ::matrix& other) : content(other)
        {}

        matrix::matrix() : content(vmd_identity_matrix)
        {}

        matrix::matrix(float p, float b, float h)
        {
            angles a = { p, b, h };
            vm_angles_2_matrix(&content, &a);
        }

        matrix::matrix(float r1c1, float r1c2, float r1c3,
            float r2c1, float r2c2, float r2c3,
            float r3c1, float r3c2, float r3c3)
        {
            content.a1d[0] = r1c1;
            content.a1d[1] = r1c2;
            content.a1d[2] = r1c3;

            content.a1d[3] = r2c1;
            content.a1d[4] = r2c2;
            content.a1d[5] = r2c3;

            content.a1d[6] = r3c1;
            content.a1d[7] = r3c2;
            content.a1d[8] = r3c3;
        }

        matrix matrix::operator*(const matrix& other) const
        {
            ::matrix m;
            vm_matrix_x_matrix(&m, &content, &other.content);

            return matrix(m);
        }

        vector matrix::operator*(const vector& vec) const
        {
            vec3d dest;
            vm_vec_rotate(&dest, &vec.content, &content);

            return vector(dest);
        }

        float matrix::operator[](int i) const
        {
            if (i < 1 || i > 9)
            {
                throw std::runtime_error("Invalid axis index!");
            }

            return content.a1d[i - 1];
        }
        float matrix::operator[](const char* name) const
        {
            if (name == nullptr)
            {
                throw std::runtime_error("Invalid axis name!");
            }

            angles ang;
            vm_extract_angles_matrix(&ang, &content);

            switch (*name)
            {
            case 'p':
                return ang.p;
            case 'b':
                return ang.b;
            case 'h':
                return ang.h;
            default:
                throw std::runtime_error("Invalid axis name!");
            }
        }

        void matrix::setValue(int i, float val)
        {
            if (i < 1 || i > 9)
            {
                throw std::runtime_error("Invalid axis index!");
            }

            content.a1d[i - 1] = val;
        }
        void matrix::setAngle(const char* name, float val)
        {
            if (name == nullptr)
            {
                throw std::runtime_error("Invalid axis name!");
            }

            angles ang;
            vm_extract_angles_matrix(&ang, &content);

            switch (*name)
            {
            case 'p':
                ang.p = val;
                break;
            case 'b':
                ang.b = val;
                break;
            case 'h':
                ang.h = val;
                break;
            default:
                throw std::runtime_error("Invalid axis name!");
            }

            // Write the changes back to the matrix
            vm_angles_2_matrix(&content, &ang);
        }

        luabind::scope matrix::registerScope()
        {
            using namespace luabind;

            return class_<matrix>("matrix")
                .def(constructor<>())
                .def(constructor<float, float, float>())
                .def(constructor<float, float, float, float, float, float, float, float, float>())
                
                .defaultGet(&getMatrixInt)
                .defaultGet(&getMatrixStr)

                .defaultSet(&matrix::setValue)
                .defaultSet(&matrix::setAngle)

                .def(const_self * other<matrix>())
                .def(const_self * other<vector>())

                .def(tostring(const_self));
        }
    }
}
