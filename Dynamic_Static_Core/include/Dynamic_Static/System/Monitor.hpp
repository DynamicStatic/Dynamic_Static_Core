
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

#include "Dynamic_Static/Core/Object.hpp"
#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Resolution.hpp"

#include <vector>

namespace Dynamic_Static {
    namespace System {
        /**
         * Provides high level control over a system monitor.
         */
        class Monitor final
            : public Object {
        public:
            /**
             * Represents a Monitor mode line.
             */
            struct Mode final {
            public:
                Resolution resolution;
                uint32_t redBits;
                uint32_t greenBits;
                uint32_t blueBits;
                uint32_t refreshRate;

            public:
                /**
                 * Gets this Monitor::Mode's std::string representation.
                 * @return This Monitor::Mode's std::string representation
                 */
                std::string to_string() const;
            };

        private:
            Mode mMode;
            math::Vector2 mPosition;
            std::vector<Mode> mModes;

        public:
            const Mode& mode() const;

            const std::vector<Mode>& modes() const;

            const Resolution& resolution() const;

            const math::Vector2 position() const;

            void position(const math::Vector2& position);

            static std::vector<Monitor*> enumerate_monitors();
        };
    } // namespace System
} // namespace Dynamic_Static
