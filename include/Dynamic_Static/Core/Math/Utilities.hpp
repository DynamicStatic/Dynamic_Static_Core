
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

namespace dst {

    typedef struct Radians { } radians; /*!< Radians tag for functions operating on angles */
    typedef struct Degrees { } degrees; /*!< Degrees tag for functions operating on angles */

    /*!
    Gets a given glm::vec's aspect ratio.
    @param <VectorType> The glm::vec type of the given glm::vec
    @param <RT> The return type (optional = float)
    @param [in] v The glm::vec to get the aspect ratio of
    @return The aspect ratio of the given glm::vec
    */
    template <typename VectorType, typename RT = float>
    inline RT aspect_ratio(const VectorType& v)
    {
        auto w = static_cast<RT>(v[0]);
        auto h = static_cast<RT>(v[1]);
        return h != 0 ? w / h : 0;
    }

    /*!
    Wraps an angle to the range [0, 2Pi].
    @param [in] angle The angle to wrap
    @param [tag dispatch dst::radians]
    @return The wrapped angle
    */
    template <typename T>
    inline T wrap_angle(const T& angle, const Radians&)
    {
        auto twoPi = glm::two_pi<T>();
        T wrappedAngle = std::fmod(angle, twoPi);
        return wrappedAngle < 0 ? wrappedAngle : wrappedAngle + twoPi;
    }

    /*!
    Gets the Cartesian coordinate of a given polar coordinate.
    @param [in] r The radial distance from the origin
    @param [in] theta The counterclockwise angle from the x axis
    @return The Cartesian coordinate of the given polar coordinate
    */
    inline glm::vec2 polar_to_cartesian(float r, float theta)
    {
        return glm::vec2(std::cos(theta), std::sin(theta)) * r;
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

} // namespace dst

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED
