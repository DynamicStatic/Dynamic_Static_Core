
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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)

#include "Dynamic_Static/Core/ToString.hpp"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN (1)
#endif
#ifndef NOMINMAX
#define NOMINMAX (1)
#endif
#include <Windows.h>

#include <stdexcept>
#include <string>

namespace Dynamic_Static {

    /**
     * Exception thrown for Win32 errors.
     */
    class Win32Exception final
        : public std::runtime_error
    {
    private:
        HRESULT mResult { E_FAIL };

    public:
        /**
         * Constructs an instance of Win32Exception with the calling thread's last Win32 error.
         */
        Win32Exception();

        /**
         * Constructs an instance of Win32Exception with a given HRESULT.
         * @param [in] result This Win32Exception's HRESULT
         */
        explicit Win32Exception(HRESULT hresult);

    public:
        /**
         * Gets this Win32Exception's HRESULT.
         * @return This Win32Exception's HRESULT
         */
        HRESULT result() const;
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /**
     * Gets the std::string representation of a given DWORD.
     * @param [in] The DWORD to get the std::string representation of
     * @return The std::string representation of the given DWORD
     */
    std::string DWORD_to_string(DWORD dword);

    /**
     * Gets the std::string representation of a given HRESULT.
     * @param [in] The HRESULT to get the std::string representation of
     * @return The std::string representation of the given HRESULT
     */
    std::string HRESULT_to_string(HRESULT hresult);

} // namespace Dynamic_Static

#endif
