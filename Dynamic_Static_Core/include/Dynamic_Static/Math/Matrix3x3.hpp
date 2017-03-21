
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
#include "Dynamic_Static/Math/Vector4.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include "Dynamic_Static/Math/glm/glm.hpp"
#include "Dynamic_Static/Math/glm/gtx/transform.hpp"

#include <array>
#include <string>
#include <ostream>

#define DST_TO_GLM_MAT3(DST_MATRIX3X3) (*reinterpret_cast<glm::mat3*>(&DST_MATRIX3X3))
#define DST_TO_GLM_MAT3_CONST(DST_MATRIX3X3) (*reinterpret_cast<const glm::mat3*>(&DST_MATRIX3X3))

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
            std::array<Vector3, 3> columns;

        public:
            inline Matrix3x3()
                : Matrix3x3(Identity)
            {
            }

            inline Matrix3x3(
                const Vector3& column0,
                const Vector3& column1,
                const Vector3& column2
            )
            {
                columns[0] = column0;
                columns[1] = column1;
                columns[2] = column2;
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
