
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

#include "Dynamic_Static/System/Keyboard.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)
#include "Dynamic_Static/System/Win32LeanAndMean.hpp"
#endif

namespace Dynamic_Static {
    namespace System {
        bool Keyboard::held(Key key) const
        {
            return mCurrent.down(key) && mPrevious.down(key);
        }

        bool Keyboard::pressed(Key key) const
        {
            return mCurrent.down(key) && mPrevious.up(key);
        }

        bool Keyboard::released(Key key) const
        {
            return mCurrent.up(key) && mPrevious.down(key);
        }

        void Keyboard::update()
        {
            mPrevious = mCurrent;
            mCurrent.update();
        }

        void Keyboard::reset()
        {
            mPrevious.reset();
            mCurrent.reset();
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        bool Keyboard::State::down(Key key) const
        {
            return mKeys[static_cast<size_t>(key)];
        }

        bool Keyboard::State::up(Key key) const
        {
            return !down(key);
        }

        void Keyboard::State::update()
        {
            #if defined(DYNAMIC_STATIC_WINDOWS)
            for (size_t i = 0; i < mKeys.size(); ++i) {
                mKeys[i] = GetAsyncKeyState(static_cast<int>(i)) ? 1 : 0;
            }
            #endif
        }

        void Keyboard::State::reset()
        {
            mKeys.reset();
        }
    } // namespace System
} // namespace Dynamic_Static
