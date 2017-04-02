
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

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

namespace Dynamic_Static {
    namespace Math {
        struct AxisAlignedBoundingBox2D;
        struct AxisAlignedBoundingBox3D;
        struct Color;
        struct Matrix3x3;
        struct Matrix4x4;
        struct OrientedBoundingBox2D;
        struct OrientedBoundingBox3D;
        struct Quaternion;
        struct Vector2;
        struct Vector3;
        struct Vector4;
        struct Transform;
        struct Rectangle;
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
#define DYNAMIC_STATIC_MATH_TYPEDEFS                                  \
using AxisAlignedBoundingBox2D = dst::math::AxisAlignedBoundingBox2D; \
using AxisAlignedBoundingBox3D = dst::math::AxisAlignedBoundingBox3D; \
using Color                    = dst::math::Color;                    \
using Matrix3x3                = dst::math::Matrix3x3;                \
using Matrix4x4                = dst::math::Matrix4x4;                \
using OrientedBoundingBox2D    = dst::math::OrientedBoundingBox2D;    \
using OrientedBoundingBox3D    = dst::math::OrientedBoundingBox3D;    \
using Quaternion               = dst::math::Quaternion;               \
using Rectangle                = dst::math::Rectangle;                \
using Transform                = dst::math::Transform;                \
using Vector2                  = dst::math::Vector2;                  \
using Vector3                  = dst::math::Vector3;                  \
using Vector4                  = dst::math::Vector4;
