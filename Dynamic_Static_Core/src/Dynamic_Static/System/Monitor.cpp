
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

#include "Dynamic_Static/System/Monitor.hpp"

#include "GLFWInclude.hpp"

namespace Dynamic_Static {
    namespace System {
        static Monitor::Mode create_mode(GLFWvidmode videoMode)
        {
            Resolution resolution {
                static_cast<uint32_t>(videoMode.width),
                static_cast<uint32_t>(videoMode.height)
            };

            return Monitor::Mode {
                resolution,
                static_cast<uint32_t>(videoMode.redBits),
                static_cast<uint32_t>(videoMode.greenBits),
                static_cast<uint32_t>(videoMode.blueBits),
                static_cast<uint32_t>(videoMode.refreshRate),
            };
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        Monitor::Monitor(void* glfwHandle)
            : mGLFWHandle { glfwHandle }
        {
            int modeCount;
            const GLFWvidmode* videoModes = glfwGetVideoModes(glfw_handle(), &modeCount);
            mModes.reserve(modeCount);
            for (int i = 0; i < modeCount; ++i) {
                mModes.push_back(create_mode(videoModes[i]));
            }

            mMode = create_mode(*glfwGetVideoMode(glfw_handle()));
            mName = glfwGetMonitorName(glfw_handle());
        }

        const Monitor::Mode& Monitor::mode() const
        {
            return mMode;
        }

        const std::vector<Monitor::Mode>& Monitor::modes() const
        {
            return mModes;
        }

        Point Monitor::position() const
        {
            int x, y;
            glfwGetMonitorPos(glfw_handle(), &x, &y);
            return Point {
                static_cast<uint32_t>(x),
                static_cast<uint32_t>(y)
            };
        }

        void Monitor::name(const std::string& /* name */)
        {
            // NOPE :
        }

        GLFWmonitor* Monitor::glfw_handle() const
        {
            return reinterpret_cast<GLFWmonitor*>(mGLFWHandle);
        }

        const std::vector<Monitor>& Monitor::enumerate_monitors()
        {
            static const std::vector<Monitor> sMonitors(
                []()
                {
                    std::vector<Monitor> monitors;
                    int monitorCount;
                    GLFWmonitor** glfwMonitors = glfwGetMonitors(&monitorCount);
                    monitors.reserve(monitorCount);
                    for (int i = 0; i < monitorCount; ++i) {
                        monitors.push_back(Monitor(glfwMonitors[i]));
                    }

                    return monitors;
                }()
            );

            return sMonitors;
        }
    } // namespace System
} // namespace Dynamic_Static
