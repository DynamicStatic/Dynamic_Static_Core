
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
#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"

namespace Dynamic_Static {
    namespace Math {
        Vector4::Vector4(const Vector2& xy)
            : Vector4(xy[0], xy[1], 0, 0)
        {
        }

        Vector4::Vector4(const Vector2& xy, float z, float w)
            : Vector4(xy[0], xy[1], z, w)
        {
        }

        Vector4::Vector4(float x, const Vector2& yz, float w)
            : Vector4(x, yz[0], yz[1], w)
        {
        }

        Vector4::Vector4(float x, float y, const Vector2& zw)
            : Vector4(x, y, zw[0], zw[1])
        {
        }

        Vector4::Vector4(const Vector2& xy, const Vector2& zw)
            : Vector4(xy[0], xy[1], zw[0], zw[1])
        {
        }

        Vector4::Vector4(const Vector3& xyz)
            : Vector4(xyz[0], xyz[1], xyz[2], 0)
        {
        }

        Vector4::Vector4(const Vector3& xyz, float w)
            : Vector4(xyz[0], xyz[1], xyz[2], w)
        {
        }

        Vector4::Vector4(float x, const Vector3& yzw)
            : Vector4(x, yzw[0], yzw[1], yzw[2])
        {
        }

        const Vector4 Vector4::One      {  1,  1,  1,  1 };
        const Vector4 Vector4::Zero     {  0,  0,  0,  0 };
        const Vector4 Vector4::Up       {  0,  1,  0,  0 };
        const Vector4 Vector4::Down     {  0, -1,  0,  0 };
        const Vector4 Vector4::Left     { -1,  0,  0,  0 };
        const Vector4 Vector4::Right    {  1,  0,  0,  0 };
        const Vector4 Vector4::Forward  {  0,  0,  1,  0 };
        const Vector4 Vector4::Backward {  0,  0, -1,  0 };
        const Vector4 Vector4::UnitX    {  1,  0,  0,  0 };
        const Vector4 Vector4::UnitY    {  0,  1,  0,  0 };
        const Vector4 Vector4::UnitZ    {  0,  0,  1,  0 };
        const Vector4 Vector4::UnitW    {  0,  0,  0,  1 };
    } // namespace Math
} // namespace Dynamic_Static
