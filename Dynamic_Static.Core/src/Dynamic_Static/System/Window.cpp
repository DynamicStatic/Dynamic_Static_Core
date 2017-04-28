
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

#include "Dynamic_Static/System/Window.hpp"
#include "Dynamic_Static/System/Monitor.hpp"
#include "GLFWInclude.hpp"

#include <set>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace Dynamic_Static {
    namespace System {
        static std::set<void*> gGLFWWindowHandles;
        static Input::Manager gAggregateInputManager;
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        static Window& dst_window(GLFWwindow* handle)
        {
            auto glfwWindow = reinterpret_cast<GLFWwindow*>(handle);
            auto dstWindow = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            assert(dstWindow != nullptr);
            return *dstWindow;
        }

        void frame_buffer_resize_callback(GLFWwindow* handle, int, int)
        {
            dst_window(handle).fire_on_resized();
        }

        void keyboard_callback(GLFWwindow* handle, int glfwKey, int /* scanCode */, int action, int /* mods */)
        {
            auto& window = dst_window(handle);
            auto dstKey = glfw_to_dst_keyboard_key(glfwKey);
            switch (action) {
                case GLFW_PRESS:
                    window.mInputManager.keyboard_state().down(dstKey, true);
                    gAggregateInputManager.keyboard_state().down(dstKey, true);
                    break;

                case GLFW_RELEASE:
                    window.mInputManager.keyboard_state().down(dstKey, false);
                    gAggregateInputManager.keyboard_state().down(dstKey, false);
                    break;

                case GLFW_REPEAT:
                    window.mInputManager.keyboard_state().down(dstKey, true);
                    gAggregateInputManager.keyboard_state().down(dstKey, true);
                    break;
            }
        }

        void mouse_button_callback(GLFWwindow* handle, int glfwButton, int action, int /* mods */)
        {
            auto& window = dst_window(handle);
            auto dstButton = glfw_to_dst_mouse_button(glfwButton);
            switch (action) {
                case GLFW_PRESS:
                    window.mInputManager.mouse_state().down(dstButton, true);
                    gAggregateInputManager.mouse_state().down(dstButton, true);
                    break;

                case GLFW_RELEASE:
                    window.mInputManager.mouse_state().down(dstButton, false);
                    gAggregateInputManager.mouse_state().down(dstButton, false);
                    break;

                case GLFW_REPEAT:
                    window.mInputManager.mouse_state().down(dstButton, true);
                    gAggregateInputManager.mouse_state().down(dstButton, true);
                    break;
            }
        }

        void mouse_position_callback(GLFWwindow* handle, double xOffset, double yOffset)
        {
            auto& dstWindow = dst_window(handle);
            float x = static_cast<float>(xOffset);
            float y = static_cast<float>(yOffset);
            auto cursorPosition = math::Vector2 { x, y };
            dstWindow.mInputManager.mouse_state().position(cursorPosition);
            cursorPosition.x += static_cast<float>(dstWindow.position().x);
            cursorPosition.y += static_cast<float>(dstWindow.position().y);
            gAggregateInputManager.mouse_state().position(cursorPosition);
        }

        void mouse_scroll_callback(GLFWwindow* handle, double /* xOffset */, double yOffset)
        {
            auto& inputManager = dst_window(handle).mInputManager;
            auto scroll = inputManager.mouse_state().scroll();
            inputManager.mouse_state().scroll(scroll + static_cast<float>(yOffset));
            auto aggregateScroll = gAggregateInputManager.mouse_state().scroll();
            gAggregateInputManager.mouse_state().scroll(aggregateScroll + static_cast<float>(yOffset));
        }

        static void glfw_error_callback(int error, const char* description)
        {
            // TODO : Setup a logger.
            std::cout << "== GLFW Error " + std::to_string(error) + " : " + std::string(description) << std::endl;
        }

        static void intialize_glfw(const Window::Configuration& configuration)
        {
            if (gGLFWWindowHandles.size() == 0) {
                glfwSetErrorCallback(glfw_error_callback);
                if (!glfwInit()) {
                    throw std::runtime_error("GLFW failed to initialize");
                }

                if (configuration.api == Window::API::Vulkan) {
                    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                } else {
                    if (configuration.api == Window::API::OpenGL) {
                        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
                        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                    }

                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, configuration.apiVersion.major);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, configuration.apiVersion.minor);
                }
            }
        }

        static void terminate_glfw()
        {
            if (gGLFWWindowHandles.size() == 0) {
                glfwTerminate();
            }
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        Window::Window()
            : Window(Configuration { })
        {
        }

        Window::Window(const Configuration& configuration)
            : mAPI { configuration.api }
            , mAPIVersion { configuration.apiVersion }
            , mMonitor { configuration.monitor }
            , mParent { configuration.parent }
        {
            intialize_glfw(configuration);
            mName = configuration.name;
            glfwWindowHint(GLFW_VISIBLE, configuration.visible);
            glfwWindowHint(GLFW_DECORATED, configuration.decorated);
            glfwWindowHint(GLFW_RESIZABLE, configuration.resizable);
            int width = static_cast<int>(configuration.resolution.width);
            int height = static_cast<int>(configuration.resolution.height);

            GLFWmonitor* glfwMonitor = nullptr;
            if (configuration.monitor) {
                glfwMonitor = reinterpret_cast<GLFWmonitor*>(configuration.monitor->mGLFWHandle);
            }

            GLFWwindow* glfwParentWindow = nullptr;
            if (configuration.parent) {
                glfwParentWindow = reinterpret_cast<GLFWwindow*>(configuration.parent->mGLFWHandle);
            }

            mGLFWHandle = glfwCreateWindow(width, height, mName.c_str(), glfwMonitor, glfwParentWindow);
            if (mGLFWHandle) {
                gGLFWWindowHandles.insert(mGLFWHandle);
            } else {
                terminate_glfw();
                throw std::runtime_error("Failed to create Window");
            }

            glfwSetWindowUserPointer(glfw_handle(), this);
            glfwSetFramebufferSizeCallback(glfw_handle(), frame_buffer_resize_callback);
            glfwSetMouseButtonCallback(glfw_handle(), mouse_button_callback);
            glfwSetCursorPosCallback(glfw_handle(), mouse_position_callback);
            glfwSetScrollCallback(glfw_handle(), mouse_scroll_callback);
            glfwSetKeyCallback(glfw_handle(), keyboard_callback);
            cursor_mode(configuration.cursorMode);
            visible(configuration.visible);
        }

        Window::Window(Window&& other)
        {
            *this = std::move(other);
        }

        Window::~Window()
        {
            if (mGLFWHandle) {
                gGLFWWindowHandles.erase(mGLFWHandle);
                glfwDestroyWindow(glfw_handle());
                terminate_glfw();
            }
        }

        Window& Window::operator=(Window&& other)
        {
            if (this != &other) {
                Object::operator=(std::move(other));
                mGLFWHandle = std::move(other.mGLFWHandle);
                mAPI = std::move(other.mAPI);
                mAPIVersion = std::move(other.mAPIVersion);
                mMonitor = std::move(other.mMonitor);
                mParent = std::move(other.mParent);
                mInputManager = std::move(other.mInputManager);
                other.mGLFWHandle = nullptr;
                glfwSetWindowUserPointer(glfw_handle(), this);
            }

            return *this;
        }

        const std::string& Window::name() const
        {
            return mName;
        }

        void Window::name(const std::string& name)
        {
            if (mName != name) {
                mName = name;
                glfwSetWindowTitle(glfw_handle(), mName.c_str());
            }
        }

        void* Window::handle()
        {
            #if defined(DYNAMIC_STATIC_WINDOWS)
            return glfwGetWin32Window(glfw_handle());
            #else
            return nullptr;
            #endif
        }

        const Input& Window::input() const
        {
            return mInputManager.input();
        }

        const Monitor* Window::monitor() const
        {
            // TODO : Use the GLFW handle to look up the dst::Monitor.
            //        This will avoid the need for move notification.
            return mMonitor;
        }

        const Window* Window::parent() const
        {
            // TODO : Use the GLFW handle to look up the dst::Window.
            //        This will avoid the need for move notification.
            return mParent;
        }

        Window::CursorMode Window::cursor_mode() const
        {
            auto cursorMode = CursorMode::Normal;
            switch (glfwGetInputMode(glfw_handle(), GLFW_CURSOR)) {
                case GLFW_CURSOR_NORMAL: cursorMode = CursorMode::Normal; break;
                case GLFW_CURSOR_HIDDEN: cursorMode = CursorMode::Hidden; break;
                case GLFW_CURSOR_DISABLED: cursorMode = CursorMode::Disabled; break;
            }

            return cursorMode;
        }

        void Window::cursor_mode(CursorMode cursorMode)
        {
            auto glfwCursorMode = GLFW_CURSOR_NORMAL;
            switch (cursorMode) {
                case CursorMode::Normal: glfwCursorMode = GLFW_CURSOR_NORMAL; break;
                case CursorMode::Hidden: glfwCursorMode = GLFW_CURSOR_HIDDEN; break;
                case CursorMode::Disabled: glfwCursorMode = GLFW_CURSOR_DISABLED; break;
            }

            glfwSetInputMode(glfw_handle(), GLFW_CURSOR, glfwCursorMode);
        }

        Resolution Window::resolution() const
        {
            int width, height;
            glfwGetWindowSize(glfw_handle(), &width, &height);
            return Resolution {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
            };
        }

        void Window::resolution(const Resolution& resolution)
        {
            int width = static_cast<int>(resolution.width);
            int height = static_cast<int>(resolution.height);
            glfwSetWindowSize(glfw_handle(), width, height);
        }

        Point Window::position() const
        {
            int x, y;
            glfwGetWindowPos(glfw_handle(), &x, &y);
            return Point {
                static_cast<uint32_t>(x),
                static_cast<uint32_t>(y)
            };
        }

        void Window::position(const Point& position)
        {
            int x = static_cast<int>(position.x);
            int y = static_cast<int>(position.y);
            glfwSetWindowPos(glfw_handle(), x, y);
        }

        bool Window::visible() const
        {
            return glfwGetWindowAttrib(glfw_handle(), GLFW_VISIBLE) == 1;
        }

        void Window::visible(bool visible)
        {
            if (this->visible() != visible) {
                if (visible) {
                    glfwShowWindow(glfw_handle());
                } else {
                    glfwHideWindow(glfw_handle());
                }
            }
        }

        void Window::make_current() const
        {
            if (mAPI != API::Vulkan) {
                glfwMakeContextCurrent(glfw_handle());
            }
        }

        void Window::render() const
        {
            if (mAPI != API::Vulkan) {
                glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(mGLFWHandle));
            }
        }

        void Window::update()
        {
            glfwPollEvents();
            gAggregateInputManager.update();
            for (auto glfwHandle : gGLFWWindowHandles) {
                auto& dstWindow = dst_window(reinterpret_cast<GLFWwindow*>(glfwHandle));
                dstWindow.mInputManager.update();
            }
        }

        const Input& Window::aggregate_input()
        {
            return gAggregateInputManager.input();
        }

        GLFWwindow* Window::glfw_handle() const
        {
            return reinterpret_cast<GLFWwindow*>(mGLFWHandle);
        }

        void Window::fire_on_resized() const
        {
            on_resized(*this);
        }

        void Window::fire_on_closed() const
        {
            on_closed(*this);
        }
    } // namespace System
} // namespace Dynamic_Static
