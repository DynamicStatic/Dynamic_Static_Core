
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

#if defined(DYNAMIC_STATIC_WINDOWS)
#include "Dynamic_Static/System/Win32LeanAndMean.hpp"
#endif

namespace Dynamic_Static {
    namespace System {
        float Mouse::x() const { return mCurrent.x(); }
        float Mouse::y() const { return mCurrent.y(); }
        float Mouse::delta_x() const { return mCurrent.x() - mPrevious.x(); }
        float Mouse::delta_y() const { return mCurrent.y() - mPrevious.y(); }
        float Mouse::scroll() const { return mCurrent.scroll() - mPrevious.scroll(); }

        bool Mouse::up(Button button) const
        {
            return mCurrent.up(button);
        }

        bool Mouse::down(Button button) const
        {
            return mCurrent.down(button);
        }

        bool Mouse::held(Button button) const
        {
            return mCurrent.down(button) && mPrevious.down(button);
        }

        bool Mouse::pressed(Button button) const
        {
            return mCurrent.down(button) && mPrevious.up(button);
        }

        bool Mouse::released(Button button) const
        {
            return mCurrent.up(button) && mPrevious.down(button);
        }

        void Mouse::update()
        {
            mPrevious = mCurrent;
            mCurrent.update();
        }

        void Mouse::update(const Mouse::State& mouseState)
        {
            mPrevious = mCurrent;
            mCurrent = mouseState;
        }

        void Mouse::reset()
        {
            mPrevious.reset();
            mCurrent.reset();
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        float Mouse::State::x() const { return mX; }
        void Mouse::State::x(float x) { mX = x; }
        float Mouse::State::y() const { return mY; }
        void Mouse::State::y(float y) { mY = y; }
        float Mouse::State::scroll() const { return mScroll; }
        void Mouse::State::scroll(float scroll) { mScroll = scroll; }

        bool Mouse::State::down(Button button) const
        {
            return mButtons[static_cast<size_t>(button)];
        }

        void Mouse::State::down(Button button, bool down)
        {
            mButtons[static_cast<size_t>(button)] = down ? 1 : 0;
        }

        bool Mouse::State::up(Button button) const
        {
            return !down(button);
        }

        void Mouse::State::update()
        {
            #if defined(DYNAMIC_STATIC_WINDOWS)
            // TODO : PhysicalToLogicalPoint(HWND)...excellent!
            POINT point;
            if (GetPhysicalCursorPos(&point)) {
                mX = static_cast<float>(point.x);
                mY = static_cast<float>(point.y);
            } else {
                // TODO : React to error.
            }

            for (size_t i = 0; i < mButtons.size(); ++i) {
                mButtons[i] = GetAsyncKeyState(static_cast<int>(i)) ? 1 : 0;
            }
            #endif
        }

        void Mouse::State::reset()
        {
            update();
            // HACK : This might actually be the right thing to do for a reset.
            // mButtons.reset();
            // mX = 0;
            // mY = 0;
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        Mouse::Button from_glfw_mouse_button(int mouseButton)
        {
            auto button = Mouse::Button::Unknown;
            switch (mouseButton) {
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
