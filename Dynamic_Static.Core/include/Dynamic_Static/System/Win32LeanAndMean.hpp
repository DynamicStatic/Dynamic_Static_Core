
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

#include "Dynamic_Static/System/Defines.hpp"
#if defined(DYNAMIC_STATIC_WINDOWS)

#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/Validate.hpp"

#ifndef WIN_32_LEAN_AND_MEAN
#define WIN_32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#include <string>
#include <stdexcept>

namespace Dynamic_Static {
    namespace System {
        class Win32Exception final
            : public std::runtime_error {
        private:
            HRESULT mResult { E_FAIL };

        public:
            /**
             * Constructs an instance of Win32Exception with the calling thread's last Win32 error.
             */
            explicit Win32Exception();

            /**
             * Constructs an instance of Win32Exception with a specified HRESULT.
             * @param [in] result The HRESULT to construct this Win32Exception with
             */
            explicit Win32Exception(HRESULT result);

        public:
            /**
             * Gets this Win32Exception's HRESULT.
             * @return This Win32Exception's HRESULT
             */
            HRESULT result() const;
        };
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    /**
     * Gets the std::string representation of the last Windows error code for the calling thread.
     * @return The std::string representation of the last Windows error code for the calling thread
     */
    std::string win32_error_message();

    /**
     * Gets the std::string representation of a specified DWORD.
     * @param [in] The DWORD to get the std::string representation of
     * @return The std::string representation of the specified DWORD
     */
    template <>
    std::string to_string<DWORD>(const DWORD& message);

    /**
     * Gets the std::wstring representation of a specified DWORD.
     * @param [in] The DWORD to get the std::wstring representation of
     * @return The std::wstring representation of the specified DWORD
     */
    template <>
    std::wstring to_wstring<DWORD>(const DWORD& message);

    /**
     * Gets the std::string representation of a specified HRESULT.
     * @param [in] The HRESULT to get the std::string representation of
     * @return The std::string representation of the specified HRESULT
     */
    template <>
    std::string to_string<HRESULT>(const HRESULT& result);

    /**
     * Gets the std::wstring representation of a specified HRESULT.
     * @param [in] The HRESULT to get the std::wstring representation of
     * @return The std::wstring representation of the specified HRESULT
     */
    template <>
    std::wstring to_wstring<HRESULT>(const HRESULT& result);

    /**
     * TODO : Documentation.
     */
    template <>
    void validate<HRESULT>(const HRESULT& result);
} // namespace Dynamic_Static

#endif
