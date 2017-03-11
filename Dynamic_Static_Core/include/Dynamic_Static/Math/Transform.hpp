
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
#include "Dynamic_Static/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Math/Quaternion.hpp"

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        class Transform final {
        private:
            Vector3 mLocalPosition { Vector3::Zero };
            Quaternion mLocalRotation;// { Quaternion::identity };
            Vector3 mLocalScale { Vector3::One };
            Vector3 mUp { Vector3::Up };
            Vector3 mLeft { Vector3::Left };
            Vector3 mForward { Vector3::Forward };

        public:
            /**
             * Gets this Transform's world space position.
             * @return This Transform's world space position
             */
            const Vector3& position() const;

            /**
             * Gets this Transform's world space position.
             * @return This Transform's world space position
             */
            Vector3& position();

            /**
             * Sets this Transform's world space position.
             * @param [in] position This Transform's world space position
             */
            void position(const Vector3& position);

            /**
             * Gets this Transform's world space rotation.
             * @return This Transform's world space rotation
             */
            const Quaternion& rotation() const;

            /**
             * Gets this Transform's world space rotation.
             * @return This Transform's world space rotation
             */
            Quaternion& rotation();

            /**
             * Sets this Transform's world space rotation.
             * @param [in] rotation This Transform's world space rotation
             */
            void rotation(const Quaternion& rotation);

            /**
             * Gets this Transform's world space scale.
             * @return This Transform's world space scale
             */
            const Vector3& scale() const;

            /**
             * Gets this Transform's world space scale.
             * @return This Transform's world space scale
             */
            Vector3& scale();

            /**
             * Sets this Transform's world space scale.
             * @param [in] scale This Transform's world space scale
             */
            void scale(const Vector3& scale);

            /**
             * Gets this Transform's local position.
             * @return This Transform's local position
             */
            const Vector3& local_position() const;

            /**
             * Gets this Transform's local position.
             * @return This Transform's local position
             */
            Vector3& local_position();

            /**
             * Sets this Transform's local position.
             * @param [in] localPosition This Transform's local position
             */
            void local_position(const Vector3& localPosition);

            /**
             * Gets this Transform's local rotation.
             * @return This Transform's local rotation
             */
            const Quaternion& local_rotation() const;

            /**
             * Gets this Transform's local rotation.
             * @return This Transform's local rotation
             */
            Quaternion& local_rotation();

            /**
             * Sets this Transform's local rotation.
             * @param [in] localRotation This Transform's local rotation
             */
            void local_rotation(const Quaternion& localRotation);

            /**
             * Gets this Transform's local scale.
             * @return This Transform's local scale
             */
            const Vector3& local_scale() const;

            /**
             * Gets this Transform's local scale.
             * @return This Transform's local scale
             */
            Vector3& local_scale();

            /**
             * Sets this Transform's local scale.
             * @param [in] localScale This Transform's local scale
             */
            void local_scale(const Vector3& localScale);

            /**
             * Gets this Transform's up vector.
             * @return This Transform's up vector
             */
            Vector3 up() const;

            /**
             * Gets this Transform's down vector.
             * @return This Transform's down vector
             */
            Vector3 down() const;

            /**
             * Gets this Transform's left vector.
             * @return This Transform's left vector
             */
            Vector3 left() const;

            /**
             * Gets this Transform's right vector.
             * @return This Transform's right vector
             */
            Vector3 right() const;

            /**
             * Gets this Transform's forward vector.
             * @return This Transform's forward vector
             */
            Vector3 forward() const;

            /**
             * Gets this Transform's backward vector.
             * @return This Transform's backward vector
             */
            Vector3 backward() const;

            /**
             * Gets a Matrix4x4 that performs a world space to local space transformation.
             * @return A Matrix4x4 that performs a world space to local space transformation
             */
            Matrix4x4 world_to_local() const;

            /**
             * Gets a Matrix4x4 that performs a local space to world space transformation.
             * @return A Matrix4x4 that performs a local space to world space transformation
             */
            Matrix4x4 local_to_world() const;
        };
    }
}
