
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
#include "Dynamic_Static/Math/Vector3.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/glm.hpp>

#include <array>

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of a 3D rotation and scale.
         */
        struct Matrix3x3 final {
        public:
            /**
             * Constant Matrix3x3
             *  [1, 0, 0]
             *  [0, 1, 0]
             *  [0, 0, 1]
             */
            static const Matrix3x3 Identity;

        public:
            union {
                std::array<Vector3, 3> columns;
                // struct {
                //     float m00, m10, m20;
                //     float m01, m11, m21;
                //     float m02, m12, m22;
                // };
            };

        public:
            inline Matrix3x3()
            {
            }

            inline Matrix3x3(
                const Vector3& column0,
                const Vector3& column1,
                const Vector3& column2
            )
            {
            }

            /**
             * Gets the std::string representation of this Matrix3x3.
             */
            inline std::string to_string() const
            {
                return "[TODO : Matrix3x3.to_string()]";
            }
        };

        static_assert(
            sizeof(Matrix3x3) == sizeof(float) * 9,
            "sizeof(Matrix3x3) must equal sizeof(float) * 9"
        );
    } // namespace Math
} // namespace Dynamic_Static

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
