
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
#include "Dynamic_Static/Core/Math/Vector3.hpp"

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static {

    /**
     * Represents a 3D rotation.
     */
    struct Quaternion
        : public glm::quat
    {
    public:
        static const Quaternion Identity;

    public:
        using glm::quat::tquat;

        /**
         * Constructs an instance of Quaternion.
         */
        inline Quaternion()
        {
            *this = Identity;
        }

        /**
         * Constructs an instance of Quaternion.
         * @param [in] angle The angle to rotate this Quaternion by
         * @param [in] axis  The axis to rotate this Quaternion along
         */
        inline Quaternion(float angle, const Vector3& axis)
        {
            *this = glm::angleAxis(angle, axis);
        }

        /**
         * TODO : Documentation.
         */
        inline operator glm::quat&()
        {
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline operator const glm::quat&() const
        {
            return *this;
        }

    public:
        /**
         * TODO : Documentation.
         */
        inline void normalize()
        {
            *this = glm::normalize(static_cast<glm::quat>(*this));
        }

        /**
         * TODO : Documentation.
         */
        inline Quaternion normalized() const
        {
            return glm::normalize(static_cast<glm::quat>(*this));
        }

        /**
         * Gets the std::string representation of this Quaternion.
         * @return The std::string representation of this Quaternion
         */
        inline std::string to_string() const
        {
            return std::string("TODO : Quaternion::to_string()");
            // return glm::to_string(*this);
        }
    };

    static_assert(
        sizeof(Quaternion) == sizeof(glm::quat),
        "sizeof(Quaternion) must equal sizeof(glm::quat)"
    );

} // namespace Dynamic_Static
