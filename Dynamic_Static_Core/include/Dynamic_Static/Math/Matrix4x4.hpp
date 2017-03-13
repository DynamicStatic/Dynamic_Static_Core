
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

#include "Dynamic_Static/Math/Defines.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"
#include "Dynamic_Static/Math/Quaternion.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLM_MAT4(DST_MATRIX4X4) (*reinterpret_cast<glm::mat4*>(&DST_MATRIX4X4))
#define DST_TO_GLM_MAT4_CONST(DST_MATRIX4X4) (*reinterpret_cast<const glm::mat4*>(&DST_MATRIX4X4))

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of a 3D translation, rotation, and scale.
         */
        struct Matrix4x4 final {
            friend Matrix4x4 operator*(const Matrix4x4&, const Matrix4x4&);
            friend Vector3 operator*(const Matrix4x4&, const Vector3&);
            friend Vector4 operator*(const Matrix4x4&, const Vector4&);
        public:
            /**
             * Constant Matrix4x4
             *  [1, 0, 0, 0]
             *  [0, 1, 0, 0]
             *  [0, 0, 1, 0]
             *  [0, 0, 0, 1]
             */
            static const Matrix4x4 Identity;

        public:
            union {
                std::array<float, 16> values;
                std::array<Vector4, 4> columns;
            };

        public:
            /**
             * TODO : Documentation.
             */
            inline Matrix4x4()
                : Matrix4x4(Identity)
            {
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(
                float _00, float _10, float _20, float _30,
                float _01, float _11, float _21, float _31,
                float _02, float _12, float _22, float _32,
                float _03, float _13, float _23, float _33
            )
            {
                columns[0][0] = _00;
                columns[0][1] = _01;
                columns[0][2] = _02;
                columns[0][3] = _03;

                columns[1][0] = _10;
                columns[1][1] = _11;
                columns[1][2] = _12;
                columns[1][3] = _13;

                columns[2][0] = _20;
                columns[2][1] = _21;
                columns[2][2] = _22;
                columns[2][3] = _23;

                columns[3][0] = _30;
                columns[3][1] = _31;
                columns[3][2] = _32;
                columns[3][3] = _33;
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(const float* values)
            {
                std::memcpy(this, values, sizeof(*this));
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(const Vector3& translation)
                : Matrix4x4(translation, Quaternion::Identity, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(const Quaternion& rotation)
                : Matrix4x4(Vector3::Zero, rotation, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(const Vector3& translation, const Quaternion& rotation)
                : Matrix4x4(translation, rotation, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
            {
                *this = create_translation(translation) * create_rotation(rotation) * create_scale(scale);
            }

            /**
             * Moves an instance of Matrix4x4.
             * @param [in] other The Matrix4x4 to move from
             */
            Matrix4x4(Matrix4x4&& other) = default;

            /**
             * Copies an instance of Matrix4x4.
             * @param [in] other The Matrix4x4 to copy from
             */
            Matrix4x4(const Matrix4x4& other) = default;

            /**
             * Moves an instance of Matrix4x4.
             * @param [in] other The Matrix4x4 to move from
             */
            Matrix4x4& operator=(Matrix4x4&& other) = default;

            /**
             * Copies an instance of Matrix4x4.
             * @param [in] other The Matrix4x4 to copy from
             */
            Matrix4x4& operator=(const Matrix4x4& other) = default;

            /**
             * TODO : Documentation.
             */
            inline Matrix4x4& operator*=(const Matrix4x4& other)
            {
                DST_TO_GLM_MAT4(*this) *= DST_TO_GLM_MAT4_CONST(other);
            }

            /**
             * Gets the column at the specified index.
             * @param [in] index The index of the column to get
             * @return The column at the specified index
             */
            inline const Vector4& operator[](size_t index) const
            {
                return columns[index];
            }

            /**
             * Gets the column at the specified index.
             * @param [in] index The index of the column to get
             * @return The column at the specified index
             */
            inline Vector4& operator[](size_t index)
            {
                return columns[index];
            }

            /**
             * Gets a pointer Matrix4x4's underlying data.
             * @return A pointer to this Matrix4x4's underlying data
             */
            inline const float* data() const
            {
                return values.data();
            }

        private:
            inline Matrix4x4(const glm::mat4& other)
            {
                DST_TO_GLM_MAT4(*this) = other;
            }

        public:
            /**
             * Applies a translation to this Matrix4x4.
             * @param [in] translation The translation to apply to this Matrix4x4
             */
            inline void translate(const Vector3& translation)
            {
                DST_TO_GLM_MAT4(*this) =
                    glm::translate(
                        DST_TO_GLM_MAT4_CONST(*this),
                        DST_TO_GLM_VEC3_CONST(translation)
                    );
            }

            /**
             * Applies a rotation to this Matrix4x4.
             * @param [in] angle The angle in radians to rotate by
             * @param [in] axis The axis to apply the rotation on
             */
            inline void rotate(float angle, const Vector3& axis)
            {
                DST_TO_GLM_MAT4(*this) =
                    glm::rotate(
                        DST_TO_GLM_MAT4_CONST(*this),
                        angle,
                        DST_TO_GLM_VEC3_CONST(axis)
                    );
            }

            /**
             * Applies a scale to this Matrix4x4.
             * @param [in] scale The scale to apply to this Matrix4x4.
             */
            inline void scale(const Vector3& scale)
            {
                DST_TO_GLM_MAT4(*this) =
                    glm::scale(
                        DST_TO_GLM_MAT4_CONST(*this),
                        DST_TO_GLM_VEC3_CONST(scale)
                    );
            }

            /**
             * Gets the std::string representation of this Matrix4x4.
             */
            inline std::string to_string() const
            {
                return "[TODO : Matrix4x4.to_string()]";
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_translation(const Vector3& translation)
            {
                return glm::translate(DST_TO_GLM_VEC3_CONST(translation));
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_rotation(float angle, const Vector3& axis)
            {
                return glm::rotate(angle, DST_TO_GLM_VEC3_CONST(axis));
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_rotation(const Quaternion& rotation)
            {
                return glm::mat4_cast(DST_TO_GLM_QUAT_CONST(rotation));
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_scale(const Vector3& scale)
            {
                return glm::scale(DST_TO_GLM_VEC3_CONST(scale));
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_view(const Vector3& position, const Vector3& target, const Vector3& up)
            {
                return
                    glm::lookAt(
                        DST_TO_GLM_VEC3_CONST(position),
                        DST_TO_GLM_VEC3_CONST(target),
                        DST_TO_GLM_VEC3_CONST(up)
                    );
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_perspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
            {
                return glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
            }

            /**
             * TODO : Documentation.
             */
            static inline Matrix4x4 create_orthographic(float left, float right, float top, float bottom, float nearPlane, float farPlane)
            {
                return glm::ortho(left, right, bottom, top, nearPlane, farPlane);
            }
        };

        static_assert(
            sizeof(Matrix4x4) == sizeof(float) * 16,
            "sizeof(Matrix4x4) must equal sizeof(float) * 16"
        );

        /**
         * Gets a value indicating whether or not two specified Matrix4x4s are equal.
         * @param [in] m0 The first Matrix4x4
         * @param [in] m1 The second Matrix4x4
         * @return whether or not the two specified Matrix4x4s are equal
         */
        inline bool operator==(const Matrix4x4 v0, const Matrix4x4& v1)
        {
            return v0.values == v1.values;
        }

        /**
         * Gets a value indicating whether or not two specified Matrix4x4s are inequal.
         * @param [in] m0 The first Matrix4x4
         * @param [in] m1 The second Matrix4x4
         * @return whether or not the two specified Matrix4x4s are inequal
         */
        inline bool operator!=(const Matrix4x4 v0, const Matrix4x4& v1)
        {
            return !(v0 == v1);
        }

        /**
         * TODO : Documentation.
         */
        inline Matrix4x4 operator*(const Matrix4x4& m0, const Matrix4x4& m1)
        {
            return DST_TO_GLM_MAT4_CONST(m0) * DST_TO_GLM_MAT4_CONST(m1);
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 operator*(const Matrix4x4& m, const Vector3& v)
        {
            using namespace glm;
            return DST_TO_GLM_MAT4_CONST(m) * DST_TO_GLM_VEC3_CONST(v);
        }

        /**
         * TODO : Documentation.
         */
        inline Vector4 operator*(const Matrix4x4& m, const Vector4& v)
        {
            return DST_TO_GLM_MAT4_CONST(m) * DST_TO_GLM_VEC4_CONST(v);
        }

        /**
         * Pushes a specified Matrix4x4 into a specified std::ostream.
         * @param [in] stream The std::ostream to push into
         * @param [in] m The Matrix4x4 to push
         * @return The std::ostream with the Matrix4x4 pushed
         */
        inline std::ostream& operator<<(std::ostream& stream, const Matrix4x4& m)
        {
            stream << m.to_string();
            return stream;
        }
    } // namespace Math
} // namespace Dynamic_Static

namespace Dynamic_Static {
    template <>
    inline std::string to_string<dst::math::Matrix4x4>(const dst::math::Matrix4x4& m)
    {
        return m.to_string();
    }
} // namespace Dynamic_Static

namespace std {
    /**
     * Function object for dst::math::Matrix4x4's hash function.
     */
    template <>
    struct hash<dst::math::Matrix4x4> {
        /**
         * Hash function for dst::math::Matrix4x4.
         */
        inline size_t operator()(const dst::math::Matrix4x4& m) const
        {
            return hash<glm::mat4>()(DST_TO_GLM_MAT4_CONST(m));
        }
    };
} // namespace std

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
