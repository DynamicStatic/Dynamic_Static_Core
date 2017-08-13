
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Input.hpp"

namespace Dynamic_Static {

    Mouse& Input::mouse()
    {
        return mMouse;
    }

    const Mouse& Input::mouse() const
    {
        return mMouse;
    }

    Keyboard& Input::keyboard()
    {
        return mKeyboard;
    }

    const Keyboard& Input::keyboard() const
    {
        return mKeyboard;
    }

    void Input::reset()
    {
        mMouse.reset();
        mKeyboard.reset();
    }

    void Input::update(
        const Mouse::State& mouseState,
        const Keyboard::State& keyboardState
    )
    {
        mMouse.update(mouseState);
        mKeyboard.update(keyboardState);
    }

} // namespace Dynamic_Static
