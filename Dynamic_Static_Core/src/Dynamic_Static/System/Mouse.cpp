
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
        float Mouse::State::y() const { return mY; }

        bool Mouse::State::down(Button button) const
        {
            return mButtons[static_cast<size_t>(button)];
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
