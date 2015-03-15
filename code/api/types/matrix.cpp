
#include "api/types/matrix.h"
#include "math/vecmat.h"

namespace api
{
    namespace types
    {
        matrix::matrix(const ::matrix& other) : content(other)
        {
        }

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
    }
}
