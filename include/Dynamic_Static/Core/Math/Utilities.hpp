
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Math/Defines.hpp"

namespace Dynamic_Static {

    /**
    * TODO : Documentation.
    */
    template <typename T>
    inline T wrap_angle(const T& angle)
    {
        T twoPi = static_cast<T>(M_PI * 2);
        T wrappedAngle = std::fmod(angle, twoPi);
        return wrappedAngle < 0 ? wrappedAngle : wrappedAngle + twoPi;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_up()
    {
        VectorType v { };
        v[1] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_down()
    {
        VectorType v { };
        v[1] = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_left()
    {
        VectorType v { };
        v[0] = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_right()
    {
        VectorType v { };
        v[0] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_forward()
    {
        VectorType v { };
        v[2] = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_backward()
    {
        VectorType v { };
        v[2] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_x()
    {
        VectorType v { };
        v[0] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_y()
    {
        VectorType v { };
        v[1] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_z()
    {
        VectorType v { };
        v[2] = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_w()
    {
        VectorType v { };
        v[3] = 1;
        return v;
    }

} // namespace Dynamic_Static

#endif





#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

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
    inline T to_radians(const T& degrees)
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
    inline T to_degrees(const T& radians)
    {
        return glm::degrees(radians);
    }

    /**
     * TODO : Documentation.
     */
    template <typename T>
    inline T wrap_radians(const T& angle)
    {
        T twoPi = static_cast<T>(M_PI * 2);
        T wrappedAngle = std::fmod(angle, twoPi);
        return wrappedAngle < 0 ? wrappedAngle : wrappedAngle + twoPi;
    }

} // namespace Dynamic_Static

#endif
