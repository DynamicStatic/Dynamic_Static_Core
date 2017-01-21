
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

#include "Dynamic_Static/Math/Vector4.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"

namespace Dynamic_Static {
    namespace Math {
        Vector4::Vector4(const glm::vec4 vec4)
            : mVec4 { vec4 }
        {
        }

        Vector4::Vector4(float x, float y, float z, float w)
            : mVec4 { x, y, z, w }
        {
        }

        Vector4::Vector4(const Vector4& other)
        {
            mVec4.x = other.mVec4.x;
            mVec4.y = other.mVec4.y;
            mVec4.z = other.mVec4.z;
            mVec4.w = other.mVec4.w;
        }

        Vector4::Vector4(const Vector3& other)
            : Vector4 { other, 0 }
        {
        }

        Vector4::Vector4(const Vector3& other, float w)
        {
            mVec4.x = other.mVec3.x;
            mVec4.y = other.mVec3.y;
            mVec4.z = other.mVec3.z;
            mVec4.w = w;
        }

        float Vector4::x() const { return mVec4.x; }
        float Vector4::y() const { return mVec4.y; }
        float Vector4::z() const { return mVec4.z; }
        float Vector4::w() const { return mVec4.w; }
        void Vector4::x(float x) { mVec4.x = x; }
        void Vector4::y(float y) { mVec4.y = y; }
        void Vector4::z(float z) { mVec4.z = z; }
        void Vector4::w(float w) { mVec4.w = w; }

        void Vector4::normalize()
        {
            mVec4 = glm::normalize(mVec4);
        }

        const Vector4 Vector4::one      = Vector4 { 1, 1, 1, 1 };
        const Vector4 Vector4::zero     = Vector4 { 0, 0, 0, 0 };
        const Vector4 Vector4::up       = Vector4 { 0, 1, 0, 0         };
        const Vector4 Vector4::down     = Vector4 { -Vector4::up       };
        const Vector4 Vector4::left     = Vector4 { -Vector4::right    };
        const Vector4 Vector4::right    = Vector4 { 1, 0, 0, 0         };
        const Vector4 Vector4::forward  = Vector4 { -Vector4::backward };
        const Vector4 Vector4::backward = Vector4 { 0, 0, 1, 0         };

        bool operator==(const Vector4& lhs, const Vector4& rhs)
        {
            return
                lhs.x() == rhs.x() &&
                lhs.y() == rhs.y() &&
                lhs.z() == rhs.z() &&
                lhs.w() == rhs.w();
        }

        Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
        {
            return Vector4 {
                lhs.x() + rhs.x(),
                lhs.y() + rhs.y(),
                lhs.z() + rhs.z(),
                lhs.w() + rhs.w(),
            };
        }

        Vector4 operator-(const Vector4& v)
        {
            return Vector4 { -v.x(), -v.y(), -v.z(), -v.w() };
        }
    }
}
