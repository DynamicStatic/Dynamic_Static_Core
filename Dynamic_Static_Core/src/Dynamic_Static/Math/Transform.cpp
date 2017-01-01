
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
        const Vector3& Transform::position() const { return m_local_position; }
        Vector3& Transform::position() { return m_local_position; }
        void Transform::position(const Vector3& position) { m_local_position = position; }

        const Quaternion& Transform::rotation() const { return m_local_rotation; }
        Quaternion& Transform::rotation() { return m_local_rotation; }
        void Transform::rotation(const Quaternion& rotation)
        {
            // TODO : Transform rotation into local space.
            local_rotation(rotation);
        }

        const Vector3& Transform::scale() const { return m_local_scale; }
        Vector3& Transform::scale() { return m_local_scale; }
        void Transform::scale(const Vector3& scale) { m_local_scale = scale; }
        const Vector3& Transform::local_position() const { return m_local_position; }
        Vector3& Transform::local_position() { return m_local_position; }
        void Transform::local_position(const Vector3& local_position) { m_local_position = local_position; }

        const Quaternion& Transform::local_rotation() const { return m_local_rotation; }
        Quaternion& Transform::local_rotation() { return m_local_rotation; }
        void Transform::local_rotation(const Quaternion& local_rotation)
        {
            m_local_rotation = local_rotation;
            m_local_rotation.normalize();
            m_up = m_local_rotation.rotate(Vector3::up);
            m_left = m_local_rotation.rotate(Vector3::left);
            m_forward = m_local_rotation.rotate(Vector3::forward);
            m_up.normalize();
            m_left.normalize();
            m_forward.normalize();
        }

        const Vector3& Transform::local_scale() const { return m_local_scale; }
        Vector3& Transform::local_scale() { return m_local_scale; }
        void Transform::local_scale(const Vector3& local_scale) { m_local_scale = local_scale; }
        Vector3 Transform::up() const { return m_up; }
        Vector3 Transform::down() const { return -m_up; }
        Vector3 Transform::left() const { return m_left; }
        Vector3 Transform::right() const { return -m_left; }
        Vector3 Transform::forward() const { return m_forward; }
        Vector3 Transform::backward() const { return -m_forward; }

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
    }
}
