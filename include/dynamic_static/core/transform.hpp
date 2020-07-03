
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#include "dynamic_static/core/math.hpp"

namespace dst {

/**
Represents 3D translation, rotation, and scale
*/
struct Transform
{
    /**
    TODO : Documentation
    */
    inline glm::mat4 world_from_local() const
    {
        return
            glm::translate(translation) *
            glm::toMat4(rotation) *
            glm::scale(scale);
    }

    /**
    TODO : Documentation
    */
    inline glm::mat4 local_from_world() const
    {
        return glm::transpose(world_from_local());
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 up() const
    {
        return glm::normalize(rotation * glm::vec3 { 0.0f, 1.0f, 0.0f });
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 down() const
    {
        return -up();
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 left() const
    {
        return glm::normalize(rotation * glm::vec3 { -1.0f, 0.0f, 0.0f });
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 right() const
    {
        return -left();
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 forward() const
    {
        return glm::normalize(rotation * glm::vec3 { 0.0f, 0.0f, -1.0f });
    }

    /**
    TODO : Documentation
    */
    inline glm::vec3 backward() const
    {
        return -forward();
    }

    glm::vec3 translation { };                     //!< This Transform object's translation
    glm::quat rotation { 1.0f, 0.0f, 0.0f, 0.0f }; //!< This Transform object's rotation
    glm::vec3 scale { 1.0f, 1.0f, 1.0f };          //!< This Transform object's scale
};

} // namespace dst
