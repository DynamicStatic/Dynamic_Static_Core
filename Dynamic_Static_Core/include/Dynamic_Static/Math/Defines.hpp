
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

#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

namespace Dynamic_Static {
    namespace Math {
        struct AxisAlignedBoundingBox2D;
        struct AxisAlignedBoundingBox3D;
        struct Matrix3x3;
        struct Matrix4x4;
        struct OrientedBoundingBox2D;
        struct OrientedBoundingBox3D;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
        struct Transform;
        //template <typename T> struct Rectangle;
    } // namespace Math

    /**
     * Alias for the Dynamic_Static::Math namespace.
     */
    namespace math = Math;
} // namespace Dynamic_Static

/**
 * Use this macro to typedef dst::math objects into another namespace.
 * \n NOTE : This macro can only be used once per namespace
 */
#define DYNAMIC_STATIC_MATH_TYPEDEFS                                   \
typedef dst::math::AxisAlignedBoundingBox2D  AxisAlignedBoundingBox2D; \
typedef dst::math::AxisAlignedBoundingBox3D  AxisAlignedBoundingBox3D; \
typedef dst::math::Matrix3x3                 Matrix3x3;                \
typedef dst::math::Matrix4x4                 Matrix4x4;                \
typedef dst::math::OrientedBoundingBox2D     OrientedBoundingBox2D;    \
typedef dst::math::OrientedBoundingBox3D     OrientedBoundingBox3D;    \
typedef dst::math::Quaternion                Quaternion;               \
typedef dst::math::Vector2                   Vector2;                  \
typedef dst::math::Vector3                   Vector3;                  \
typedef dst::math::Vector4                   Vector4;                  \
typedef dst::math::Transform                 Transform;                //\
//template <typename T> using Rectangle<T> = dst::math::Rectangle<T>;
