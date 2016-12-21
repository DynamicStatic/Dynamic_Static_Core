
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Collection.hpp"

#include <cmath>
#include <algorithm>
#include <type_traits>
#include <initializer_list>

namespace Dynamic_Static {
    /**
     * Gets a value clamped to a specified range.
     * @param <T>        The type of the value
     * @param [in] value The value to clamp
     * @param [in] min   The minimum value [inclusive]
     * @param [in] max   The maximum value [inclusive]
     * @return The value clamped into the range [minimum, maximum]
     */
    template <typename T>
    inline const T& clamp(const T& value, const T& min, const T& max)
    {
        // TODO : Fully specialize this for built in floating point
        //        types so we can take advantage of std::fmin() and
        //        std::fmax() which gracefully handle NaNs.
        return std::min(std::max(min, value), max);
    }

    /**
     * Gets a value clamped to a specified range.
     * @param <T>        The type of the value
     * @param [in] value The value to clamp
     * @param [in] range The values to generate the clamp range from
     *                   \n NOTE : These values can be unsorted
     * @return The value clamped into the specified range
     */
    template <typename T>
    inline const T& clamp(const T& value, const Collection<T>& range)
    {
        // TODO : Fully specialize this for built in floating point
        //        types so we can take advantage of std::fmin() and
        //        std::fmax() which gracefully handle NaNs.
        const T* min = &value;
        const T* max = &value;
        for (const auto& r : range) {
            min = &std::min(*min, r);
            max = &std::max(*max, r);
        }

        return clamp(value, *min, *max);
    }

    /**
     * Gets a value linearly interpolated between two values by a specified weight.
     * \n NOTE : This function can only be used with built in floating point types
     * @param <T>      The type of the value
     * @param [in] v_0 The value to interpolate from
     * @param [in] v_1 The value to interpolate towards
     * @param [in] s   The weight of the interpolation
     * @return The result of the linear interpolation
     */
    template <typename T>
    inline T lerp(T v_0, T v_1, T t)
    {
        static_assert(
            std::is_floating_point<T>::value,
            "Dynamic_Static::lerp() can only be used with built in floating point types"
        );

        // FROM : https://devblogs.nvidia.com/parallelforall/lerp-faster-cuda/
        // TLDR : std::fma() (fused multiply-add) is commonly implemented as a
        //        single CPU instruction which will be used if available.  In
        //        addition to a performance benefit, accuracy is improved since
        //        there is no rounding performed until std::fma() returns.
        //
        //        Consider...
        //        (static_cast<T>(1) - t) * v_0 + t * v_1
        //        and...
        //        v_0 + t * (v_1 - v_0)
        //        The first form incurs 4 rounding errors and the second 3.
        //        Note that the second form cannot guarantee that the value
        //        returned equals v_0 when t equals 1 due to rounding error.
        //
        //        std::fma() computes...
        //        x * y + z
        //        so our operation is...
        //        t * v_1 + (-t * v_0 + v_0)

        return std::fma(t, v_1, std::fma(-t, v_0, v_0));
    }
}
