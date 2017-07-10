
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Vector3.hpp"
#include "Dynamic_Static/Core/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Core/Math/Quaternion.hpp"

namespace Dynamic_Static
{
    class Transform final
    {
    public:
        Vector3 translation { Vector3::Zero };
        Quaternion rotation { Quaternion::Identity };
        Vector3 scale { Vector3::One };

    public:
        inline Matrix4x4 world() const
        {
            return Matrix4x4(translation, rotation, scale);
        }

        inline Vector3 up() const
        {
            return Vector4(world() * Vector4::Up).normalized();
        }

        inline Vector3 down() const
        {
            return Vector4(world() * Vector4::Down).normalized();
        }

        inline Vector3 left() const
        {
            return Vector4(world() * Vector4::Left).normalized();
        }

        inline Vector3 right() const
        {
            return Vector4(world() * Vector4::Right).normalized();
        }

        inline Vector3 forward() const
        {
            return Vector4(world() * Vector4::Forward).normalized();
        }

        inline Vector3 backward() const
        {
            return Vector4(world() * Vector4::Backward).normalized();
        }
    };
} // namespace Dynamic_Static
