
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

#include "Dynamic_Static/Core/Object.hpp"
#include "Dynamic_Static/Core/Events.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include <string>

namespace Dynamic_Static {
    namespace System {
        class Window final
            : public Object {
        private:
            class Platform;

        private:
            uint32_t mX { 320 };
            uint32_t mY { 180 };
            uint32_t mWidth { 1280 };
            uint32_t mHeight { 720 };
            void* mHandle { nullptr };
            #if defined(DYNAMIC_STATIC_WINDOWS)
            void* mInstance { nullptr };
            std::wstring mTitle { L"Dynamic_Static" };
            std::wstring mClassName { L"Dynamic_Static::System::Window" };
            #endif

        public:
            /**
             * Event fired when this Window is resized.
             * @param [in] The Window being resized
             */
            Event<Window, const Window&> OnResized;

            /**
             * Event fired when this Window is closed.
             * @param [in] The Window being closed
             */
            Event<Window, const Window&> OnClosed;

        public:
            /**
             * Constructs an instance of Window.
             */
            Window();

            /**
             * Constructs an instance of Window.
             * @param [in] width  This Window's initial width
             * @param [in] height This Window's initial height
             */
            Window(uint32_t width, uint32_t height);

        public:
            /**
             * Gets this Window's handle.
             * @return This Window's handle
             */
            void* handle() const;

            #if defined(DYNAMIC_STATIC_WINDOWS)
            /**
             * Gets this Window's instance.
             * @return This Window's instance
             */
            void* instance() const;
            #endif

            /**
             * Gets this Window's width.
             * @return This Window's width
             */
            uint32_t width() const;

            /**
             * Gets this Window's height.
             * @return This Window's height
             */
            uint32_t height() const;

            /**
            * Updates this Window.
            * \n NOTE : This method needs to be called at regular intervals to keep this Window's contents up to date
            */
            void update();

            /**
             * Opens this Window.
             */
            void open();

            /**
             * Closes this Window.
             */
            void close();

            /**
             * Hides this Window.
             */
            void hide();

            /**
             * Minimizes this Window.
             */
            void minimize();

            /**
             * Maximizes this Window.
             */
            void maximize();
        };
    } // namespace System
} // namespace Dynamic_Static
