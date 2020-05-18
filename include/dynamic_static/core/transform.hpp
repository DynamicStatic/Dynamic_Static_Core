
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
    glm::vec3 translation { };         //!< This Transform object's translation
    glm::quat rotation { 1, 0, 0, 0 }; //!< This Transform object's rotation
    glm::vec3 scale { 1, 1, 1 };       //!< This Transform object's scale
};

} // namespace dst
