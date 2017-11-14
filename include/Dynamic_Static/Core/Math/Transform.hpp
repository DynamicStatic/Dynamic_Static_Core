
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Core/Math/Quaternion.hpp"
#include "Dynamic_Static/Core/Math/Vector3.hpp"

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    class Transform final
    {
    public:
        Vector3 translation { Vector3::Zero };
        Quaternion rotation { Quaternion::Identity };
        Vector3 scale { Vector3::One };

    public:
        /**
         * TODO : Documentation.
         */
        inline Matrix4x4 world() const
        {
            return Matrix4x4(translation, rotation, scale);
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 up() const
        {
            return Vector4(world() * Vector4::Up).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 down() const
        {
            return Vector4(world() * Vector4::Down).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 left() const
        {
            return Vector4(world() * Vector4::Left).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 right() const
        {
            return Vector4(world() * Vector4::Right).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 forward() const
        {
            return Vector4(world() * Vector4::Forward).normalized();
        }

        /**
         * TODO : Documentation.
         */
        inline Vector3 backward() const
        {
            return Vector4(world() * Vector4::Backward).normalized();
        }
    };

} // namespace Dynamic_Static
