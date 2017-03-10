
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

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <array>
#include <string>

namespace std {
    template <>
    struct hash<dst::math::Vector3>;
}

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of 2D vectors and points.
         */
        struct Vector2 final {
            friend Vector2 operator+(const Vector2&, const Vector2&);
            friend Vector2 operator-(const Vector2&, const Vector2&);
            friend Vector2 operator*(const Vector2&, const Vector2&);
            friend Vector2 operator*(const Vector2&, float);
            friend Vector2 operator/(const Vector2&, const Vector2&);
            friend Vector2 operator/(const Vector2&, float);
            friend struct std::hash<Vector2>;
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
             * Constant Vector2(0, -1).
             */
            static const Vector2 Left;

            /**
             * Constant Vector2(0, 1).
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
                glm::vec2 vec2;
                std::array<float, 2> values;
                struct { float x, y; };
                struct { float r, g; };
                struct { float s, t; };
            };

        public:
            /**
             * Constructs an instance of Vector2.
             * @param [in] x This Vector2's x value
             * @param [in] y This Vector2's y value
             */
            inline Vector2(float x = 0, float y = 0)
            {
                values[0] = x;
                values[1] = y;
            }

            /**
             * Constructs an instance of Vector2.
             * @param [in] values This Vector2's values
             */
            inline Vector2(float* values)
            {
                this->values[0] = values[0];
                this->values[1] = values[1];
            }

            /**
             * Copies an instance of Vector2.
             * @param [in] other The Vector2 to copy from
             */
            Vector2(const Vector2& other) = default;

            /**
             * Copies an instance of Vector2 from the first two elements of a Vector3.
             * @param [in] other The Vector3 to copy from
             */
            Vector2(const Vector3& other);

            /**
             * Copies an instance of Vector2 from the first two elements of a Vector4.
             * @param [in] other The Vector4 to copy from
             */
            Vector2(const Vector4& other);

            /**
             * Moves an instance of Vector2.
             * @param [in] other The Vector2 to move from
             */
            Vector2& operator=(Vector2&& other) = default;

            /**
             * Copies an instance of Vector2.
             * @param [in] other The Vector4 to copy from
             */
            inline Vector2& operator=(const Vector2& other) = default;

            /**
             * Adds a specified Vector2 to this Vector2.
             * @param [in] other The Vector2 to add to this Vector2
             */
            inline Vector2& operator+=(const Vector2& other)
            {
                vec2 += other.vec2;
                return *this;
            }

            /**
             * Subtracts a specified Vector2 from this Vector2.
             * @param [in] other The Vector2 to subtract from this Vector2
             */
            inline Vector2 operator-=(const Vector2& other)
            {
                vec2 -= other.vec2;
                return *this;
            }

            /**
             * Multiplies this Vector2 by a specified Vector2.
             * @param [in] other The Vector2 to multiply this Vector2 by
             */
            inline Vector2& operator*=(const Vector2& other)
            {
                vec2 *= other.vec2;
                return *this;
            }

            /**
             * Multiplies this Vector2 by a specified scalar.
             * @param [in] other The scalar to multiply this Vector2 by
             */
            inline Vector2& operator*=(float scalar)
            {
                vec2 *= scalar;
                return *this;
            }

            /**
             * Divides this Vector2 by a specified Vector2.
             * @param [in] other The Vector2 to divide this Vector2 by
             */
            inline Vector2& operator/=(const Vector2& other)
            {
                vec2 /= other.vec2;
                return *this;
            }

            /**
             * Divides this Vector2 by a specified scalar.
             * @param [in] other The scalar to divide this Vector2 by
             */
            inline Vector2& operator/=(float scalar)
            {
                vec2 /= scalar;
                return *this;
            }

        private:
            inline Vector2(const glm::vec2& other)
            {
                vec2 = other;
            }

        public:
            /**
             * Gets this Vector2's magnitude.
             */
            inline float magnitude() const
            {
                return glm::length(vec2);
            }

            /**
             * Gets this Vector2's magnitude squared.
             */
            inline float magnitude_sqaured() const
            {
                return glm::length2(vec2);
            }

            /**
             * Gets a normalized copy of this Vector2.
             * @return A normalized copy of this Vector2
             */
            inline Vector2 normalized() const
            {
                return glm::normalize(vec2);
            }

            /**
             * Normalizes this Vector2.
             */
            inline void normalize()
            {
                vec2 = glm::normalize(vec2);
            }

            /**
             * Gets the std::string representation of this Vector2.
             */
            inline std::string to_string() const
            {
                return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
            }

            /**
             * Gets the absolute angle in radians between two specified Vector2s.
             * @param [in] v0 The first Vector2.
             * @param [in] v1 The second Vector2.
             * @return The absolute angle in radians between the two specified Vector2s.
             */
            static inline float absolute_angle(const Vector2& v0, const Vector2& v1)
            {
                return glm::angle(v0.vec2, v1.vec2);
            }

            /**
             * Gets the oriented angle in radians between two specified Vector2s.
             * @param [in] from The first Vector2.
             * @param [in] to The second Vector2.
             * @return The oriented angle in radians between the two specified Vector2s.
             */
            static inline float oriented_angle(const Vector2& from, const Vector2& to)
            {
                return glm::orientedAngle(from.vec2, to.vec2);
            }

            /**
             * Gets the dot product between two specified Vector2s.
             * @param [in] The first Vector2
             * @param [in] The second Vector2
             * @return The dot product between the two specified Vector2s
             */
            static inline float dot(const Vector2& v0, const Vector2& v1)
            {
                return glm::dot(v0.vec2, v1.vec2);
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

        const Vector2 Vector2::One   { 1,  1 };
        const Vector2 Vector2::Zero  { 0,  0 };
        const Vector2 Vector2::Up    { 0,  1 };
        const Vector2 Vector2::Down  { 0, -1 };
        const Vector2 Vector2::Left  { 0,  0 };
        const Vector2 Vector2::Right { 0,  0 };
        const Vector2 Vector2::UnitX { 1,  0 };
        const Vector2 Vector2::UnitY { 0,  1 };

        /**
         * Gets the result of addition between two Vector2s.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @param The result of addition between the Vector2s
         */
        Vector2 operator+(const Vector2& v0, const Vector2& v1)
        {
            return v0.vec2 + v1.vec2;
        }

        /**
         * Gets the result of subtracting a Vector2 from another.
         * @param [in] v0 The Vector2 to subtract from
         * @param [in] v1 The Vector2 to subtract
         * @return The result of subtraction between the Vector2s
         */
        Vector2 operator-(const Vector2& v0, const Vector2& v1)
        {
            return v0.vec2 - v1.vec2;
        }

        /**
         * Gets the result of multiplication between two Vector2s.
         * @param [in] v0 The first Vector2
         * @param [in] v1 The second Vector2
         * @param The result of multiplication between the Vector2s
         */
        Vector2 operator*(const Vector2& v0, const Vector2& v1)
        {
            return v0.vec2 * v1.vec2;
        }

        /**
         * Gets the result of multiplication between a Vector2 and a scalar
         * @param [in] v The Vector2
         * @param [in] scalar The scalar
         * @param The result of multiplication between the Vector2 and the scalar
         */
        Vector2 operator*(const Vector2& v, float scalar)
        {
            return v.vec2 * scalar;
        }

        /**
         * Gets the result of dividing a Vector2 by another.
         * @param [in] v0 The Vector2 to divide
         * @param [in] v1 The Vector2 to divide by
         * @param The result of division between the Vector2s
         */
        Vector2 operator/(const Vector2& v0, const Vector2& v1)
        {
            return v0.vec2 / v1.vec2;
        }

        /**
         * Gets the result of dividing a Vector2 by a scalar
         * @param [in] v The Vector2
         * @param [in] scalar The scalar
         * @param The result of dividision of the Vector2 by the scalar
         */
        Vector2 operator/(const Vector2& v, float scalar)
        {
            return v.vec2 / scalar;
        }
    } // namespace Math
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
        size_t operator()(const dst::math::Vector2& v) const
        {
            return hash<glm::vec2>()(v.vec2);
        }
    };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
