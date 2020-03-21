
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <algorithm>

namespace dst {

/**
TODO : Documentation
*/
template <typename T>
inline const T& clamp(const T& value, const T& min, const T& max)
{
    return std::max(min, std::min(value, max));
}

/**
Gets a linear interpolation from one given floating point value to another using a 0 - 1 weighting
@param <T> The type of the value to interpolate
@param [in] v0 The value to interpolate from
@param [in] v1 The value to interpolate to
@param [in] t The weight of the interpolation
@return The interpolated value
*/
template <typename T>
inline T lerp(T v0, T v1, T t)
{
    // FROM : https://devblogs.nvidia.com/parallelforall/lerp-faster-cuda/
    // TLDR :
    //  std::fma() (fused multiply-add) is commonly implemented as a single CPU
    //  instruction which will be used if available.  In addition to a performance
    //  benefit accuracy is improved since there's no rounding performed until
    //  std::fma() returns.
    //
    //  In this lerp function there are 4 rounding errors...
    //      (static_cast<T>(1) - t) * v0 + t * v1
    //
    //  ...this version has 3 rounding errors and no guarantee that the result
    //  equals v1 when t equals 1 due to rounding error...
    //      v0 + t * (v1 - v0)
    //
    //  std::fma() computes...
    //  x * y + z
    //  so our operation is...
    //  t * v1 + (-t * v0 + v0)
    //
    return std::fma(t, v1, std::fma(-t, v0, v0));
}

/**
Rounds a given floating point value to the nearest whole number then casts the result to a given type
@param <ReturnType> The type to cast the rounded result to
@param <T> The type of the value to round and cast
@param [in] The value to round and cast
@return The value after rounding and casting
*/
template <typename ReturnType, typename T>
inline ReturnType round_cast(const T& value)
{
    return static_cast<ReturnType>(std::round(value));
}

} // namespace dst
