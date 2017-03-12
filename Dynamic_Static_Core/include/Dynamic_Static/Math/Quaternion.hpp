
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
#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLMQUAT(DSTQUATERNION) (*reinterpret_cast<glm::quat*>(&DSTQUATERNION))
#define DST_TO_GLMQUAT_CONST(DSTQUATERNION) (*reinterpret_cast<const glm::quat*>(&DSTQUATERNION))

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of a 3D rotation.
         */
        struct Quaternion final {
        public:
            /**
             * Constant Quaternion(0, 0, 0, 1).
             */
            static const Quaternion Identity;

        public:
            union {
                glm::quat _quat;
                std::array<float, 4> values;
                struct { float x, y, z, w; };
            };

        public:
            /**
             * Constructs an instance of Quaternion.
             */
            inline Quaternion()
                : Quaternion(Identity)
            {
            }

            /**
             * Constructs an instance of Quaternion.
             * @param [in] x Quaternion's x value
             * @param [in] y Quaternion's y value
             * @param [in] z Quaternion's z value
             * @param [in] w Quaternion's w value
             */
            inline Quaternion(float x, float y, float z, float w)
                : x { x }
                , y { y }
                , z { z }
                , w { w }
            {
            }

            /**
             * Constructs an instance of Quaternion.
             * @param [in] values An array containing this Quaternion's values
             */
            inline Quaternion(const float* values)
            {
                std::copy_n(values, this->values.size(), this->values.begin());
            }

            /**
             * Constructs an instance of Quaternion.
             * @param [in] eulerAngles This Quaternion's Euler angles in radians
             */
            inline Quaternion(const Vector3& eulerAngles)
            {
                DST_TO_GLMQUAT(*this) = glm::quat(DST_TO_GLMVEC3_CONST(eulerAngles));
            }

            /**
             * Constructs an instance of Quaternion.
             * @aparam [in] xyzw This Quaternion's x, y, z, and w values
             */
            inline Quaternion(const Vector4& xyzw)
                : Quaternion(xyzw.values.data())
            {
            }

            /**
             * Moves an instance of Quaternion.
             * @param [in] other The Quaternion to move from
             */
            Quaternion(Quaternion&& other) = default;

            /**
             * Copies an instance of Quaternion.
             * @param [in] other The Quaternion to copy from
             */
            Quaternion(const Quaternion& other) = default;

            /**
             * Moves an instance of Quaternion.
             * @param [in] other The Quaternion to move from
             */
            Quaternion& operator=(Quaternion&& other) = default;

            /**
             * Copies an instance of Quaternion.
             * @param [in] other The Quaternion to copy from
             */
            Quaternion& operator=(const Quaternion& other) = default;

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
            inline Quaternion(const glm::quat& other)
            {
                DST_TO_GLMQUAT(*this) = other;
            }

        public:
            /**
             * Gets a normalized copy of this Quaternion.
             * @return A normalized copy of this Quaternion
             */
            inline Quaternion normalized() const
            {
                return glm::normalize(DST_TO_GLMQUAT_CONST(*this));
            }

            /**
             * Normalizes this Quaternion.
             */
            inline void normalize()
            {
                DST_TO_GLMQUAT(*this) = glm::normalize(DST_TO_GLMQUAT_CONST(*this));
            }

            /**
             * Rotates a specified Vector3 by this Quaternion.
             * @param [in] v The Vector3 to rotate
             * @return The rotated Vector3
             */
            inline Vector3 rotate(const Vector3& v)
            {
                return glm::rotate(DST_TO_GLMQUAT_CONST(*this), DST_TO_GLMVEC3_CONST(v));
            }

            static inline Quaternion angle_axis(float angle, const Vector3& axis)
            {
                return glm::angleAxis(angle, DST_TO_GLMVEC3_CONST(axis));
            }

            /**
             * Gets the std::string representation of this Quaternion.
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
        };

        static_assert(
            sizeof(Quaternion) == sizeof(float) * 4,
            "sizeof(Quaternion) must equal sizeof(float) * 4"
        );

        /**
         * Gets a value indicating whether or two specified Quaternion are equal.
         * @param [in] q0 The first Quaternion
         * @param [in] q1 The second Quaternion
         * @return whether or not the two specified Quaternion are equal
         */
        inline bool operator==(const Quaternion q0, const Quaternion& q1)
        {
            return q0.values == q1.values;
        }

        /**
         * Gets a value indicating whether or not two specified Quaternions are inequal.
         * @param [in] q0 The first Quaternion
         * @param [in] q1 The second Quaternion
         * @return whether or not the two specified Quaternions are inequal
         */
        inline bool operator!=(const Quaternion q0, const Quaternion& q1)
        {
            return !(q0 == q1);
        }
    } // namespace Math
} // namespace Dynamic_Static

namespace Dynamic_Static {
    template <>
    inline std::string to_string<dst::math::Quaternion>(const dst::math::Quaternion& q)
    {
        return q.to_string();
    }
} // namespace Dynamic_Static

namespace std {
    /**
     * Function object for dst::math::Quaternion's hash function.
     */
    template <>
    struct hash<dst::math::Quaternion> {
        /**
         * Hash function for dst::math::Quaternion.
         */
        inline size_t operator()(const dst::math::Quaternion& q) const
        {
            return hash<glm::quat>()(DST_TO_GLMQUAT_CONST(q));
        }
    };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
