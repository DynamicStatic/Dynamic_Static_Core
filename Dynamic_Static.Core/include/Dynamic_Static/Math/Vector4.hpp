
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

#include "Dynamic_Static/Math/glm/glm.hpp"
#include "Dynamic_Static/Math/glm/gtx/norm.hpp"
// #include "Dynamic_Static/Math/glm/gtx/hash.hpp"

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLM_VEC4(DST_VECTOR4) (*reinterpret_cast<glm::vec4*>(&DST_VECTOR4))
#define DST_TO_GLM_VEC4_CONST(DST_VECTOR4) (*reinterpret_cast<const glm::vec4*>(&DST_VECTOR4))

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of 3D vectors and points.
         */
        struct Vector4 {
            friend struct Quaternion;
            friend Vector4 operator+(const Vector4&, const Vector4&);
            friend Vector4 operator-(const Vector4&, const Vector4&);
            friend Vector4 operator*(const Vector4&, const Vector4&);
            friend Vector4 operator*(const Vector4&, float);
            friend Vector4 operator/(const Vector4&, const Vector4&);
            friend Vector4 operator/(const Vector4&, float);
            friend Vector4 operator*(const Matrix4x4&, const Vector4&);
            friend Vector4 operator*(const Quaternion&, const Vector4&);
        public:
            /**
             * Constant Vector4(1, 1, 1, 1).
             */
            static const Vector4 One;

            /**
             * Constant Vector4(0, 0, 0, 0).
             */
            static const Vector4 Zero;

            /**
             * Constant Vector4(0, 1, 0, 0).
             */
            static const Vector4 Up;

            /**
             * Constant Vector4(0, -1, 0, 0).
             */
            static const Vector4 Down;

            /**
             * Constant Vector4(1, 0, 0, 0).
             */
            static const Vector4 Left;

            /**
             * Constant Vector4(-1, 0, 0, 0).
             */
            static const Vector4 Right;

            /**
             * Constant Vector4(0, 0, 1, 0).
             */
            static const Vector4 Forward;

            /**
             * Constant Vector4(0, 0, -1, 0).
             */
            static const Vector4 Backward;

            /**
             * Constant Vector4(1, 0, 0, 0).
             */
            static const Vector4 UnitX;

            /**
             * Constant Vector4(0, 1, 0, 0).
             */
            static const Vector4 UnitY;

            /**
             * Constant Vector4(0, 0, 1, 0).
             */
            static const Vector4 UnitZ;

            /**
             * Constant Vector4(0, 0, 0, 1).
             */
            static const Vector4 UnitW;

        public:
            union {
                std::array<float, 4> values;
                struct { float x, y, z, w; };
                struct { float r, g, b, a; };
            };

        public:
            /**
             * Constructs an instance of Vector4.
             * @param [in] value The initial value for this Vector4's elements
             */
            inline Vector4(float value = 0)
                : Vector4(value, value, value, value)
            {
            }

            /**
             * Constructs an instance of Vector4.
             * @param [in] x This Vector4's x value
             * @param [in] y This Vector4's y value
             * @param [in] z This Vector4's z value
             * @param [in] w This Vector4's w value
             */
            inline Vector4(float x, float y, float z, float w)
            {
                values[0] = x;
                values[1] = y;
                values[2] = z;
                values[3] = w;
            }

            /**
             * Constructs an instance of Vector4.
             * @param [in] values An array containing this Vector4's values
             */
            inline Vector4(const float* values)
            {
                std::memcpy(this, values, sizeof(*this));
            }

            /**
             * Constructs an instance of Vector4.
             * @param [in] xy The Vector2 to copy the x and y values from
             * \n NOTE : This Vector4's z and w values will be set to zero
             */
            Vector4(const Vector2& xy);

            /**
             * Constructs an instance of Vector4.
             * @param [in] xy The Vector2 to copy the x and y values from
             * @param [in] z This Vector4's z value
             * @param [in] w This Vector4's w value
             */
            Vector4(const Vector2& xy, float z, float w);

            /**
             * Constructs an instance of Vector4.
             * @param [in] x This Vector4's x value
             * @param [in] yz The Vector2 to copy the y and z values from
             * @param [in] w This Vector4's w value
             */
            Vector4(float x, const Vector2& yz, float w);

            /**
             * Constructs an instance of Vector4.
             * @param [in] x This Vector4's x value
             * @param [in] y This Vector4's y value
             * @param [in] zw The Vector2 to copy the z and w values from
             */
            Vector4(float x, float y, const Vector2& zw);

            /**
             * Constructs an instance of Vector4.
             * @param [in] xy The Vector2 to copy the x and y values from
             * @param [in] zw The Vector2 to copy the x and y values from
             */
            Vector4(const Vector2& xy, const Vector2& zw);

            /**
             * Constructs an instance of Vector4.
             * @param [in] xyz The Vector3 to copy the x, y, and z values from
             * \n NOTE : This Vector4's w value will be set to zero
             */
            Vector4(const Vector3& xyz);

            /**
             * Constructs an instance of Vector4.
             * @param [in] xyz The Vector3 to copy the x, y, and z values from
             * @param [in] w This Vector4's w value
             */
            Vector4(const Vector3& xyz, float w);

            /**
             * Constructs an instance of Vector4.
             * @param [in] x This Vector4's x value
             * @param [in] yzw The Vector4's y, z, and w values
             */
            Vector4(float x, const Vector3& yzw);

            /**
             * Moves an instance of Vector4.
             * @param [in] other The Vector4 to move from
             */
            Vector4(Vector4&& other) = default;

            /**
             * Copies an instance of Vector4.
             * @param [in] other The Vector4 to copy from
             */
            Vector4(const Vector4& other) = default;

            /**
             * Moves an instance of Vector4.
             * @param [in] other The Vector4 to move from
             */
            Vector4& operator=(Vector4&& other) = default;

            /**
             * Copies an instance of Vector4.
             * @param [in] other The Vector4 to copy from
             */
            Vector4& operator=(const Vector4& other) = default;

            /**
             * Adds a specified Vector4 to this Vector4.
             * @param [in] other The Vector4 to add to this Vector4
             */
            inline Vector4& operator+=(const Vector4& other)
            {
                DST_TO_GLM_VEC4(*this) += DST_TO_GLM_VEC4_CONST(other);
                return *this;
            }

            /**
             * Subtracts a specified Vector4 from this Vector4.
             * @param [in] other The Vector4 to subtract from this Vector4
             */
            inline Vector4& operator-=(const Vector4& other)
            {
                DST_TO_GLM_VEC4(*this) -= DST_TO_GLM_VEC4_CONST(other);
                return *this;
            }

            /**
             * Multiplies this Vector4 by a specified Vector4.
             * @param [in] other The Vector4 to multiply this Vector4 by
             */
            inline Vector4& operator*=(const Vector4& other)
            {
                DST_TO_GLM_VEC4(*this) *= DST_TO_GLM_VEC4_CONST(other);
                return *this;
            }

            /**
             * Multiplies this Vector4 by a specified scalar.
             * @param [in] other The scalar to multiply this Vector4 by
             */
            inline Vector4& operator*=(float scalar)
            {
                DST_TO_GLM_VEC4(*this) *= scalar;
                return *this;
            }

            /**
             * Divides this Vector4 by a specified Vector4.
             * @param [in] other The Vector4 to divide this Vector4 by
             */
            inline Vector4& operator/=(const Vector4& other)
            {
                DST_TO_GLM_VEC4(*this) /= DST_TO_GLM_VEC4_CONST(other);
                return *this;
            }

            /**
             * Divides this Vector4 by a specified scalar.
             * @param [in] other The scalar to divide this Vector4 by
             */
            inline Vector4& operator/=(float scalar)
            {
                DST_TO_GLM_VEC4(*this) /= scalar;
                return *this;
            }

            /**
             * Gets the opposite of this Vector2.
             * @return The opposite of this Vector2
             */
            inline Vector4 operator-() const
            {
                return -DST_TO_GLM_VEC4_CONST(*this);
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
             * Gets a pointer Vector4's underlying data.
             * @return A pointer to this Vector4's underlying data
             */
            inline const float* data() const
            {
                return values.data();
            }

        private:
            inline Vector4(const glm::vec4& other)
            {
                DST_TO_GLM_VEC4(*this) = DST_TO_GLM_VEC4_CONST(other);
            }

        public:
            /**
             * Gets this Vector4's magnitude.
             */
            inline float magnitude() const
            {
                return glm::length(DST_TO_GLM_VEC4_CONST(*this));
            }

            /**
             * Gets this Vector4's magnitude squared.
             */
            inline float magnitude_squared() const
            {
                return glm::length2(DST_TO_GLM_VEC4_CONST(*this));
            }

            /**
             * Gets a normalized copy of this Vector4.
             * @return A normalized copy of this Vector4
             */
            inline Vector4 normalized() const
            {
                if (magnitude_squared()) {
                    return glm::normalize(DST_TO_GLM_VEC4_CONST(*this));
                } else {
                    return Vector4::Zero;
                }
            }

            /**
             * Normalizes this Vector4.
             */
            inline void normalize()
            {
                *this = normalized();
            }

            /**
             * Gets the std::string representation of this Vector4.
             */
            inline std::string to_string() const
            {
                return 
                    "(" +
                    std::to_string(x) + ", " +
                    std::to_string(y) + ", " +
                    std::to_string(z) + ", " +
                    std::to_string(w) +
                    ")";
            }

            /**
             * Gets a Vector4 lineraly interpolated between two Vector4s by a specified weight.
             * @param [in] v0 The Vector4 to interpolate from
             * @param [in] v1 The Vector4 to interpolate towards
             * @param [in] s The weight of the interpolation
             * @return The result of the linear interpolation
             */
            static inline Vector4 lerp(const Vector4& v0, const Vector4& v1, float t)
            {
                return Vector4(
                    dst::lerp(v0.x, v1.x, t),
                    dst::lerp(v0.y, v1.y, t),
                    dst::lerp(v0.z, v1.z, t),
                    dst::lerp(v0.w, v1.w, t)
                );
            }
        };

        static_assert(
            sizeof(Vector4) == sizeof(float) * 4,
            "sizeof(Vector4) must equal sizeof(float) * 4"
        );

        /**
         * Gets a value indicating whether or not two specified Vector4s are equal.
         * @param [in] v0 The first Vector4
         * @param [in] v1 The second Vector4
         * @return whether or not the two specified Vector4s are equal
         */
        inline bool operator==(const Vector4& v0, const Vector4& v1)
        {
            return v0.values == v1.values;
        }

        /**
         * Gets a value indicating whether or not two specified Vector4s are inequal.
         * @param [in] v0 The first Vector4
         * @param [in] v1 The second Vector4
         * @return whether or not the two specified Vector4s are inequal
         */
        inline bool operator!=(const Vector4& v0, const Vector4& v1)
        {
            return !(v0 == v1);
        }

        /**
         * Gets the result of addition between two Vector4s.
         * @param [in] v0 The first Vector4
         * @param [in] v1 The second Vector4
         * @param The result of addition between the Vector4s
         */
        inline Vector4 operator+(const Vector4& v0, const Vector4& v1)
        {
            return DST_TO_GLM_VEC4_CONST(v0) + DST_TO_GLM_VEC4_CONST(v1);
        }

        /**
         * Gets the result of subtracting a Vector4 from another.
         * @param [in] v0 The Vector4 to subtract from
         * @param [in] v1 The Vector4 to subtract
         * @return The result of subtraction between the Vector4s
         */
        inline Vector4 operator-(const Vector4& v0, const Vector4& v1)
        {
            return DST_TO_GLM_VEC4_CONST(v0) - DST_TO_GLM_VEC4_CONST(v1);
        }

        /**
         * Gets the result of multiplication between two Vector4s.
         * @param [in] v0 The first Vector4
         * @param [in] v1 The second Vector4
         * @param The result of multiplication between the Vector4s
         */
        inline Vector4 operator*(const Vector4& v0, const Vector4& v1)
        {
            return DST_TO_GLM_VEC4_CONST(v0) * DST_TO_GLM_VEC4_CONST(v1);
        }

        /**
         * Gets the result of multiplication between a Vector4 and a scalar
         * @param [in] v The Vector4
         * @param [in] scalar The scalar
         * @param The result of multiplication between the Vector4 and the scalar
         */
        inline Vector4 operator*(const Vector4& v, float scalar)
        {
            return DST_TO_GLM_VEC4_CONST(v) * scalar;
        }

        /**
         * Gets the result of dividing a Vector4 by another.
         * @param [in] v0 The Vector4 to divide
         * @param [in] v1 The Vector4 to divide by
         * @param The result of division between the Vector4s
         */
        inline Vector4 operator/(const Vector4& v0, const Vector4& v1)
        {
            return DST_TO_GLM_VEC4_CONST(v0) / DST_TO_GLM_VEC4_CONST(v1);
        }

        /**
         * Gets the result of dividing a Vector4 by a scalar
         * @param [in] v The Vector4
         * @param [in] scalar The scalar
         * @param The result of dividision of the Vector4 by the scalar
         */
        inline Vector4 operator/(const Vector4& v, float scalar)
        {
            return DST_TO_GLM_VEC4_CONST(v) / scalar;
        }

        /**
         * Pushes a specified Vector4 into a specified std::ostream.
         * @param [in] stream The std::ostream to push into
         * @param [in] v The Vector4 to push
         * @return The std::ostream with the Vector4 pushed
         */
        inline std::ostream& operator<<(std::ostream& stream, const Vector4& v)
        {
            stream << v.to_string();
            return stream;
        }
    } // namespace Math
} // namespace Dynamic_Static

namespace Dynamic_Static {
    template <>
    inline std::string to_string<dst::math::Vector4>(const dst::math::Vector4& v)
    {
        return v.to_string();
    }
} // namespace Dynamic_Static

namespace std {
    // TODO : Clang really doesn't want to compile these hash functions.
    // /**
    //  * Function object for dst::math::Vector4's hash function.
    //  */
    // template <>
    // struct hash<dst::math::Vector4> {
    //     /**
    //      * Hash function for dst::math::Vector4.
    //      */
    //     inline size_t operator()(const dst::math::Vector4& v) const
    //     {
    //         return hash<glm::vec3>()(DST_TO_GLM_VEC4_CONST(v));
    //     }
    // };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
