
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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
#include "Dynamic_Static/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Math/Quaternion.hpp"

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        struct Transform final {
        public:
            Vector3 translation;
            Quaternion rotation;
            Vector3 scale { 1, 1, 1 };

        public:
            /**
             * TODO : Documentation.
             */
            Transform() = default;

            /**
             * TODO : Documentation.
             */
            Transform(Transform&& other) = default;

            /**
             * TODO : Documentation.
             */
            Transform(const Transform& other) = default;

            /**
             * TODO : Documentation.
             */
            Transform& operator=(Transform&& other) = default;

            /**
             * TODO : Documentation.
             */
            Transform& operator=(const Transform& other) = default;

            /**
             * TODO : Documentation.
             */
            Transform(const Vector3& translation)
                : Transform(translation, Quaternion::Identity, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            Transform(const Quaternion& rotation)
                : Transform(Vector3::Zero, rotation, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            Transform(const Vector3& translation, const Quaternion& rotation)
                : Transform(translation, rotation, Vector3::One)
            {
            }

            /**
             * TODO : Documentation.
             */
            Transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
                : translation { translation }
                , rotation { rotation }
                , scale { scale }
            {
            }

        public:
            /**
             * TODO : Documentation.
             */
            inline Matrix4x4 world() const
            {
                return Matrix4x4(translation, rotation, scale);
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 up() const
            {
                return up(world());
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 down() const
            {
                return down(world());
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 left() const
            {
                return left(world());
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 right() const
            {
                return right(world());
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 forward() const
            {
                auto wtf = forward(world());
                return wtf;
            }

            /**
             * TODO : Documentation.
             */
            inline Vector3 backward() const
            {
                return backward(world());
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 up(const Matrix4x4& m)
            {
                return (m * Vector3::Up).normalized();
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 down(const Matrix4x4& m)
            {
                return (m * Vector3::Down).normalized();
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 left(const Matrix4x4& m)
            {
                return (m * Vector3::Left).normalized();
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 right(const Matrix4x4& m)
            {
                return (m * Vector3::Right).normalized();
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 forward(const Matrix4x4& m)
            {
                return (m * Vector3::Forward).normalized();
            }

            /**
             * TODO : Documentation.
             */
            static inline Vector3 backward(const Matrix4x4& m)
            {
                return (m * Vector3::Backward).normalized();
            }
        };

        static_assert(
            sizeof(Transform) == sizeof(Vector3) + sizeof(Quaternion) + sizeof(Vector3),
            "sizeof(Transform) must equal sizeof(Vector3) + sizeof(Quaternion) + sizeof(Vector3)"
        );
    } // namespace Math
} // namespace Dynamic_Static
