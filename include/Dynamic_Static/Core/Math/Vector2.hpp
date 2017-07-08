
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

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
#include "glm/gtx/norm.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static
{
    /**
     * Represents a 2D vector or point.
     */
    struct Vector2
        : public glm::vec2
    {
    public:
        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 Up;
        static const Vector2 Down;
        static const Vector2 Left;
        static const Vector2 Right;
        static const Vector2 UnitX;
        static const Vector2 UnitY;

    public:
        using glm::vec2::tvec2;

    public:
        /**
         * Gets the std::string representation of this Vector2.
         * @return The std::string representation of this Vector2
         */
        inline std::string to_string() const
        {
            return glm::to_string(*this);
        }
    };

    const Vector2 Vector2::Zero  { 0, 0 };
    const Vector2 Vector2::One   { 1, 1 };
    const Vector2 Vector2::Up    { 0, 1 };
    const Vector2 Vector2::Down  { 0, 1 };
    const Vector2 Vector2::Left  { 1, 0 };
    const Vector2 Vector2::Right { 1, 0 };
    const Vector2 Vector2::UnitX { 1, 0 };
    const Vector2 Vector2::UnitY { 0, 1 };

    static_assert(
        sizeof(Vector2) == sizeof(glm::vec2),
        "sizeof(Vector2) must equal sizeof(glm::vec2)"
    );
} // namespace Dynamic_Static
