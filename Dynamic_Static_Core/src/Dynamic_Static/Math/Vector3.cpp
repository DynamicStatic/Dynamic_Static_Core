
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

#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"

namespace Dynamic_Static {
    namespace Math {
        Vector3::Vector3(const glm::vec3& vec3)
            : mVec3 { vec3 }
        {
        }

        Vector3::Vector3(float x, float y, float z)
            : mVec3 { x, y, z }
        {
        }

        Vector3::Vector3(const Vector3& other)
        {
            mVec3 = other.mVec3;
        }

        Vector3::Vector3(const Vector4& other)
        {
            mVec3 = other.mVec4;
        }

        Vector3& Vector3::operator+=(const Vector3& other)
        {
            mVec3 += other.mVec3;
            return *this;
        }

        float Vector3::x() const { return mVec3.x; }
        float Vector3::y() const { return mVec3.y; }
        float Vector3::z() const { return mVec3.z; }
        void Vector3::x(float x) { mVec3.x = x; }
        void Vector3::y(float y) { mVec3.y = y; }
        void Vector3::z(float z) { mVec3.z = z; }

        void Vector3::normalize()
        {
            if (mVec3.x && mVec3.y && mVec3.z) {
                mVec3 = glm::normalize(mVec3);
            }
        }

        Vector3 Vector3::normalized() const
        {
            Vector3 vec3 = *this;
            vec3.normalize();
            return vec3;
        }

        std::string Vector3::to_string() const
        {
            return
                "{ " +
                std::to_string(x()) + ", " +
                std::to_string(y()) + ", " +
                std::to_string(z()) +
                " }";
        }

        const Vector3 Vector3::one      = Vector3 {  1,  1,  1 };
        const Vector3 Vector3::zero     = Vector3 {  0,  0,  0 };
        const Vector3 Vector3::up       = Vector3 {  0,  1,  0 };
        const Vector3 Vector3::down     = Vector3 {  0, -1,  0 };
        const Vector3 Vector3::left     = Vector3 {  1,  0,  0 };
        const Vector3 Vector3::right    = Vector3 { -1,  0,  0 };
        const Vector3 Vector3::forward  = Vector3 {  0,  0,  1 };
        const Vector3 Vector3::backward = Vector3 {  0,  0, -1 };
        const Vector3 Vector3::unit_x   = Vector3 {  1,  0,  0 };
        const Vector3 Vector3::unit_y   = Vector3 {  0,  1,  0 };
        const Vector3 Vector3::unit_z   = Vector3 {  0,  0,  1 };

        bool operator==(const Vector3& lhs, const Vector3& rhs)
        {
            return
                lhs.x() == rhs.x() &&
                lhs.y() == rhs.y() &&
                lhs.z() == rhs.z();
        }

        Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
        {
            return Vector3 {
                lhs.x() + rhs.x(),
                lhs.y() + rhs.y(),
                lhs.z() + rhs.z(),
            };
        }

        Vector3 operator-(const Vector3& v)
        {
            return Vector3 { -v.x(), -v.y(), -v.z() };
        }

        Vector3 operator*(const Vector3&v, float s)
        {
            return Vector3 { v.x() * s, v.y() * s, v.z() * s };
        }
    }
}

namespace Dynamic_Static {
    template <>
    std::string to_string<dst::math::Vector3>(const dst::math::Vector3& v)
    {
        return v.to_string();
    }
}
