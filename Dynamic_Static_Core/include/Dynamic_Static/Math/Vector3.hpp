
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

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLMVEC3(DSTVECTOR3) (*reinterpret_cast<glm::vec3*>(&DSTVECTOR3))
#define DST_TO_GLMVEC3_CONST(DSTVECTOR3) (*reinterpret_cast<const glm::vec3*>(&DSTVECTOR3))

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of 3D vectors and points.
         */
        struct Vector3 {
            friend class Quaternion;
            friend Vector3 operator+(const Vector3&, const Vector3&);
            friend Vector3 operator-(const Vector3&, const Vector3&);
            friend Vector3 operator*(const Vector3&, const Vector3&);
            friend Vector3 operator*(const Vector3&, float);
            friend Vector3 operator/(const Vector3&, const Vector3&);
            friend Vector3 operator/(const Vector3&, float);
        public:
            /**
             * Constant Vector3(1, 1, 1).
             */
            static const Vector3 One;

            /**
             * Constant Vector3(0, 0, 0).
             */
            static const Vector3 Zero;

            /**
             * Constant Vector3(0, 1, 0).
             */
            static const Vector3 Up;

            /**
             * Constant Vector3(0, -1, 0).
             */
            static const Vector3 Down;

            /**
             * Constant Vector3(-1, 0, 0).
             */
            static const Vector3 Left;

            /**
             * Constant Vector3(1, 0, 0).
             */
            static const Vector3 Right;

            /**
             * Constant Vector3(0, 0, 1).
             */
            static const Vector3 Forward;

            /**
             * Constant Vector3(0, 0, -1).
             */
            static const Vector3 Backward;

            /**
             * Constant Vector3(1, 0, 0).
             */
            static const Vector3 UnitX;

            /**
             * Constant Vector3(0, 1, 0).
             */
            static const Vector3 UnitY;

            /**
             * Constant Vector3(0, 0, 1).
             */
            static const Vector3 UnitZ;

        public:
            union {
                glm::vec3 _vec3;
                std::array<float, 3> values;
                struct { float x, y, z; };
                struct { float r, g, b; };
                struct { float s, t, p; };
            };

        public:
            /**
             * Constructs an instance of Vector3.
             * @param [in] value The initial value for this Vector3's elements
             */
            inline Vector3(float value = 0)
                : Vector3(value, value, value)
            {
            }

            /**
             * Constructs an instance of Vector3.
             * @param [in] x This Vector3's x value
             * @param [in] y This Vector3's y value
             * @param [in] z This Vector3's z value
             */
            inline Vector3(float x, float y, float z)
            {
                values[0] = x;
                values[1] = y;
                values[2] = z;
            }

            /**
             * Constructs an instance of Vector3.
             * @param [in] values An array containing this Vector3's values
             */
            inline Vector3(const float* values)
            {
                std::copy_n(values, this->values.size(), this->values.begin());
            }

            /**
             * Constructs an instance of Vector3.
             * @param [in] xy The Vector2 to copy the x and y values from
             *                \n NOTE : This Vector3's z value will be set to zero
             */
            Vector3(const Vector2& xy);

            /**
             * Constructs an instance of Vector3.
             * @param [in] xy The Vector2 to copy the x and y values from
             * @param [in] z This Vector3's z value
             */
            Vector3(const Vector2& xy, float z);

            /**
             * Constructs an instance of Vector3.
             * @param [in] x This Vector3's x value
             * @param [in] yz The Vector2 to copy the yz and y values from
             */
            Vector3(float x, const Vector2& yz);

            /**
             * Constructs an instance of Vector3.
             * @param [in] xyz The Vector4 to copy the x, y, and z elements from
             */
            Vector3(const Vector4& xyz);

            /**
             * Moves an instance of Vector3.
             * @param [in] other The Vector3 to move from
             */
            Vector3(Vector3&& other) = default;

            /**
             * Copies an instance of Vector3.
             * @param [in] other The Vector3 to copy from
             */
            Vector3(const Vector3& other) = default;

            /**
             * Moves an instance of Vector3.
             * @param [in] other The Vector3 to move from
             */
            Vector3& operator=(Vector3&& other) = default;

            /**
             * Copies an instance of Vector3.
             * @param [in] other The Vector4 to copy from
             */
            Vector3& operator=(const Vector3& other) = default;

            /**
             * Adds a specified Vector3 to this Vector3.
             * @param [in] other The Vector3 to add to this Vector3
             */
            inline Vector3& operator+=(const Vector3& other)
            {
                _vec3 += other._vec3;
                return *this;
            }

            /**
             * Subtracts a specified Vector3 from this Vector3.
             * @param [in] other The Vector3 to subtract from this Vector3
             */
            inline Vector3& operator-=(const Vector3& other)
            {
                _vec3 -= other._vec3;
                return *this;
            }

            /**
             * Multiplies this Vector3 by a specified Vector3.
             * @param [in] other The Vector3 to multiply this Vector3 by
             */
            inline Vector3& operator*=(const Vector3& other)
            {
                _vec3 *= other._vec3;
                return *this;
            }

            /**
             * Multiplies this Vector3 by a specified scalar.
             * @param [in] other The scalar to multiply this Vector3 by
             */
            inline Vector3& operator*=(float scalar)
            {
                _vec3 *= scalar;
                return *this;
            }

            /**
             * Divides this Vector3 by a specified Vector3.
             * @param [in] other The Vector3 to divide this Vector3 by
             */
            inline Vector3& operator/=(const Vector3& other)
            {
                _vec3 /= other._vec3;
                return *this;
            }

            /**
             * Divides this Vector3 by a specified scalar.
             * @param [in] other The scalar to divide this Vector3 by
             */
            inline Vector3& operator/=(float scalar)
            {
                _vec3 /= scalar;
                return *this;
            }

            /**
             * Gets the opposite of this Vector2.
             * @return The opposite of this Vector2
             */
            inline Vector3 operator-() const
            {
                return -_vec3;
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

        private:
            inline Vector3(const glm::vec3& other)
            {
                _vec3 = other;
            }

        public:
            /**
             * Gets this Vector3's magnitude.
             */
            inline float magnitude() const
            {
                return glm::length(_vec3);
            }

            /**
             * Gets this Vector3's magnitude squared.
             */
            inline float magnitude_squared() const
            {
                return glm::length2(_vec3);
            }

            /**
             * Gets a normalized copy of this Vector3.
             * @return A normalized copy of this Vector3
             */
            inline Vector3 normalized() const
            {
                return glm::normalize(_vec3);
            }

            /**
             * Normalizes this Vector3.
             */
            inline void normalize()
            {
                _vec3 = glm::normalize(_vec3);
            }

            /**
             * Gets the std::string representation of this Vector3.
             */
            inline std::string to_string() const
            {
                return 
                    "(" +
                    std::to_string(x) + ", " +
                    std::to_string(y) + ", " +
                    std::to_string(z) +
                    ")";
            }

            /**
             * Gets a Vector3 lineraly interpolated between two Vector3s by a specified weight.
             * @param [in] v0 The Vector3 to interpolate from
             * @param [in] v1 The Vector3 to interpolate towards
             * @param [in] s The weight of the interpolation
             * @return The result of the linear interpolation
             */
            static inline Vector3 lerp(const Vector3& v0, const Vector3& v1, float t)
            {
                return Vector3(
                    dst::lerp(v0.x, v1.x, t),
                    dst::lerp(v0.y, v1.y, t),
                    dst::lerp(v0.z, v1.z, t)
                );
            }
        };

        static_assert(
            sizeof(Vector3) == sizeof(float) * 3,
            "sizeof(Vector3) must equal sizeof(float) * 3"
        );

        /**
         * Gets a value indicating whether or not two specified Vector3s are equal.
         * @param [in] v0 The first Vector3
         * @param [in] v1 The second Vector3
         * @return whether or not the two specified Vector3s are equal
         */
        inline bool operator==(const Vector3 v0, const Vector3& v1)
        {
            return v0._vec3 == v1._vec3;
        }

        /**
         * Gets a value indicating whether or two specified Vector3 are inequal.
         * @param [in] v0 The first Vector3
         * @param [in] v1 The second Vector3
         * @return whether or not the two specified Vector3 are inequal
         */
        inline bool operator!=(const Vector3 v0, const Vector3& v1)
        {
            return !(v0 == v1);
        }

        /**
         * Gets the result of addition between two Vector3s.
         * @param [in] v0 The first Vector3
         * @param [in] v1 The second Vector3
         * @param The result of addition between the Vector3s
         */
        inline Vector3 operator+(const Vector3& v0, const Vector3& v1)
        {
            return v0._vec3 + v1._vec3;
        }

        /**
         * Gets the result of subtracting a Vector3 from another.
         * @param [in] v0 The Vector3 to subtract from
         * @param [in] v1 The Vector3 to subtract
         * @return The result of subtraction between the Vector3s
         */
        inline Vector3 operator-(const Vector3& v0, const Vector3& v1)
        {
            return v0._vec3 - v1._vec3;
        }

        /**
         * Gets the result of multiplication between two Vector3s.
         * @param [in] v0 The first Vector3
         * @param [in] v1 The second Vector3
         * @param The result of multiplication between the Vector3s
         */
        inline Vector3 operator*(const Vector3& v0, const Vector3& v1)
        {
            return v0._vec3 * v1._vec3;
        }

        /**
         * Gets the result of multiplication between a Vector3 and a scalar
         * @param [in] v The Vector3
         * @param [in] scalar The scalar
         * @param The result of multiplication between the Vector3 and the scalar
         */
        inline Vector3 operator*(const Vector3& v, float scalar)
        {
            return v._vec3 * scalar;
        }

        /**
         * Gets the result of dividing a Vector3 by another.
         * @param [in] v0 The Vector3 to divide
         * @param [in] v1 The Vector3 to divide by
         * @param The result of division between the Vector3s
         */
        inline Vector3 operator/(const Vector3& v0, const Vector3& v1)
        {
            return v0._vec3 / v1._vec3;
        }

        /**
         * Gets the result of dividing a Vector3 by a scalar
         * @param [in] v The Vector3
         * @param [in] scalar The scalar
         * @param The result of dividision of the Vector3 by the scalar
         */
        inline Vector3 operator/(const Vector3& v, float scalar)
        {
            return v._vec3 / scalar;
        }

        /**
         * Pushes a specified Vector3 into a specified std::ostream.
         * @param [in] stream The std::ostream to push into
         * @param [in] v The Vector3 to push
         * @return The std::ostream with the Vector3 pushed
         */
        inline std::ostream& operator<<(std::ostream& stream, const Vector3& v)
        {
            stream << v.to_string();
            return stream;
        }
    } // namespace Math
} // namespace Dynamic_Static

namespace Dynamic_Static {
    template <>
    inline std::string to_string<dst::math::Vector3>(const dst::math::Vector3& v)
    {
        return v.to_string();
    }
} // namespace Dynamic_Static

namespace std {
    /**
     * Function object for dst::math::Vector3's hash function.
     */
    template <>
    struct hash<dst::math::Vector3> {
        /**
         * Hash function for dst::math::Vector3.
         */
        inline size_t operator()(const dst::math::Vector3& v) const
        {
            return hash<glm::vec3>()(v._vec3);
        }
    };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
