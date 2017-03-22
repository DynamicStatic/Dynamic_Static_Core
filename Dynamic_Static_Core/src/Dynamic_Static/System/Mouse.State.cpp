
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

#include "Dynamic_Static/System/Mouse.hpp"

namespace Dynamic_Static {
    namespace System {
        float Mouse::State::scroll() const
        {
            return mScroll;
        }

        void Mouse::State::scroll(float scroll)
        {
            mScroll = scroll;
        }

        const math::Vector2& Mouse::State::position() const
        {
            return mPosition;
        }

        void Mouse::State::position(const math::Vector2 & position)
        {
            mPosition = position;
        }

        bool Mouse::State::down(Button button) const
        {
            return mButtons[static_cast<size_t>(button)];
        }

        void Mouse::State::down(Button button, bool down)
        {
            if (button != Button::Unknown) {
                mButtons[static_cast<size_t>(button)] = down ? 1 : 0;
            }
        }

        bool Mouse::State::up(Button button) const
        {
            return !down(button);
        }

        void Mouse::State::reset()
        {
            mScroll = 0;
            mButtons.reset();
            mPosition = math::Vector2::Zero;
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton)
        {
            auto button = Mouse::Button::Unknown;
            switch (glfwMouseButton) {
                case /* GLFW_MOUSE_BUTTON_LEFT   */ 0: button = Mouse::Button::Left; break;
                case /* GLFW_MOUSE_BUTTON_RIGHT  */ 1: button = Mouse::Button::Right; break;
                case /* GLFW_MOUSE_BUTTON_MIDDLE */ 2: button = Mouse::Button::Middle; break;
                // case /* GLFW_MOUSE_BUTTON_4      */ 3: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_5      */ 4: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_6      */ 5: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_7      */ 6: button = Mouse::Button::Unknown; break;
                // case /* GLFW_MOUSE_BUTTON_LAST   */ 7: button = Mouse::Button::Unknown; break;
                default: button = Mouse::Button::Unknown;
            }

            return button;
        }
    } // namespace System
} // namespace Dynamic_Static
