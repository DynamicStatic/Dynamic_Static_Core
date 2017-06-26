
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#include "Dynamic_Static/Core/Win32LeanAndMean.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)

namespace Dynamic_Static
{
    Win32Exception::Win32Exception()
        : Win32Exception(GetLastError())
    {
    }

    Win32Exception::Win32Exception(HRESULT hresult)
        : std::runtime_error("Win32 Error : " + HRESULT_to_string(hresult))
        , mResult { hresult }
    {
    }

    HRESULT Win32Exception::result() const
    {
        return mResult;
    }
} // namespace Dynamic_Static

namespace Dynamic_Static
{
    std::string DWORD_to_string(DWORD dword)
    {
        // TODO : This function doesn't work for all cases...
        //        for instance, if GetLastError() spits our 998
        //        (ERROR_NOACCESS) this won't get the correct message.
        std::string str = std::to_string(dword) + " Unknown";

        // TODO : Compile flags for UNICODE define.
        // NOTE : HRESULT to LPTSTR...
        // http://stackoverflow.com/a/455533/3453616
        LPTSTR message = nullptr;
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            nullptr,
            dword,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            message,
            0,
            nullptr
        );

        if (message) {
            // TODO : Cross platform std::wstring to std::string utility.
            // NOTE : std::wstring to std::string (Windows specific)...
            // http://stackoverflow.com/a/3999597/3453616
            std::wstring wstr(message);
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

            LocalFree(message);
        }

        return str;
    }

    std::string HRESULT_to_string(HRESULT hresult)
    {
        return dst::to_string(static_cast<DWORD>(HRESULT_CODE(hresult)));
    }
} // namespace Dynamic_Static

#endif
