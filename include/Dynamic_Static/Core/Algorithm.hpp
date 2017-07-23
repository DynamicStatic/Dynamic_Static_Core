
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/TypeUtilities.hpp"

#include <algorithm>
#include <cmath>

namespace Dynamic_Static {

    /**
     * Rounds a given floating point value to the nearest whole number then casts the result to a given type.
     * @param <RT> The type to cast the rounded result to
     * @param <T>  The type of the value to round and cast
     * @param [in] The value to round and cast
     * @return The value after rounding and casting
     */
    template <typename RT, typename T>
    inline RT round_cast(T value)
    {
        return static_cast<RT>(std::round(value));
    }

    /**
     * Gets a value clamped to a given range.
     * @param <T>        The type of the value to clamp
     * @param [in] value The value to clamp
     * @param [in] min   The minimum value
     * @param [in] max   The maximum value
     * @return The value clamped into the range [minimum, maximum]
     */
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, T>::type
        clamp(T value, T min, T max)
    {
        return std::min(std::max(min, value), max);
    }

    /**
     * Gets a value clamped to a given range.
     * @param <T>        The type of the value to clamp
     * @param [in] value The value to clamp
     * @param [in] min   The minimum value
     * @param [in] max   The maximum value
     * @return The value clamped into the range [minimum, maximum]
     */
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, T>::type
        clamp(T value, T min, T max)
    {
        return std::fmin(std::fmax(min, value), max);
    }

    /**
     * Gets a linear interpolation from one given floating point value to another using a 0 - 1 weighting.
     * @param <T>     The type of the value to interpolate
     * @param [in] v0 The value to interpolate from
     * @param [in] v1 The value to interpolate to
     * @param [in] t  The weight of the interpolation
     * @return The interpolated value
     */
    template <typename T>
    inline T lerp(T v0, T v1, T t)
    {
        // FROM : https://devblogs.nvidia.com/parallelforall/lerp-faster-cuda/
        // TLDR : std::fma() (fused multiply-add) is commonly implemented as a
        //        single CPU instruction which will be used if available.  In
        //        addition to a performance benefit, accuracy is improved since
        //        there is no rounding performed until std::fma() returns.
        //
        //        Consider...
        //        (static_cast<T>(1) - t) * v0 + t * v1
        //        and...
        //        v0 + t * (v1 - v0)
        //        The first form incurs 4 rounding errors and the second 3.
        //        Note that the second form cannot guarantee that the value
        //        returned equals v1 when t equals 1 due to rounding error.
        //
        //        std::fma() computes...
        //        x * y + z
        //        so our operation is...
        //        t * v1 + (-t * v0 + v0)

        return std::fma(t, v1, std::fma(-t, v0, v0));
    }

} // namespace Dynamic_Static
