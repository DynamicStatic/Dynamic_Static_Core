
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

#include "Dynamic_Static/Math/Defines.hpp"

#pragma warning(push, 0)
#include "Dynamic_Static/Math/glm/glm.hpp"
#pragma warning(pop)

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        struct Matrix4x4 final
            : public glm::mat4x4 {
            using glm::mat4x4::tmat4x4;

            /**
             * Constructs an instance of Matrix4x4.
             */
            Matrix4x4() = default;

            /**
             * TODO : Documentation.
             */
            Matrix4x4(const glm::mat4x4& other);

            /**
             * TODO : Documentation.
             */
            Matrix4x4& operator=(const glm::mat4x4& other);

            /**
             * TODO : Documentation.
             */
            void rotate(float angle, const Vector3& axis);

            /**
             * TODO : Documentation.
             */
            void look_at(const Vector3& eye, const Vector3& center, const Vector3& up);

            /**
             * TODO : Documentation.
             */
            static Matrix4x4 perspective(float fov_y, float aspect_ratio, float near_plane, float far_plane);
        };

        static_assert(
            sizeof(Matrix4x4) == sizeof(float) * 16,
            "sizeof(Matrix4x4) must equal sizeof(float) * 16"
        );
    }
}
