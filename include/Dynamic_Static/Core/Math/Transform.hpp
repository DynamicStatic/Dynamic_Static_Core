
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

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
        glm::vec3 scale { 1 };

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
        inline glm::mat4 local_from_world() const
        {
            return glm::transpose(world_from_local());
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
