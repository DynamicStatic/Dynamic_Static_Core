
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

#include "Dynamic_Static/Math/Transform.hpp"
#include "Dynamic_Static/Core/NotImplementedError.hpp"

namespace Dynamic_Static {
    namespace Math {
        // TODO : Add Transform parenting...
        // NOTE : Since there's no Transform parenting yet, everything is in local space...
        const Vector3& Transform::position() const { return mLocalPosition; }
        Vector3& Transform::position() { return mLocalPosition; }
        void Transform::position(const Vector3& position) { mLocalPosition = position; }

        const Quaternion& Transform::rotation() const { return mLocalRotation; }
        Quaternion& Transform::rotation() { return mLocalRotation; }
        void Transform::rotation(const Quaternion& rotation)
        {
            // TODO : Transform rotation into local space.
            local_rotation(rotation);
        }

        const Vector3& Transform::scale() const { return mLocalScale; }
        Vector3& Transform::scale() { return mLocalScale; }
        void Transform::scale(const Vector3& scale) { mLocalScale = scale; }
        const Vector3& Transform::local_position() const { return mLocalPosition; }
        Vector3& Transform::local_position() { return mLocalPosition; }
        void Transform::local_position(const Vector3& localPosition) { mLocalPosition = localPosition; }

        const Quaternion& Transform::local_rotation() const { return mLocalRotation; }
        Quaternion& Transform::local_rotation() { return mLocalRotation; }
        void Transform::local_rotation(const Quaternion& localRotation)
        {
            mLocalRotation = localRotation;
            mLocalRotation.normalize();
            mUp = mLocalRotation.rotate(Vector3::Up);
            mLeft = mLocalRotation.rotate(Vector3::Left);
            mForward = mLocalRotation.rotate(Vector3::Forward);
            mUp.normalize();
            mLeft.normalize();
            mForward.normalize();
        }

        const Vector3& Transform::local_scale() const { return mLocalScale; }
        Vector3& Transform::local_scale() { return mLocalScale; }
        void Transform::local_scale(const Vector3& localScale) { mLocalScale = localScale; }
        Vector3 Transform::up() const { return mUp; }
        Vector3 Transform::down() const { return -mUp; }
        Vector3 Transform::left() const { return mLeft; }
        Vector3 Transform::right() const { return -mLeft; }
        Vector3 Transform::forward() const { return mForward; }
        Vector3 Transform::backward() const { return -mForward; }

        Matrix4x4 Transform::world_to_local() const
        {
            throw NotImplementedError();
            return Matrix4x4::identity;
        }

        Matrix4x4 Transform::local_to_world() const
        {
            throw NotImplementedError();
            return Matrix4x4::identity;
        }
    } // namespace Math
} // namespace Dynamic_Static
