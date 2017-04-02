
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
#include "Dynamic_Static/System/Point.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Resolution.hpp"

#include <vector>

struct GLFWmonitor;
namespace Dynamic_Static {
    namespace System {
        class Window;

        /**
         * Provides high level control over a system monitor.
         */
        class Monitor final
            : public Object {
            friend class Window;
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
            std::vector<Mode> mModes;
            mutable void* mGLFWHandle { nullptr };

        private:
            Monitor(void* glfwHandle);

        public:
            /**
             * Gets this Monitor's name.
             * @return This Monitor's name
             */
            const std::string& name() const;

            /**
             * Gets this Monitor's current Mode.
             * @return This Monitor's current Mode
             */
            const Mode& mode() const;

            /**
             * Gets all of the Modes supported by this Monitor.
             * @return All of the Modes supported by this Monitor
             */
            const std::vector<Mode>& modes() const;

            /**
             * Gets this Monitor's position.
             * @return This Monitor's position
             */
            Point position() const;

            /**
             * Gets all of the currently attached Monitors.
             * @return All of the currently attached Monitors
             */
            static const std::vector<Monitor>& enumerate_monitors();

        private:
            void name(const std::string& name) final override;
            GLFWmonitor* glfw_handle() const;
        };
    } // namespace System
} // namespace Dynamic_Static
