
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/math/defines.hpp"

namespace dst {

/**
Gets a given glm::vec object's aspect ratio
@param <VectorType> The type of the given glm::vec
@param <ReturnType, default = float> The return type
@param [in] vector The glm::vec to get the aspect ratio of
@return The aspect ratio of the given glm::vec
*/
template <typename VectorType, typename ReturnType = float>
inline ReturnType aspect_ratio(const VectorType& vector)
{
    auto width = static_cast<ReturnType>(vector[0]);
    auto height = static_cast<ReturnType>(vector[1]);
    return height != 0 ? width / height : 0;
}

} // namespace dst
