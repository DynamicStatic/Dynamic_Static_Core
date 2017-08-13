
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Input/Keyboard.hpp"
#include "Dynamic_Static/Core/Input/Mouse.hpp"

namespace Dynamic_Static {

    /**
     * Provides methods for input device queries.
     */
    class Input final
    {
    public:
        class Manager;

    private:
        Mouse mMouse;
        Keyboard mKeyboard;

    private:
        Input() = default;

    public:
        /**
         * Gets this Input's Mouse.
         * @return This Input's Mouse
         */
        Mouse& mouse();

        /**
         * Gets this Input's Mouse.
         * @return This Input's Mouse
         */
        const Mouse& mouse() const;

        /**
         * Gets this Input's Keyboard.
         * @return This Input's Keyboard
         */
        Keyboard& keyboard();

        /**
         * Gets this Input's Keyboard.
         * @return This Input's Keyboard
         */
        const Keyboard& keyboard() const;

        /**
         * Resets this Input.
         */
        void reset();

    private:
        void update(
            const Mouse::State& mouseState,
            const Keyboard::State& keyboardState
        );
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    class Input::Manager final
    {
    private:
        Input mInput;
        Mouse::State mMouseState;
        Keyboard::State mKeyboardState;

    public:
        /**
         * Gets this Input::Manager's Input.
         * @return This Input::Manager's Input
         */
        const Input& input() const;

        /**
         * Gets this Input::Manager's Input.
         * @return This Input::Manager's Input
         */
        Input& input();

        /**
         * Gets this Input::Manager's Mouse::State.
         * @return This Input::Manager's Mouse::State
         */
        const Mouse::State& mouse_state() const;

        /**
         * Gets this Input::Manager's Mouse::State.
         * @return This Input::Manager's Mouse::State
         */
        Mouse::State& mouse_state();

        /**
         * Gets this Input::Manager's Keyboard::State.
         * @return This Input::Manager's Keyboard::State
         */
        const Keyboard::State& keyboard_state() const;

        /**
         * Gets this Input::Manager's Keyboard::State.
         * @return This Input::Manager's Keyboard::State
         */
        Keyboard::State& keyboard_state();

        /**
         * Updates this Input::Manager's Input.
         * \n NOTE : This method must be called periodically to keep this Input::Manager's Input up to date.
         */
        void update();

        /**
         * Resets this Input::Manager's Input.
         */
        void reset();
    };

} // namespace Dynamic_Static
