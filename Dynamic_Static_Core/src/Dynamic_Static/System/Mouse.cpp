
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
        Mouse::Mouse(Mouse&& other)
        {
            *this = std::move(other);
        }

        Mouse& Mouse::operator=(Mouse&& other)
        {
            if (this != &other) {
                mCurrent = std::move(other.mCurrent);
                mPrevious = std::move(other.mPrevious);
                mDelta = std::move(other.mDelta);
            }

            return *this;
        }
        const math::Vector2& Mouse::position() const
        {
            return mCurrent.position();
        }

        const math::Vector2& Mouse::delta() const
        {
            return mDelta;
        }

        float Mouse::scroll() const
        {
            return mCurrent.scroll() - mPrevious.scroll();
        }

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

        void Mouse::reset()
        {
            mPrevious.reset();
            mCurrent.reset();
        }

        void Mouse::update(const Mouse::State& mouseState)
        {
            mPrevious = mCurrent;
            mCurrent = mouseState;
            mDelta = mCurrent.position() - mPrevious.position();
        }
    } // namespace System
} // namespace Dynamic_Static
