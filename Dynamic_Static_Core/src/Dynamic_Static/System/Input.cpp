
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

#include "Dynamic_Static/System/Input.hpp"

namespace Dynamic_Static {
    namespace System {
        const Mouse& Input::mouse() const { return mMouse; }
        Mouse& Input::mouse() { return mMouse; }
        const Keyboard& Input::keyboard() const { return mKeyboard; }
        Keyboard& Input::keyboard() { return mKeyboard; }

        void Input::update()
        {
            mMouse.update();
            mKeyboard.update();
        }

        void Input::update(const Keyboard::State& keyboardState)
        {
            mKeyboard.update(keyboardState);
        }

        void Input::reset()
        {
            mMouse.reset();
            mKeyboard.reset();
        }
    } // namespace System
} // namespace Dynamic_Static
