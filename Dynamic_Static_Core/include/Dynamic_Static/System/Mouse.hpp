
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

#include <bitset>

namespace Dynamic_Static {
    namespace System {
        /**
         * TODO : Documentation.
         */
        class Mouse final
            : NonCopyable
            , NonMoveable {
        public:
            // #if defined(DYNAMIC_STATIC_WINDOWS)
            /**
             * Specifies buttons on a mouse.
             */
            enum class Button {
                // TODO : Wrap these values for cross compile.
                // The following table shows the symbolic constant names, hexadecimal values,
                // and mouse or keyboard equivalents for the virtual-key codes used by Windows.
                // The codes are listed in numeric order.
                // http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

                Left         = 0x01,
                Right        = 0x02,

                // ControlBreak = 0x03,

                Middle       = 0x04,
                X1           = 0x05,
                X2           = 0x06,
                Count        = X2,
            };
            // #endif

        private:
            class State final {
            private:
                float mX { 0 };
                float mY { 0 };
                std::bitset<static_cast<size_t>(Button::Count)> mButtons;

            public:
                float x() const;
                float y() const;
                bool down(Button button) const;
                bool up(Button button) const;
                void update();
                void reset();
            };

        private:
            State mCurrent;
            State mPrevious;

        public:
            /**
             * TODO : Documentation.
             */
            float x() const;

            /**
             * TODO : Documentation.
             */
            float y() const;

            /**
             * TODO : Documentation.
             */
            float delta_x() const;

            /**
             * TODO : Documentation.
             */
            float delta_y() const;

            /**
             * TODO : Documentation.
             */
            bool up(Button button) const;

            /**
             * TODO : Documentation.
             */
            bool down(Button button) const;

            /**
             * TODO : Documentation.
             */
            bool held(Button button) const;

            /**
             * TODO : Documentation.
             */
            bool pressed(Button button) const;

            /**
             * TODO : Documentation.
             */
            bool released(Button button) const;

            /**
             * TODO : Documentation.
             */
            void update();

            /**
             * TODO : Documentation.
             */
            void reset();
        };
    } // namespace System
} // namespace Dynamic_Static
