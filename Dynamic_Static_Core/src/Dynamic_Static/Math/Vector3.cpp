
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

namespace Dynamic_Static {
    namespace Math {
        const Vector3 Vector3::one      = Vector3 {  1, 1, 1 };
        const Vector3 Vector3::zero     = Vector3 {  0, 0, 0 };
        const Vector3 Vector3::x        = Vector3 {  1, 0, 0 };
        const Vector3 Vector3::y        = Vector3 {  0, 1, 0 };
        const Vector3 Vector3::z        = Vector3 {  0, 0, 1 };
        const Vector3 Vector3::up       = Vector3 {  0, 0, 0 }; // Vector3 {  Vector3::y       };
        const Vector3 Vector3::down     = Vector3 {  0, 0, 0 }; // Vector3 { -Vector3::up      };
        const Vector3 Vector3::left     = Vector3 {  0, 0, 0 }; // Vector3 {  Vector3::x       };
        const Vector3 Vector3::right    = Vector3 {  0, 0, 0 }; // Vector3 { -Vector3::left    };
        const Vector3 Vector3::forward  = Vector3 {  0, 0, 0 }; // Vector3 {  Vector3::z       };
        const Vector3 Vector3::backward = Vector3 {  0, 0, 0 }; // Vector3 { -Vector3::forward };
    }
}
