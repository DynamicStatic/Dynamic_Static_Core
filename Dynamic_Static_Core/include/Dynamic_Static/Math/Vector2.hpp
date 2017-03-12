
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLM_VEC2(DST_VECTOR2) (*reinterpret_cast<glm::vec2*>(&DST_VECTOR2))
#define DST_TO_GLM_VEC2_CONST(DST_VECTOR2) (*reinterpret_cast<const glm::vec2*>(&DST_VECTOR2))

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of 2D vectors and points.
         */
        struct Vector2 {
            friend Vector2 operator+(const Vector2&, const Vector2&);
            friend Vector2 operator-(const Vector2&, const Vector2&);
            friend Vector2 operator*(const Vector2&, const Vector2&);
            friend Vector2 operator*(const Vector2&, float);
            friend Vector2 operator/(const Vector2&, const Vector2&);
            friend Vector2 operator/(const Vector2&, float);
        public:
            /**
             * Constant Vector2(1, 1).
             */
            static const Vector2 One;

            /**
             * Constant Vector2(0, 0).
             */
            static const Vector2 Zero;

            /**
             * Constant Vector2(0, 1).
             */
            static const Vector2 Up;

            /**
             * Constant Vector2(0, -1).
             */
            static const Vector2 Down;

            /**
             * Constant Vector2(-1, 0).
             */
            static const Vector2 Left;

            /**
             * Constant Vector2(1, 0).
             */
            static const Vector2 Right;

            /**
             * Constant Vector2(1, 0).
             */
            static const Vector2 UnitX;

            /**
             * Constant Vector2(0, 1).
             */
            static const Vector2 UnitY;

        public:
            union {
                std::array<float, 2> values;
                struct { float x, y; };
                struct { float r, g; };
                struct { float s, t; };
            };

        public:
            /**
             * Constructs an instance of Vector2.
             * @param [in] value The initial value for this Vector2's elements
             */
            inline Vector2(float value = 0)
                : Vector2(value, value)
            {
            }

            /**
             * Constructs an instance of Vector2.
             * @param [in] x This Vector2's x value
             * @param [in] y This Vector2's y value
             */
            inline Vector2(float x, float y)
            {
                values[0] = x;
                values[1] = y;
            }

            /**
             * Constructs an instance of Vector2.
             * @param [in] values An array containing this Vector2's values
             */
            inline Vector2(const float* values)
            {
                std::memcpy(this, values, sizeof(*this));
            }

            /**
             * Constructs an instance of Vector2.
             * @param [in] xy The Vector3 to copy the x and y elements from
             */
            Vector2(const Vector3& xy);

            /**
             * Constructs an instance of Vector2.
             * @param [in] xy The Vector4 to copy the x and y elements from
             */
            Vector2(const Vector4& xy);

            /**
             * Moves an instance of Vector2.
             * @param [in] other The Vector2 to move from
             */
            Vector2(Vector2&& other) = default;

            /**
             * Copies an instance of Vector2.
             * @param [in] other The Vector2 to copy from
             */
            Vector2(const Vector2& other) = default;

            /**
             * Moves an instance of Vector2.
             * @param [in] other The Vector2 to move from
             */
            Vector2& operator=(Vector2&& other) = default;

            /**
             * Copies an instance of Vector2.
             * @param [in] other The Vector4 to copy from
             */
            Vector2& operator=(const Vector2& other) = default;

            /**
             * Adds a specified Vector2 to this Vector2.
             * @param [in] other The Vector2 to add to this Vector2
             */
            inline Vector2& operator+=(const Vector2& other)
            {
                DST_TO_GLM_VEC2(*this) += DST_TO_GLM_VEC2_CONST(other);
                return *this;
            }

            /**
             * Subtracts a specified Vector2 from this Vector2.
             * @param [in] other The Vector2 to subtract from this Vector2
             */
            inline Vector2& operator-=(const Vector2& other)
            {
                DST_TO_GLM_VEC2(*this) -= DST_TO_GLM_VEC2_CONST(other);
                return *this;
            }

            /**
             * Multiplies this Vector2 by a specified Vector2.
             * @param [in] other The Vector2 to multiply this Vector2 by
             */
            inline Vector2& operator*=(const Vector2& other)
            {
                DST_TO_GLM_VEC2(*this) *= DST_TO_GLM_VEC2_CONST(other);
                return *this;
            }

            /**
             * Multiplies this Vector2 by a specified scalar.
             * @param [in] other The scalar to multiply this Vector2 by
             */
            inline Vector2& operator*=(float scalar)
            {
                DST_TO_GLM_VEC2(*this) *= scalar;
                return *this;
            }

            /**
             * Divides this Vector2 by a specified Vector2.
             * @param [in] other The Vector2 to divide this Vector2 by
             */
            inline Vector2& operator/=(const Vector2& other)
            {
                DST_TO_GLM_VEC2(*this) /= DST_TO_GLM_VEC2_CONST(other);
                return *this;
            }

            /**
             * Divides this Vector2 by a specified scalar.
             * @param [in] other The scalar to divide this Vector2 by
             */
            inline Vector2& operator/=(float scalar)
            {
                DST_TO_GLM_VEC2(*this) /= scalar;
                return *this;
            }

            /**
             * Gets the opposite of this Vector2.
             * @return The opposite of this Vector2
             */
            inline Vector2 operator-() const
            {
                return -DST_TO_GLM_VEC2_CONST(*this);
            }

            /**
             * Gets the value at the specified index.
             * @param [in] index The index of the value to get
             * @return The value at the specified index
             */
            inline float operator[](size_t index) const
            {
                return values[index];
            }

            /**
             * Gets the value at the specified index.
             * @param [in] index The index of the value to get
             * @return The value at the specified index
             */
            inline float& operator[](size_t index)
            {
                return values[index];
            }

            /**
             * Gets a pointer Vector2's underlying data.
             * @return A pointer to this Vector2's underlying data
             */
            inline const float* data() const
            {
                return values.data();
            }

        private:
            inline Vector2(const glm::vec2& other)
            {
                DST_TO_GLM_VEC2(*this) = other;
            }

        public:
            /**
             * Gets this Vector2's magnitude.
             */
            inline float magnitude() const
            {
                return glm::length(DST_TO_GLM_VEC2_CONST(*this));
            }

            /**
             * Gets this Vector2's magnitude squared.
             */
            inline float magnitude_squared() const
            {
                return glm::length2(DST_TO_GLM_VEC2_CONST(*this));
            }

            /**
             * Gets a normalized copy of this Vector2.
             * @return A normalized copy of this Vector2
             */
            inline Vector2 normalized() const
            {
                return glm::normalize(DST_TO_GLM_VEC2_CONST(*this));
            }

            /**
             * Normalizes this Vector2.
             */
            inline void normalize()
            {
                DST_TO_GLM_VEC2(*this) = glm::normalize(DST_TO_GLM_VEC2_CONST(*this));
            }

            /**
             * Gets the std::string representation of this Vector2.
             */
            inline std::string to_string() const
            {
                return 
                    "(" +
                    std::to_string(x) + ", " +
                    std::to_string(y) +
                    ")";
            }

            /**
             * Gets a Vector2 lineraly interpolated between two Vector2s by a specified weight.
             * @param [in] v0 The Vector2 to interpolate from
             * @param [in] v1 The Vector2 to interpolate towards
             * @param [in] s The weight of the interpolation
             * @return The result of the linear interpolation
             */
            static inline Vector2 lerp(const Vector2& v0, const Vector2& v1, float t)
            {
                return Vector2(
                    dst::lerp(v0.x, v1.x, t),
                    dst::lerp(v0.y, v1.y, t)
                );
            }
        };

        static_assert(
            sizeof(Vector2) == sizeof(float) * 2,
            "sizeof(Vector2) must equal sizeof(float) * 2"
        );

        /**
         * Gets a value indicating whether or not two specified Vector2s are equal.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @return whether or not the two specified Vector2s are equal
         */
        inline bool operator==(const Vector2 v0, const Vector2& v1)
        {
            return v0.values == v1.values;
        }

        /**
         * Gets a value indicating whether or two specified Vector2s are inequal.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @return whether or not the two specified Vector2s are inequal
         */
        inline bool operator!=(const Vector2 v0, const Vector2& v1)
        {
            return !(v0 == v1);
        }

        /**
         * Gets the result of addition between two Vector2s.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @param The result of addition between the Vector2s
         */
        inline Vector2 operator+(const Vector2& v0, const Vector2& v1)
        {
            return DST_TO_GLM_VEC2_CONST(v0) + DST_TO_GLM_VEC2_CONST(v1);
        }

        /**
         * Gets the result of subtracting a Vector2 from another.
         * @param [in] v0 The Vector2 to subtract from
         * @param [in] v1 The Vector2 to subtract
         * @return The result of subtraction between the Vector2s
         */
        inline Vector2 operator-(const Vector2& v0, const Vector2& v1)
        {
            return DST_TO_GLM_VEC2_CONST(v0) - DST_TO_GLM_VEC2_CONST(v1);
        }

        /**
         * Gets the result of multiplication between two Vector2s.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @param The result of multiplication between the Vector2s
         */
        inline Vector2 operator*(const Vector2& v0, const Vector2& v1)
        {
            return DST_TO_GLM_VEC2_CONST(v0) * DST_TO_GLM_VEC2_CONST(v1);
        }

        /**
         * Gets the result of multiplication between a Vector2 and a scalar
         * @param [in] v The Vector2
         * @param [in] scalar The scalar
         * @param The result of multiplication between the Vector2 and the scalar
         */
        inline Vector2 operator*(const Vector2& v, float scalar)
        {
            return DST_TO_GLM_VEC2_CONST(v) * scalar;
        }

        /**
         * Gets the result of dividing a Vector2 by another.
         * @param [in] v0 The Vector2 to divide
         * @param [in] v1 The Vector2 to divide by
         * @param The result of division between the Vector2s
         */
        inline Vector2 operator/(const Vector2& v0, const Vector2& v1)
        {
            return DST_TO_GLM_VEC2_CONST(v0) / DST_TO_GLM_VEC2_CONST(v1);
        }

        /**
         * Gets the result of dividing a Vector2 by a scalar
         * @param [in] v The Vector2
         * @param [in] scalar The scalar
         * @param The result of dividision of the Vector2 by the scalar
         */
        inline Vector2 operator/(const Vector2& v, float scalar)
        {
            return DST_TO_GLM_VEC2_CONST(v) / scalar;
        }

        /**
         * Pushes a specified Vector2 into a specified std::ostream.
         * @param [in] stream The std::ostream to push into
         * @param [in] v The Vector2 to push
         * @return The std::ostream with the Vector2 pushed
         */
        inline std::ostream& operator<<(std::ostream& stream, const Vector2& v)
        {
            stream << v.to_string();
            return stream;
        }
    } // namespace Math
} // namespace Dynamic_Static

namespace Dynamic_Static {
    template <>
    inline std::string to_string<dst::math::Vector2>(const dst::math::Vector2& v)
    {
        return v.to_string();
    }
} // namespace Dynamic_Static

namespace std {
    /**
     * Function object for dst::math::Vector2's hash function.
     */
    template <>
    struct hash<dst::math::Vector2> {
        /**
         * Hash function for dst::math::Vector2.
         */
        inline size_t operator()(const dst::math::Vector2& v) const
        {
            return hash<glm::vec2>()(DST_TO_GLM_VEC2_CONST(v));
        }
    };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
