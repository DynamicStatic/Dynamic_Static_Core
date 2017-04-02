
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

#include "Dynamic_Static/System/Defines.hpp"

#include <string>

namespace Dynamic_Static {
    namespace System {
        /**
         * Represents a width and height.
         */
        struct Resolution final {
        public:
            uint32_t width { 0 };
            uint32_t height { 0 };

        public:
            /**
             * Constructs an instance of Resolution.
             * @param [in, optional] width This Resolution's width
             * @param [in, optional] height Thie Resolution's height
             */
            Resolution(uint32_t width = 0, uint32_t height = 0);

            /**
             * Copies an instance of Resolution.
             * @param [in] other The Resolution to copy from
             */
            Resolution(const Resolution& other) = default;

            /**
             * Copies an instance of Resolution.
             * @param [in] other The Resolution to copy from
             */
            Resolution& operator=(const Resolution& other) = default;

        public:
            /**
             * Gets this Resolution's aspect ratio.
             * @return This Resolution's aspect ratio
             */
            float aspect_ratio() const;

            /**
             * Gets this Resolution's std::string representation.
             * @return This Resolution's std::string representation
             */
            std::string to_string() const;
        };

        /**
         * Gets a value indicating whether or not two specified Resolutions are equal.
         * @param [in] lhs The first Resolution
         * @param [in] rhs The second Resolution
         * @return Whether or not two specified Resolutions are equal
         */
        bool operator==(const Resolution& lhs, const Resolution& rhs);

        /**
         * Gets a value indicating whether or not two specified Resolutions are inequal.
         * @param [in] lhs The first Resolution
         * @param [in] rhs The second Resolution
         * @return Whether or not two specified Resolutions are inequal
         */
        bool operator!=(const Resolution& lhs, const Resolution& rhs);
    } // namespace System
} // namespace Dynamic_Static
