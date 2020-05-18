#if 0
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

#include "Dynamic_Static/Core/Math/Utilities.hpp"

namespace dst {

    /*!
    Represents a position, rotation, and scale.
    */
    struct Transform
    {
        glm::vec3 translation { };
        glm::quat rotation { 1, 0, 0, 0 };
        glm::vec3 scale { 1 };

        /*!
        Gets a glm::mat4 representing this Transform's world from local matrix.
        @return A glm::mat4 representing this Transform's world from local matrix
        */
        inline glm::mat4 world_from_local() const
        {
            return
                glm::translate(translation) *
                glm::toMat4(rotation) *
                glm::scale(scale);
        }

        /*!
        Gets a glm::mat4 representing this Transform's local from world matrix.
        @return A glm::mat4 representing this Transform's local from world matrix
        */
        inline glm::mat4 local_from_world() const
        {
            return glm::transpose(world_from_local());
        }

        /*!
        Gets a glm::vec3 representing this Transform's up vector in world space.
        @return A glm::vec3 representing this Transform's up vector in world space
        */
        inline glm::vec3 up() const
        {
            return glm::normalize(rotation * dst::world_up<glm::vec3>());
        }

        /*!
        Gets a glm::vec3 representing this Transform's down vector in world space.
        @return A glm::vec3 representing this Transform's down vector in world space
        */
        inline glm::vec3 down() const
        {
            return glm::normalize(rotation * dst::world_down<glm::vec3>());
        }

        /*!
        Gets a glm::vec3 representing this Transform's left vector in world space.
        @return A glm::vec3 representing this Transform's left vector in world space
        */
        inline glm::vec3 left() const
        {
            return glm::normalize(rotation * dst::world_left<glm::vec3>());
        }

        /*!
        Gets a glm::vec3 representing this Transform's right vector in world space.
        @return A glm::vec3 representing this Transform's right vector in world space
        */
        inline glm::vec3 right() const
        {
            return glm::normalize(rotation * dst::world_right<glm::vec3>());
        }

        /*!
        Gets a glm::vec3 representing this Transform's forward vector in world space.
        @return A glm::vec3 representing this Transform's forward vector in world space
        */
        inline glm::vec3 forward() const
        {
            return glm::normalize(rotation * dst::world_forward<glm::vec3>());
        }

        /*!
        Gets a glm::vec3 representing this Transform's backward vector in world space.
        @return A glm::vec3 representing this Transform's backward vector in world space
        */
        inline glm::vec3 backward() const
        {
            return glm::normalize(rotation * dst::world_backward<glm::vec3>());
        }
    };

} // namespace dst

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED
#endif