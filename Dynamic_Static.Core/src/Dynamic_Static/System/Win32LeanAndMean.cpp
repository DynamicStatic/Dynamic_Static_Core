
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

#include "Dynamic_Static/System/Win32LeanAndMean.hpp"

namespace Dynamic_Static {
    namespace System {
        Win32Exception::Win32Exception()
            : Win32Exception(GetLastError())
        {
        }

        Win32Exception::Win32Exception(HRESULT result)
            : std::runtime_error("Win32 Error : " + dst::to_string(result))
            , mResult { result }
        {
        }

        HRESULT Win32Exception::result() const
        {
            return mResult;
        }
    } // namespace System
} // namespace Dynamic_Static

namespace Dynamic_Static {
    std::string win32_error_message()
    {
        return dst::to_string(GetLastError());
    }

    template <>
    std::string to_string<DWORD>(const DWORD& message)
    {
        // TODO : This function doesn't work for all cases...
        //        for instance, if GetLastError() spits out 998
        //        (ERROR_NOACCESS) this won't get the correct message.
        std::string str = std::to_string(message) + " Unkown";

        // TODO : Compile flags for UNICODE define.
        // NOTE : HRESULT to LPTSTR...
        // http://stackoverflow.com/a/455533/3453616
        LPTSTR messageBuffer = nullptr;
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            nullptr,
            message,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            messageBuffer,
            0,
            nullptr
        );

        if (messageBuffer) {
            // TODO : Cross platform std::wstring to std::string utility.
            // NOTE : std::wstring to std::string (Windows specific)...
            // http://stackoverflow.com/a/3999597/3453616
            std::wstring wstr(messageBuffer);
            size_t length = WideCharToMultiByte(
                CP_UTF8,
                0,
                &wstr[0],
                static_cast<int>(wstr.size()),
                nullptr,
                0,
                nullptr,
                nullptr
            );

            str = std::string(length, '\0');
            WideCharToMultiByte(
                CP_UTF8,
                0,
                &wstr[0],
                static_cast<int>(wstr.size()),
                &str[0],
                static_cast<int>(str.size()),
                nullptr,
                nullptr
            );

            LocalFree(messageBuffer);
        }

        return str;
    }

    template <>
    std::wstring to_wstring<DWORD>(const DWORD& message)
    {
        return to_wstring(to_string(message));
    }

    template <>
    std::string to_string<HRESULT>(const HRESULT& result)
    {
        return to_string<DWORD>(HRESULT_CODE(result));
    }

    template <>
    std::wstring to_wstring<HRESULT>(const HRESULT& result)
    {
        return to_wstring(to_string(result));
    }

    template <>
    void validate<HRESULT>(const HRESULT& result)
    {
        if (FAILED(result)) {
            throw System::Win32Exception(result);
        }
    }
} // namespace Dynamic_Static

#endif
