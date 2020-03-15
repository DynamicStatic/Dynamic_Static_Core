#if 0
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <algorithm>
#include <cmath>

namespace dst {

    /*!
    Rounds a given floating point value to the nearest whole number then casts the result to a given type.
    @param <RT> The type to cast the rounded result to
    @param <T> The type of the value to round and cast
    @param [in] The value to round and cast
    @return The value after rounding and casting
    */
    template <typename RT, typename T>
    inline RT round_cast(const T& value)
    {
        return static_cast<RT>(std::round(value));
    }

    /*!
    Gets a linear interpolation from one given floating point value to another using a 0 - 1 weighting.
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
        /* TLDR :
            std::fma() (fused multiply-add) is commonly implemented as a single
            CPU instruction which will be used if available.  In addition to a
            performance benefit, accuracy is improved since there's no rounding
            performed until std::fma() returns.

            In this lerp function there are 4 rounding errors...
                (static_cast<T>(1) - t) * v0 + t * v1

            ...this version has 3 rounding errors and no guarantee that the
            result equals v1 when t equals 1 due to rounding error...
                v0 + t * (v1 - v0)

            std::fma() computes...
            x * y + z
            so our operation is...
            t * v1 + (-t * v0 + v0)
        */
        return std::fma(t, v1, std::fma(-t, v0, v0));
    }

    /*!
    Gets the first element in a given range that is equal to a given value.
    @param [in] range The range to search
    @param [in] value The value to search for
    @param <RangeType> The type of the range to search
    \n NOTE : RangeType must provide begin() and end() methods
    @param <ValueType> The type of the value to search for
    @return Iterator to the first element equal to the given value
    */
    template <typename RangeType, typename ValueType>
    inline auto find(RangeType& range, const ValueType& value)
    {
        return std::find(range.begin(), range.end(), value);
    }

    /*!
    Gets the first element in a given range that is equal to a given value.
    @param [in] range The range to search
    @param [in] value The value to search for
    @param <RangeType> The type of the range to search
    \n NOTE : RangeType must provide begin() and end() methods
    @param <ValueType> The type of the value to search for
    @return Iterator to the first element equal to the given value
    */
    template <typename RangeType, typename ValueType>
    inline auto find(const RangeType& range, const ValueType& value)
    {
        return std::find(range.begin(), range.end(), value);
    }

} // namespace dst
#endif