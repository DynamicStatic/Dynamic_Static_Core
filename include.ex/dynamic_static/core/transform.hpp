
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
TODO : Documentation
*/
struct Transform
{
    glm::vec3 translation { };         //!< TODO : Documentation
    glm::quat rotation { 1, 0, 0, 0 }; //!< TODO : Documentation
    glm::vec3 scale { 1, 1, 1 };       //!< TODO : Documentation
};

} // namespace dst
