
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

#include "Dynamic_Static/Math/Quaternion.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"
#include "Dynamic_Static/Math/Utilities.hpp"

#include <glm/gtx/quaternion.hpp>

namespace Dynamic_Static {
    namespace Math {
        Quaternion::Quaternion()
            : m_quat { }
        {
        }

        Quaternion::Quaternion(float x, float y, float z, float w)
            : m_quat { x, y, z, w }
        {
        }

        Quaternion::Quaternion(const Vector3& v)
            : m_quat { v.m_vec3 }
        {
        }

        Quaternion::Quaternion(const glm::quat& quat)
            : m_quat { quat }
        {
        }

        float Quaternion::x() const { return m_quat.x; }
        float Quaternion::y() const { return m_quat.y; }
        float Quaternion::z() const { return m_quat.z; }
        float Quaternion::w() const { return m_quat.w; }
        void Quaternion::x(float x) { m_quat.x = x; }
        void Quaternion::y(float y) { m_quat.y = y; }
        void Quaternion::z(float z) { m_quat.z = z; }
        void Quaternion::w(float w) { m_quat.w = w; }

        void Quaternion::normalize()
        {
            m_quat = glm::normalize(m_quat);
        }

        Vector3 Quaternion::rotate(const Vector3& v)
        {
            return Vector3 { glm::rotate(m_quat, v.m_vec3) };
        }

        Vector4 Quaternion::rotate(const Vector4& v)
        {
            return Vector4 { glm::rotate(m_quat, v.m_vec4) };
        }

        Quaternion Quaternion::angle_axis(float angle, const Vector3& axis)
        {
            return Quaternion { glm::angleAxis(angle, axis.m_vec3) };
        }

        Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
        {
            return Quaternion { lhs.m_quat * rhs.m_quat };
        }

        const Quaternion Quaternion::identity = Quaternion { 0, 0, 0, 1 };
    }
}
