
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Input.hpp"

namespace Dynamic_Static {

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
