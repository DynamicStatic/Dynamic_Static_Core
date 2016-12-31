
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
            Vector3 m_local_position;
            Quaternion m_local_rotation;
            Vector3 m_local_scale;

        public:
            /**
             * Gets this Transform's world space position.
             * @return This Transform's world space position
             */
            const Vector3& position() const;

            /**
             * Sets this Transform's world space position.
             * @param [in] local_position This Transform's world space position
             */
            void position(const Vector3& position);

            /**
             * Gets this Transform's world space rotation.
             * @return This Transform's world space rotation
             */
            const Quaternion& rotation() const;

            /**
             * Sets this Transform's world space rotation.
             * @param [in] local_position This Transform's world space rotation
             */
            void rotation(const Quaternion& rotation);

            /**
             * Gets this Transform's world space scale.
             * @return This Transform's world space scale
             */
            const Vector3& scale() const;

            /**
             * Sets this Transform's world space scale.
             * @param [in] local_position This Transform's world space scale
             */
            void scale(const Vector3& scale);

            /**
             * Gets this Transform's local position.
             * @return This Transform's local position
             */
            const Vector3& local_position() const;

            /**
             * Sets this Transform's local position.
             * @param [in] local_position This Transform's local position
             */
            void local_position(const Vector3& local_position);

            /**
             * Gets this Transform's local rotation.
             * @return This Transform's local rotation
             */
            const Quaternion& local_rotation() const;

            /**
             * Sets this Transform's local rotation.
             * @param [in] local_position This Transform's local rotation
             */
            void local_rotation(const Quaternion& local_rotation);

            /**
             * Gets this Transform's local scale.
             * @return This Transform's local scale
             */
            const Vector3& local_scale() const;

            /**
             * Sets this Transform's local scale.
             * @param [in] local_position This Transform's local scale
             */
            void local_scale(const Vector3& local_scale);

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

            /**
             * Rotates this Transform so its' forward vector points at the specified point in world space.
             * @param [in]            target The point in world space to rotate this Transform's forward vector towards
             * @param [in] (optional) up     This Transform's up vector in world space after the rotation for the forward vector
             *                               \n NOTE : If this parameter isn't provided, it will default to Vector3::y
             *                               \n NOTE : This parameter is a hint
             */
            void look_at(const Vector3& target, const Vector3& up = Vector3::up) const;
        };
    }
}
