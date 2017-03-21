
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

#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"

namespace Dynamic_Static {
    namespace Math {
        Vector2::Vector2(const Vector3& xy)
            : Vector2(xy.values.data())
        {
        }

        Vector2::Vector2(const Vector4& xy)
            : Vector2(xy.values.data())
        {
        }

        const Vector2 Vector2::One   {  1,  1 };
        const Vector2 Vector2::Zero  {  0,  0 };
        const Vector2 Vector2::Up    {  0,  1 };
        const Vector2 Vector2::Down  {  0, -1 };
        const Vector2 Vector2::Left  {  1,  0 };
        const Vector2 Vector2::Right { -1,  0 };
        const Vector2 Vector2::UnitX {  1,  0 };
        const Vector2 Vector2::UnitY {  0,  1 };
    } // namespace Math
} // namespace Dynamic_Static
