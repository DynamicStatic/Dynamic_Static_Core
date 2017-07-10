
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

#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static
{
    /**
     * Represents a 4D vector or point.
     */
    struct Vector4
        : public detail::VectorBase<Vector4, glm::vec4>
    {
    public:
        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 Up;
        static const Vector4 Down;
        static const Vector4 Left;
        static const Vector4 Right;
        static const Vector4 Forward;
        static const Vector4 Backward;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 UnitW;

    public:
        using DSTBase::DSTBase;
        using DSTBase::operator+=;
        using DSTBase::operator-=;
        using DSTBase::operator*=;
        using DSTBase::operator/=;
    };

    const Vector4 Vector4::Zero     { 0, 0, 0, 0 };
    const Vector4 Vector4::One      { 1, 1, 1, 1 };
    const Vector4 Vector4::Up       { 0, 1, 0, 0 };
    const Vector4 Vector4::Down     { 0, 1, 0, 0 };
    const Vector4 Vector4::Left     { 1, 0, 0, 0 };
    const Vector4 Vector4::Right    { 1, 0, 0, 0 };
    const Vector4 Vector4::Forward  { 0, 0, 1, 0 };
    const Vector4 Vector4::Backward { 0, 0, 1, 0 };
    const Vector4 Vector4::UnitX    { 1, 0, 0, 0 };
    const Vector4 Vector4::UnitY    { 0, 1, 0, 0 };
    const Vector4 Vector4::UnitZ    { 0, 0, 1, 0 };
    const Vector4 Vector4::UnitW    { 0, 0, 0, 1 };

    static_assert(
        sizeof(Vector4) == sizeof(glm::vec4),
        "sizeof(Vector4) must equal sizeof(glm::vec4)"
    );
} // namespace Dynamic_Static
