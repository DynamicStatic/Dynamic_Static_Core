
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static {

    /**
     * Converts degrees to radians.
     * @param <T>     The type of the value to convert to radians
     * @param degrees The value to convert to radians
     * @return The value converted to radians
     */
    template <typename T>
    T to_radians(const T& degrees)
    {
        return glm::radians(degrees);
    }

    /**
     * Converts radians to degrees.
     * @param <T>     The type of the value to convert to degrees
     * @param radians The value to convert to degrees
     * @return The value converted to degrees
     */
    template <typename T>
    T to_degrees(const T& radians)
    {
        return glm::degrees(radians);
    }

} // namespace Dynamic_Static
