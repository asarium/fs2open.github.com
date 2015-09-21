#pragma once

#include "globalincs/pstypes.h"

#include "api/types/vector.h"

#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class vector;

        /**
         * 3x3 Matrix object (commonly used for orientations)
         *
         * @ingroup GRP_SCRIPTING_API_TYPES
         */
        class matrix
        {
        public:
        	/**
        	 * Constructs a new API matrix object
        	 * @notscriptingapi
        	 * @param The underlying matrix
        	 */
            explicit matrix(const ::matrix&);

            /**
             * @brief Initializes the matrix with the identity matrix
             */
            matrix();
            /**
             * @brief Initializes the matrix from pitch bank and heading
             * @param p Pitch
             * @param b Bank
             * @param h Heading
             */
            matrix(float, float, float);
            /**
             * @brief Fully initializes the matrix
             * @param r1c1 Value for 1x1
             * @param r1c2 Value for 1x2
             * @param r1c3 Value for 1x3
             * @param r2c1 Value for 2x1
             * @param r2c2 Value for 2x2
             * @param r2c3 Value for 2x3
             * @param r3c1 Value for 3x1
             * @param r3c2 Value for 3x2
             * @param r3c3 Value for 3x3
             */
            matrix(float, float, float,
                float, float, float,
                float, float, float);

            /**
             * @brief Executes a matrix multiplication
             * @param The matrix to multiply with
             * @return matrix, or empty matrix if unsuccessful
             */
            matrix operator*(const matrix&) const;
            /**
             * @brief Multiplies a vector with this matrix
             * @param The vector
             * @return The result of the operation
             */
            vector operator*(const vector&) const;

            /**
             * @brief Gets value at specified index
             * @param index into 3x3 matrix (1-9)
             * @return The value
             */
            float operator[](int) const;
            /**
             * @brief Gets value at specified index
             * @param "p", "b" or "h" for pitch, bank or heading
             * @return The value
             */
            float operator[](const char*) const;

            /**
             * @brief Sets a value of the matrix
             * @param Matrix index
             * @param New value
             *
             * @note This function is exposed via the lua __newindex (a.x = y) operator
             */
            void setValue(int, float);
            /**
             * @brief Sets a value of the matrix
             * @param "p", "b" or "h" for pitch, bank or heading
             * @param New value
             *
             * @note This function is exposed via the lua __newindex (a.x = y) operator
             */
            void setAngle(const char*, float);

            /**
             * @brief Returns matrix that has been interpolated to Final by Factor (0.0-1.0) (only makes sense for orientation matrices)
             * @param final The other atrix
             * @param factor The interpolation factor
             * @return Interpolated orientation, or null orientation on failure
             */
            matrix getInterpolated(const matrix& final, float factor) const;

            /**
             * @brief Returns a transpose version of the specified orientation
             * @return Transpose matrix, or null orientation on failure
             */
            matrix getTranspose() const;

            /**
             * @brief Returns rotated version of given vector
             * @param v The vector to rotate
             * @return Rotated vector, or empty vector on error
             */
            vector rotateVector(const vector& v) const;
            /**
             * @brief Returns unrotated version of given vector
             * @param v The vector to unrotate
             * @return Unrotated vector, or empty vector on error
             */
            vector unrotateVector(const vector& v) const;

            /**
             * @brief Returns the vector that points up (0,1,0 unrotated by this matrix)
             * @return Vector or null vector on error
             */
            vector getUvec() const;
            /**
             * @brief Returns the vector that points to the front (0,0,1 unrotated by this matrix)
             * @return Vector or null vector on error
             */
            vector getFvec() const;
            /**
             * @brief Returns the vector that points to the right (1,0,0 unrotated by this matrix)
             * @return Vector or null vector on error
             */
            vector getRvec() const;

            /**
             * @brief The actual matrix
             *
             * @notscriptingapi
             */
            ::matrix content;

            /**
             * @notscriptingapi
             */
            static luabind::scope registerScope();
        };
    }
}
