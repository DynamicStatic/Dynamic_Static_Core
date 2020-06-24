
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

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#ifdef DYNAMIC_STATIC_COMPILER_MSVC
#pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"
#ifdef DYNAMIC_STATIC_COMPILER_MSVC
#pragma warning(pop)
#endif

#define _USE_MATH_DEFINES
#include <cmath>

namespace dst {

/**
Gets a 2, 3, or 4 component vector with its x component set to 1
@param <VectorType> TODO : Documentation
@return The 2, 3, or 4 component vector with its x component set to 1
*/
template <typename GlmVectorType>
inline constexpr GlmVectorType unit_x()
{
    return { 1 };
}

/**
Gets a 2, 3, or 4 component vector with its y component set to 1
@param <VectorType> TODO : Documentation
@return The 2, 3, or 4 component vector with its y component set to 1
*/
template <typename GlmVectorType>
inline constexpr GlmVectorType unit_y()
{
    return { 0, 1 };
}

/**
Gets a 3 or 4 component vector with its z component set to 1
@param <VectorType> TODO : Documentation
@return The 3 or 4 component vector with its z component set to 1
*/
template <typename GlmVectorType>
inline constexpr GlmVectorType unit_z()
{
    return { 0, 0, 1 };
}

/**
Gets a 4 component vector with its w component set to 1
@param <VectorType> TODO : Documentation
@return The 4 component vector with its w component set to 1
*/
template <typename GlmVectorType>
inline constexpr GlmVectorType unit_w()
{
    return { 0, 0, 0, 1 };
}

/**
Gets a given glm::vec<> object's aspect ratio
@param <VectorType> The type of the given glm::vec<>
@param <ReturnType>(optional = float) The return type
@param [in] vector The glm::vec<> to get the aspect ratio of
@return The aspect ratio of the given glm::vec<>
*/
template <typename GlmVectorType, typename ReturnType = float>
inline ReturnType aspect_ratio(const GlmVectorType& vector)
{
    auto width = (double)vector[0];
    auto height = (double)vector[1];
    return (ReturnType)(height != 0.0 ? width / height : 0.0);
}

} // namespace dst
