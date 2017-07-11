
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#include "Dynamic_Static/Core/Input/Input.Manager.hpp"

namespace Dynamic_Static
{
    const Input& Input::Manager::input() const
    {
        return mInput;
    }

    Input& Input::Manager::input()
    {
        return mInput;
    }

    const Mouse::State& Input::Manager::mouse_state() const
    {
        return mMouseState;
    }

    Mouse::State& Input::Manager::mouse_state()
    {
        return mMouseState;
    }

    const Keyboard::State& Input::Manager::keyboard_state() const
    {
        return mKeyboardState;
    }

    Keyboard::State& Input::Manager::keyboard_state()
    {
        return mKeyboardState;
    }

    void Input::Manager::update()
    {
        mInput.update(mMouseState, mKeyboardState);
    }

    void Input::Manager::reset()
    {
        mInput.reset();
        mMouseState.reset();
        mKeyboardState.reset();
    }
} // namespace Dynamic_Static
