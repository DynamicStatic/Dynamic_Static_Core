
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

#include "Dynamic_Static/Core/Defines.hpp"
#if defined(DYNAMIC_STATIC_WINDOWS)

#include "Dynamic_Static/System/Window.hpp"
#include "Dynamic_Static/Core/NonConstructable.hpp"
#include "Dynamic_Static/Core/NotImplementedError.hpp"
#include "Dynamic_Static/System/Win32LeanAndMean.hpp"

#include <cassert>
#include <unordered_map>

namespace Dynamic_Static {
    namespace System {
        class Window::Platform final
            : NonConstructable {
        private:
            static std::unordered_map<HWND, Window*> sWindows;

        public:
            static void add(Window& window);
            static void remove(Window& window);
            static LRESULT CALLBACK wnd_proc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
        };

        std::unordered_map<HWND, Window*> Window::Platform::sWindows;
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        Window::Window()
            : Window(1280, 720)
        {
        }

        Window::Window(uint32_t width, uint32_t height)
            : mWidth { width }
            , mHeight { height }
        {
            name(dst::to_string(mClassName));

            mInstance = GetModuleHandle(nullptr);
            auto instance = static_cast<HINSTANCE>(mInstance);
            WNDCLASSEX windowClass { }; // TODO : WNDCLASS alt.
            windowClass.cbSize = sizeof(windowClass);
            windowClass.hInstance = instance;
            windowClass.style = CS_HREDRAW | CS_VREDRAW;
            windowClass.lpszClassName = mClassName.c_str();
            windowClass.lpfnWndProc = &Platform::wnd_proc;
            windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // TODO : LoadCursor() alt.
            windowClass.hIconSm = LoadIcon(instance, IDI_APPLICATION); // TODO : LoadIcon() alt.
            windowClass.hIcon = LoadIcon(instance, IDI_APPLICATION); // TODO : LoadIcon() alt.
            windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
            if (!RegisterClassEx(&windowClass)) { // TODO : RegisterClass() alt.
                throw Win32Exception();
            }

            RECT client { 0, 0, static_cast<long>(mWidth), static_cast<long>(mHeight) };
            mHandle = CreateWindowEx(
                NULL,
                mClassName.c_str(),
                mTitle.c_str(),
                // HACK : Removing anything that allows the Window to resize...
                // FUCK : Resizing the Window crashes the app...
                WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
                mX,
                mY,
                client.right - client.left,
                client.bottom - client.top,
                NULL,
                NULL,
                instance,
                NULL
            );

            if (!mHandle) {
                throw Win32Exception(/* TODO : what. */);
            }

            Platform::add(*this);
        }

        void* Window::handle() const { return mHandle; }
        void* Window::instance() const { return mInstance; }

        void Window::update()
        {
            MSG msg;
            UINT msgFilterMin = 0;
            UINT msgFilterMax = 0;
            if (PeekMessage(&msg, static_cast<HWND>(mHandle), msgFilterMin, msgFilterMax, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        void Window::open()
        {
            // TODO : Validate.
            BOOL result;
            auto handle = static_cast<HWND>(mHandle);
            result = ShowWindow(handle, SW_SHOW);
            result = SetForegroundWindow(handle);
            handle = SetFocus(handle);
        }

        void Window::close()
        {
            throw NotImplementedError("Window::close()");
        }

        void Window::hide()
        {
            throw NotImplementedError("Window::hide()");
        }

        void Window::minimize()
        {
            throw NotImplementedError("Window::minimize()");
        }

        void Window::maximize()
        {
            throw NotImplementedError("Window::maximize()");
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace System {
        void Window::Platform::add(Window& window)
        {
            sWindows.insert(
                std::unordered_map<HWND, Window*>::value_type(
                    static_cast<HWND>(window.handle()),
                    &window
                )
            );
        }

        void Window::Platform::remove(Window& window)
        {
            sWindows.erase(static_cast<HWND>(window.handle()));
        }

        LRESULT CALLBACK Window::Platform::wnd_proc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            auto itr = sWindows.find(handle);
            if (itr != sWindows.end()) {
                auto window = itr->second;
                assert(window && window->handle() == handle);
                switch (message) {
                    case WM_LBUTTONDOWN:
                    {
                    } break;

                    case WM_CLOSE:
                    {
                        window->OnClosed(*window);
                        DestroyWindow(handle);
                    } break;

                    case WM_PAINT:
                    {
                        // TODO : BOOL result = ValidateRect(handle, NULL);
                    } break;

                    case WM_SIZE:
                    {
                        window->mWidth = LOWORD(lParam);
                        window->mHeight = HIWORD(lParam);
                        window->OnResized(*window);
                    } break;

                    case WM_EXITSIZEMOVE:
                    {
                    } break;
                }
            }

            return DefWindowProc(handle, message, wParam, lParam);
        }
    } // namespace System
} // namespace Dynamic_Static

#endif
