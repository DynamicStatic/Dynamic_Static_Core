
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
#include "Dynamic_Static/Math/Vector2.hpp"

#include <type_traits>

namespace Dynamic_Static {
    namespace Math {
        /**
         * Representation of a 2D axis aligned rectangle.
         */
        struct Rectangle final {
        public:
            float width { 0 };
            float height { 0 };
            Vector2 position;

        public:
            inline Rectangle(float width, float height)
                : width { width }
                , height { height }
            {
            }

            inline Rectangle(float width, float height, const Vector2& position)
                : width { width }
                , height { height }
                , position { position }
            {
            }

            /**
             * Copies an instance of Rectangle.
             * @param [in] other The Rectangle to copy from
             */
            Rectangle(const Rectangle& other) = default;

            /**
             * Moves an instance of Rectangle.
             * @param [in] other The Rectangle to move from
             */
            Rectangle(Rectangle&& other) = default;

            /**
             * Copies an instance of Rectangle.
             * @param [in] other The Rectangle to copy from
             */
            Rectangle& operator=(const Rectangle& other) = default;

            /**
             * Moves an instance of Rectangle.
             * @param [in] other The Rectangle to move from
             */
            Rectangle& operator=(Rectangle&& other) = default;

        public:
            /**
             * Gets this Rectangle's top edge.
             * @return This Rectangle's top edge
             */
            inline float top() const
            {
                return position.y + height * 0.5f;
            }

            /**
             * Gets this Rectangle's left edge.
             * @return This Rectangle's left edge
             */
            inline float left() const
            {
                return position.x - width * 0.5f;
            }

            /**
             * Gets this Rectangle's right edge.
             * @return This Rectangle's right edge
             */
            inline float right() const
            {
                return position.x + width * 0.5f;
            }

            /**
             * Gets this Rectangle's bottom edge.
             * @return This Rectangle's bottom edge
             */
            inline float bottom() const
            {
                return position.y - height * 0.5f;
            }

            /**
             * Gets this Rectangle's area.
             * @return This Rectangle's area
             */
            inline float area() const
            {
                return width * height;
            }
        };

        static_assert(
            sizeof(Rectangle) == sizeof(float) * 4,
            "sizeof(Rectangle) must equal sizeof(float) * 4"
        );

        /**
         * Gets a value indicating whether or not two specified Rectangles are equal.
         * @param [in] v0 The first Rectangles
         * @param [in] v1 The second Rectangles
         * @return whether or not the two specified Rectangles are equal
         */
        inline bool operator==(const Rectangle& r0, const Rectangle& r1)
        {
            return r0.width == r1.width;
        }

        /**
         * Gets a value indicating whether or not two specified Rectangles are inequal.
         * @param [in] v0 The first Rectangles
         * @param [in] v1 The second Rectangles
         * @return whether or not the two specified Rectangles are inequal
         */
        inline bool operator!=(const Rectangle& r0, const Rectangle& r1)
        {
            return !(r0 == r1);
        }
    } // namespace Math
} // namespace Dynamic_Static
