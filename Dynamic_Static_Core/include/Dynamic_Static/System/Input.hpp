
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
#include "Dynamic_Static/System/Mouse.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Keyboard.hpp"

namespace Dynamic_Static {
    namespace System {
        /**
         * Provides high level control over input devices.
         */
        class Input final
            : NonCopyable
            , NonMoveable {
        private:
            Mouse mMouse;
            Keyboard mKeyboard;

        public:

        public:
            /**
             * Gets this Input's Mouse.
             */
            const Mouse& mouse() const;

            /**
             * Gets this Input's Mouse.
             */
            Mouse& mouse();

            /**
             * Gets this Input's Keyboard.
             */
            const Keyboard& keyboard() const;

            /**
             * Gets this Input's Keyboard.
             */
            Keyboard& keyboard();

            /**
             * Updates this Input.
             * \n NOTE : This method must be called periodically to keep this Input up to date.
             */
            void update();

            /**
             * Updates this Input.
             * \n NOTE : This method must be called periodically to keep this Input up to date.
             */
            void update(const Keyboard::State& keyboardState, const Mouse::State& mouseState);

            /**
             * Resets this Input.
             */
            void reset();
        };
    } // namespace System
} // namespace Dynamic_Static
