
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
     * Represents a 3D vector or point.
     */
    struct Vector3
        : public detail::VectorBase<Vector3, glm::vec3>
    {
    public:
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;

    public:
        using DSTBase::DSTBase;
        using DSTBase::operator=;
        using DSTBase::operator+=;
        using DSTBase::operator-=;
        using DSTBase::operator*=;
        using DSTBase::operator/=;
    };

    static_assert(
        sizeof(Vector3) == sizeof(glm::vec3),
        "sizeof(Vector3) must equal sizeof(glm::vec3)"
    );

} // namespace Dynamic_Static
