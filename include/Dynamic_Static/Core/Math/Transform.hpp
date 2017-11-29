
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Utilities.hpp"

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    struct Transform final
    {
        glm::vec3 translation { };
        glm::quat rotation { 1, 0, 0, 0 };
        glm::vec3 scale { };

        /**
         * TODO : Documentation.
         */
        inline glm::mat4 world_from_local() const
        {
            return
                glm::translate(translation) *
                glm::toMat4(rotation) *
                glm::scale(scale);
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 up() const
        {
            return glm::normalize(rotation * dst::world_up<glm::vec3>());
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 down() const
        {
            return glm::normalize(rotation * dst::world_down<glm::vec3>());
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 left() const
        {
            return glm::normalize(rotation * dst::world_left<glm::vec3>());
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 right() const
        {
            return glm::normalize(rotation * dst::world_right<glm::vec3>());
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 forward() const
        {
            return glm::normalize(rotation * dst::world_forward<glm::vec3>());
        }

        /**
         * TODO : Documentation.
         */
        inline glm::vec3 backward() const
        {
            return glm::normalize(rotation * dst::world_backward<glm::vec3>());
        }
    };

} // namespace Dynamic_Static

#endif





#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Core/Math/Quaternion.hpp"
#include "Dynamic_Static/Core/Math/Vector3.hpp"

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    class Transform final
    {
    public:
        Vector3 translation { Vector3::Zero };
        Quaternion rotation { Quaternion::Identity };
        Vector3 scale { Vector3::One };

    public:
        /**
         * TODO : Documentation.
         */
        inline Matrix4x4 world() const
        {
            return Matrix4x4(translation, rotation, scale);
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 up() const
        {
            return Vector4(world() * Vector4::Up).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 down() const
        {
            return Vector4(world() * Vector4::Down).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 left() const
        {
            return Vector4(world() * Vector4::Left).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 right() const
        {
            return Vector4(world() * Vector4::Right).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 forward() const
        {
            return Vector4(world() * Vector4::Forward).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 backward() const
        {
            return Vector4(world() * Vector4::Backward).normalized();
        }
    };

} // namespace Dynamic_Static

#endif
