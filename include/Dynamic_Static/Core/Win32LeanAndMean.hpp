
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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
