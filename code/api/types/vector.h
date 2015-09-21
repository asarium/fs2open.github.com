#pragma once

#include "globalincs/pstypes.h"

#include "api/types/types.h"

#include <luabind/object.hpp>
#include <luabind/luabind.hpp>

namespace api
{
    namespace types
    {
        class matrix;

        /**
         *
         *
         * @ingroup GRP_SCRIPTING_API_TYPES
         */
        class vector
        {
        public:
        	/**
        	 * @notscriptingapi
        	 * @param vec The vec3d value
        	 */
            explicit vector(const vec3d& vec);

            /**
             * @brief Construct a new vector
             * @param x The X value
             * @param y The Y value
             * @param z The Z value
             */
            vector(float x, float y, float z);

            /**
             * @brief Returns orientation object representing the direction of the vector. Does not require vector to be normalized.
             * @return Orientation object, or null orientation object if handle is invalid
             */
            types::matrix getOrientation() const;

            /**
             * @brief Returns the magnitude of a vector (Total regardless of direction)
             * @return Magnitude of vector, or 0 if handle is invalid
             */
            float getMagnitude() const;

            /**
             * @brief Distance from other position
             * @param other The other vector
             * @return The distance
             */
            float getDistance(const vector& other) const;

            /**
             * @brief Returns dot product of vector object with vector argument
             * @param other The other vector
             * @return Dot product, or 0 if a handle is invalid
             */
            float getDotProduct(const vector& other) const;
			/**
			 * @brief Returns cross product of vector object with vector argument
			 * @param other The other vector
			 * @return Cross product, or null vector if a handle is invalid
			 */
            vector getCrossProduct(const vector& other) const;

            /**
             * @brief Gets screen coordinates of a world vector
             * The Lua function takes no parameters and returns two numbers (x, y)
             * @param L
             * @param outX
             * @param outY
             */
            void getScreenCoords(lua_State* L, luabind::object* outX, luabind::object* outY) const;

            /**
             * @brief Returns a normalized version of the vector
             * @return The normalized vector
             */
            vector getNormalized() const;

            /**
             * @brief Adds vector by another vector
             * @param other The other vector
             * @return The new vector
             */
            vector operator+(const vector& other) const;
            /**
             * @brief Adds value to all axes
             * @param other The value
             * @return The new vector
             */
            vector operator+(float val) const;

            /**
             * @brief Substracts vector from another vector
             * @param other The other vector
             * @return The new vector
             */
            vector operator-(const vector& other) const;
            /**
             * @brief Substracts value from all axes
             * @param other The value
             * @return The new vector
             */
            vector operator-(float val) const;

            /**
             * @brief Multiplies each axes by the other vector's axes.
             * @param other The other vector
             * @return The new vector
             */
            vector operator*(const vector& other) const;
            /**
             * @brief Scales vector object (Multiplies all axes by number)
             * @param other The value
             * @return The new vector
             */
            vector operator*(float val) const;

            /**
             * @brief Divides each axes by the other vector's axes.
             * @param other The other vector
             * @return The new vector
             */
            vector operator/(const vector& other) const;
            /**
             * @brief Scales vector object (Divides all axes by number)
             * @param other The value
             * @return The new vector
             */
            vector operator/(float val) const;

            /**
             * @brief Accesses a value of the vector
             * @param axis The name of the axis "x", "y" or "z"
             * @return The axis value
             */
            float operator[](const char* axis) const;
            /**
             * @brief Retrieves a reference to an axis value
             * In Lua this operator is accessible via __newindex (e.g. v.x = y)
             * @param axis The name of the axis "x", "y" or "z"
             * @return An axis reference
             */
            float& operator[](const char* axis);

            /**
             * @brief Accesses a value of the vector
             * @param axis The index of the axis (1-3)
             * @return The axis value
             */
            float operator[](int axis) const;
            /**
             * @brief Retrieves a reference to an axis value
             * In Lua this operator is accessible via __newindex (e.g. v[1] = y)
             * @param axis The index of the axis (1-3)
             * @return An axis reference
             */
            float& operator[](int axis);

            /**
             * The actual vector values
             * @notscriptingapi
             */
            vec3d content;

            /**
             * @notscriptingapi
             */
            static luabind::scope registerScope();
        };
    }
}
