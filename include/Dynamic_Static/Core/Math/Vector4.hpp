
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

    static_assert(
        sizeof(Vector4) == sizeof(glm::vec4),
        "sizeof(Vector4) must equal sizeof(glm::vec4)"
    );

} // namespace Dynamic_Static
