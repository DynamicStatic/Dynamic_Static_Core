
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
#include "Dynamic_Static/Math/Vector4.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif

#include <glm/glm.hpp>

#include <array>

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of a 3D translation, rotation, and scale.
         */
        struct Matrix4x4 final {
        public:
            /**
             * Constant Matrix4x4
             *  [1, 0, 0, 0]
             *  [0, 1, 0, 0]
             *  [0, 0, 1, 0]
             *  [0, 0, 0, 1]
             */
            static const Matrix4x4 Identity;

        public:
            std::array<Vector4, 4> columns;

        public:
            inline Matrix4x4()
                : Matrix4x4(Identity)
            {
            }

            inline Matrix4x4(
                const Vector4& column0,
                const Vector4& column1,
                const Vector4& column2,
                const Vector4& column3
            )
            {
            }

            /**
             * Gets the column at the specified index.
             * @param [in] index The index of the column to get
             * @return The column at the specified index
             */
            inline const Vector4& operator[](size_t index) const
            {
                return columns[index];
            }

            /**
             * Gets the column at the specified index.
             * @param [in] index The index of the column to get
             * @return The column at the specified index
             */
            inline Vector4& operator[](size_t index)
            {
                return columns[index];
            }

        public:
            /**
             * Gets the std::string representation of this Matrix4x4.
             */
            inline std::string to_string() const
            {
                return "[TODO : Matrix4x4.to_string()]";
            }
        };

        static_assert(
            sizeof(Matrix4x4) == sizeof(float) * 16,
            "sizeof(Matrix4x4) must equal sizeof(float) * 16"
        );
    } // namespace Math
} // namespace Dynamic_Static

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif
