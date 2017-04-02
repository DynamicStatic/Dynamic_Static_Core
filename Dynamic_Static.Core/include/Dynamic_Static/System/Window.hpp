
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
#include "Dynamic_Static/Core/Version.hpp"
#include "Dynamic_Static/Core/Callback.hpp"

#include "Dynamic_Static/System/Point.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Monitor.hpp"
#include "Dynamic_Static/System/Resolution.hpp"
#include "Dynamic_Static/System/Input.Manager.hpp"

#include <string>

struct GLFWwindow;
namespace Dynamic_Static {
    namespace System {
        class Monitor;

        /**
         * Provides high level control over a system window.
         */
        class Window final
            : public Object {
            friend static void frame_buffer_resize_callback(GLFWwindow*, int, int);
            friend static void keyboard_callback(GLFWwindow*, int, int, int, int);
            friend static void mouse_button_callback(GLFWwindow*, int, int, int);
            friend static void mouse_position_callback(GLFWwindow*, double, double);
            friend static void mouse_scroll_callback(GLFWwindow*, double, double);
        public:
            /**
             * Specifies a rendering API.
             */
            enum class API {
                Vulkan,
                OpenGL,
                OpenGLES,
            };

            /**
             * Specifies cursor modes.
             */
            enum class CursorMode {
                Normal,
                Hidden,
                Disabled,
            };

            /**
             * Specifies construction parameters for a Window.
             */
            class Configuration final {
            public:
                API api { API::Vulkan };
                Version apiVersion { 0, 0, 0 };
                std::string name { "Dynamic_Static" };
                CursorMode cursorMode { CursorMode::Normal };
                Resolution resolution { 1280, 720 };
                Point position { 320, 180 };
                Window* parent { nullptr };
                const Monitor* monitor { nullptr };
                bool decorated { true };
                bool resizable { true };
                bool visible { true };
            };

        private:
            API mAPI { API::Vulkan };
            Version mAPIVersion { 0, 0, 0 };
            Window* mParent { nullptr };
            const Monitor* mMonitor { nullptr };
            Input::Manager mInputManager;
            mutable void* mGLFWHandle { nullptr };

        public:
            /**
             * Callback executed when this Window is resized.
             * @param [in] The Window being resized
             */
            Callback<Window, const Window&> OnResized;

            /**
             * Callback executed when this Window is closed.
             * @param [in] The Window being closed
             */
            Callback<Window, const Window&> OnClosed;

        public:
            /**
             * Constructs an instance of Window.
             */
            Window();

            /**
             * Constructs an instance of Window.
             * @param [in] configuration This Window's Configuration
             */
            Window(const Configuration& configuration);

            /**
             * Moves an instance of Window.
             * @param [in] other The Window to move from
             */
            Window(Window&& other);

            /**
             * Destroys this Window.
             */
            ~Window();

            /**
             * Moves an instance of Window.
             * @param [in] other The Window to move from
             */
            Window& operator=(Window&& other);

        public:
            /**
             * Gets this Window's name.
             * @return This Window's name
             */
            const std::string& name() const final override;

            /**
             * Sets this Window's name.
             * @param [in] name This Window's name
             */
            void name(const std::string& name) final override;

            /**
             * Gets this Window's OS handle.
             * @return This Window's OS handle
             */
            void* handle();

            /**
             * Gets this Window's Input.
             * @return This Window's Input
             */
            const Input& input() const;

            /**
             * Gets this Window's Monitor.
             * @return This Window's Monitor
             */
            const Monitor* monitor() const;

            /**
             * Gets this Window's parent.
             * @return This Window's parent
             */
            const Window* parent() const;

            /**
             * Gets this Window's Window::CursorMode.
             * @return This Window's Window::CursorMode
             */
            Window::CursorMode cursor_mode() const;

            /**
             * Sets this Window's Window::CursorMode.
             * @param [in] cursorMode This Window's Window::CursorMode
             */
            void cursor_mode(Window::CursorMode cursorMode);

            /**
             * Gets this Window's Resolution.
             * @return This Window's Resolution
             */
            Resolution resolution() const;

            /**
             * Sets this Window's Resolution.
             * @param [in] resolution This Window's Resolution
             */
            void resolution(const Resolution& resolution);

            /**
             * Gets this Window's position.
             * @return This Window's position
             */
            Point position() const;

            /**
             * Sets this Window's position.
             * @param [in] position This Window's position
             */
            void position(const Point& position);

            /**
             * Gets a value indicating whether or not this Window is visible.
             * @return Whether or not this Window is visible
             */
            bool visible() const;

            /**
             * Sets a value indicating whether or not this Window is visible.
             * @return Whether or not this Window is visible
             */
            void visible(bool visible);

            /**
             * Makes this Window's OpenGL context current.
             * \n NOTE : If using Vulkan this method is a no-op
             */
            void make_current() const;

            /**
             * Renders this Window.
             * \n NOTE : If using Vulkan this method is a no-op
             * \n NOTE : If not using Vulkan this method must be called periodically to keep this Window up to date
             */
            void render() const;

            /**
             * Updates all Windows' OS events.
             * \n NOTE : This method must be called periodically to keep Windows up to date.
             */
            static void update();

            /**
             * Gets aggregate Input for all Windows
             * @return Aggregate Input for all Windows
             */
            static const Input& aggregate_input();

        private:
            GLFWwindow* glfw_handle() const;
            void fire_on_resized() const;
            void fire_on_closed() const;
        };
    } // namespace System
} // namespace Dynamic_Static
