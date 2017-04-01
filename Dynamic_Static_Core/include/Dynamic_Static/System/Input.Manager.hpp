
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

#pragma once

#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/NonMoveable.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/System/Mouse.hpp"
#include "Dynamic_Static/System/Keyboard.hpp"

namespace Dynamic_Static {
    namespace System {
        class Input::Manager final
            : NonCopyable {
        private:
            Input mInput;
            Mouse::State mMouseState;
            Keyboard::State mKeyboardState;

        public:
            /**
             * Constructs an instance of Input::Manager.
             */
            Manager() = default;

            /**
             * Moves an instance of Input::Manager.
             * @param [in] other The Input::Manager to move from
             */
            Manager(Manager&& other);

            /**
             * Moves an instance of Input::Manager.
             * @param [in] other The Input::Manager to move from
             */
            Manager& operator=(Manager&& other);

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
    } // namespace System
} // namespace Dynamic_Static
