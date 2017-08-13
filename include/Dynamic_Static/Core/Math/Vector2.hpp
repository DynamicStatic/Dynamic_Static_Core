
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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

namespace Dynamic_Static {

    /**
     * Represents a 2D vector or point.
     */
    struct Vector2
        : public detail::VectorBase<Vector2, glm::vec2>
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
        using DSTBase::DSTBase;
        using DSTBase::operator=;
        using DSTBase::operator+=;
        using DSTBase::operator-=;
        using DSTBase::operator*=;
        using DSTBase::operator/=;

    public:
        /**
         * TODO : Documentation.
         */
        inline float to_angle() const
        {
            return std::atan2f(x, y);
        }
    };

    static_assert(
        sizeof(Vector2) == sizeof(glm::vec2),
        "sizeof(Vector2) must equal sizeof(glm::vec2)"
    );

} // namespace Dynamic_Static
