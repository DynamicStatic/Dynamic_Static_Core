
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

#include <cmath>

namespace Dynamic_Static {

    typedef struct Radians { } radians; /*!< Radians tag for functions operating on angles */
    typedef struct Degrees { } degrees; /*!< Degrees tag for functions operating on angles */

    /*!
    Wraps an angle to the range [0, 2Pi].
    @param [in] angle The angle to wrap
    @param [tag dispatch dst::radians]
    @return The wrapped angle
    */
    template <typename T>
    inline T wrap_angle(const T& angle, const Radians&)
    {
        T twoPi = static_cast<T>(M_PI * 2);
        T wrappedAngle = std::fmod(angle, twoPi);
        return wrappedAngle < 0 ? wrappedAngle : wrappedAngle + twoPi;
    }

    /*!
    Gets the world left vector; (-1, 0), (-1, 0, 0), or (-1, 0, 0, 0).
    @return The world left vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_left()
    {
        VectorType v { };
        v.x = -1;
        return v;
    }

    /*!
    Gets the world right vector; (1, 0), (1, 0, 0), or (1, 0, 0, 0).
    @return The world right vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_right()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /*!
    Gets the world up vector; (0, 1), (0, 1, 0), or (0, 1, 0, 0).
    @return The world up vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_up()
    {
        VectorType v { };
        v.y = 1;
        return v;
    }

    /*!
    Gets the world down vector; (0, -1), (0, -1, 0), or (0, -1, 0, 0).
    @return The world down vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_down()
    {
        VectorType v { };
        v.y = -1;
        return v;
    }

    /*!
    Gets the world forward vector; (0, 0, -1) or (0, 0, -1, 0).
    @return The world forward vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_forward()
    {
        VectorType v { };
        v.z = -1;
        return v;
    }

    /*!
    Gets the world backward vector; (0, 0, 1) or (0, 0, 1, 0).
    @return The world backward vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_backward()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /*!
    Gets a 2, 3, or 4 component vector with its x component set to 1; (1, 0), (1, 0, 0), or (1, 0, 0, 0).
    @return The 2, 3, or 4 component vector with its x component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_x()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /*!
    Gets a 2, 3, or 4 component vector with its y component set to 1; (0, 1), (0, 1, 0), or (0, 1, 0, 0).
    @return The 2, 3, or 4 component vector with its y component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_y()
    {
        VectorType v { };
        v.y = 1;
        return v;
    }

    /*!
    Gets a 3 or 4 component vector with its z component set to 1; (0, 0, 1) or (0, 0, 1, 0).
    @return The 3 or 4 component vector with its z component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_z()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /*!
    Gets a 4 component vector with its w component set to 1; (0, 0, 0, 1).
    @return The 4 component vector with its w component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_w()
    {
        VectorType v { };
        v.w = 1;
        return v;
    }

} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED
