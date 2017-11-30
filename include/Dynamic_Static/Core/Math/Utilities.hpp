
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

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
        v.y = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_down()
    {
        VectorType v { };
        v.y = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_left()
    {
        VectorType v { };
        v.x = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_right()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_forward()
    {
        VectorType v { };
        v.z = -1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType world_backward()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_x()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_y()
    {
        VectorType v { };
        v.y = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_z()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /**
     * TODO : Documentation.
     */
    template <typename VectorType>
    inline VectorType unit_w()
    {
        VectorType v { };
        v.w = 1;
        return v;
    }

} // namespace Dynamic_Static
