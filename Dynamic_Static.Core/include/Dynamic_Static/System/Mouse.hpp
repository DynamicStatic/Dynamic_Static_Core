
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
#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include <bitset>

namespace Dynamic_Static {
    namespace System {
        /**
         * Provides high level control over a system mouse.
         */
        class Mouse final
            : NonCopyable {
            friend class Input;
        public:
            /**
             * Specifies buttons on a mouse.
             */
            enum class Button {
                // NOTE : The following table shows the symbolic constant names, hexadecimal values,
                //        and mouse or keyboard equivalents for the virtual-key codes used by Windows.
                //        The codes are listed in numeric order.
                // http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

                Left         = 0x01,
                Right        = 0x02,

                // ControlBreak = 0x03,

                Middle       = 0x04,
                X1           = 0x05,
                X2           = 0x06,
                Count        = X2,
                Unknown      = Count,
            };

        public:
            /**
             * Represents a Mouse's state.
             */
            class State final {
            private:
                float mScroll { 0 };
                math::Vector2 mPosition;
                std::bitset<static_cast<size_t>(Button::Count)> mButtons;

            public:
                /**
                 * Gets this Mouse::State's scroll value.
                 * @return This Mouse::State's scroll value
                 */
                float scroll() const;

                /**
                 * Sets this Mouse::State's scroll value.
                 * @param [in] scroll This Mouse::State's scroll value
                 */
                void scroll(float scroll);

                /**
                 * Gets this Mouse::State's position.
                 * @return This Mouse::State's position
                 */
                const math::Vector2& position() const;

                /**
                 * Sets this Mouse::State's position.
                 * @param [in] position This Mouse::State's position
                 */
                void position(const math::Vector2& position);

                /**
                 * Gets a value indicating whether or not a specified Mouse::Button is down in this Mouse::State.
                 * @param [in] button The Mouse::Button to check
                 * @return Whether or not the specified Mouse::Button is down in this Mouse::State.
                 */
                bool down(Button button) const;

                /**
                 * Sets a value indicating whether or not a specified Mouse::Button is down in this Mouse::State.
                 * @param [in] button The Mouse::Button to set
                 * @param [in] down Whether or not the specified Mouse::Button is down in this Mouse::State.
                 */
                void down(Button button, bool down);

                /**
                 * Gets a value indicating whether or not a specified Mouse::Button is up in this Mouse::State.
                 * @param [in] button The Mouse::Button to check
                 * @return Whether or not the specified Mouse::Button is up in this Mouse::State.
                 */
                bool up(Button button) const;

                /**
                 * Resets this Mouse::State.
                 */
                void reset();
            };

        private:
            State mCurrent;
            State mPrevious;
            math::Vector2 mDelta;

        public:
            /**
             * Constructs an instance of Mouse.
             */
            Mouse() = default;

            /**
             * Moves an instance of Mouse.
             * @param [in] other The Mouse to move from
             */
            Mouse(Mouse&& other);

            /**
             * Moves an instance of Mouse.
             * @param [in] other The Mouse to move from
             */
            Mouse& operator=(Mouse&& other);

        public:
            /**
             * Gets this Mouse's current position.
             * @return This Mouse's current position
             */
            const math::Vector2& position() const;

            /**
             * Gets the delta between this Mouse's current and previous position.
             * @return The delta between this Mouse's current and previous position
             */
            const math::Vector2& delta() const;

            /**
             * Gets the delta between this Mouse's current and previous scroll.
             * @return The delta between this Mouse's current and previous scroll
             */
            float scroll() const;

            /**
             * Gets a value indicating whether or not a specified Mouse::Button is up.
             * @param [in] button The Mouse::Button to check
             * @return Whether or not thea specified Mouse::Button is up
             */
            bool up(Button button) const;

            /**
             * Gets a value indicating whether or not a specified Mouse::Button is down.
             * @param [in] button The Mouse::Button to check
             * @return Whether or not the specified Mouse::Button is down
             */
            bool down(Button button) const;

            /**
             * Gets a value indicating whether or not a specified Mouse::Button has been held.
             * @param [in] button The Mouse::Button to check
             * @return Whether or not the specified Mouse::Button has been held
             */
            bool held(Button button) const;

            /**
             * Gets a value indicating whether or not a specified Mouse::Button has been pressed.
             * @param [in] button The Mouse::Button to check
             * @return Whether or not the specified Mouse::Button has been pressed
             */
            bool pressed(Button button) const;

            /**
             * Gets a value indicating whether or not a specified Mouse::Button has been released.
             * @param [in] button The Mouse::Button to check
             * @return Whether or not the specified Mouse::Button has been released
             */
            bool released(Button button) const;

            /**
             * Resets this Mouse.
             */
            void reset();

        private:
            void update(const Mouse::State& mouseState);
        };
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        /**
         * Converts a GLFW mouse button to a Mouse::Button.
         * @param [in] glfwMouseButton The GLFW mouse button to convert to a Mouse::Button
         * @return The converted Mouse::Button
         */
        Mouse::Button glfw_to_dst_mouse_button(int glfwMouseButton);
    } // namespace System
} // namespace Dynamic_Static
