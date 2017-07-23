
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

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

#include <cassert>
#include <cstddef>
#include <cstring>
#include <cstdint>
#include <cstdlib>

#if defined(__X86_64__) || defined(_WIN64)
    #ifndef DYNAMIC_STATIC_64_BIT
    #define DYNAMIC_STATIC_64_BIT (1)
    #endif
#else
    #ifndef DYNAMIC_STATIC_32_BIT
    #define DYNAMIC_STATIC_32_BIT (1)
    #endif
#endif

#if defined(__linux__)
    #ifndef DYNAMIC_STATIC_LINUX
    #define DYNAMIC_STATIC_LINUX (1)
    #endif
#elif defined(_WIN32) || defined(_WIN64)
    #ifndef DYNAMIC_STATIC_WINDOWS
    #define DYNAMIC_STATIC_WINDOWS (1)
    #endif
#endif

#if defined(__clang__)
    #ifndef DYNAMIC_STATIC_CLANG
    #define DYNAMIC_STATIC_CLANG (1)
    #endif
#elif defined(__GNUG__)
    #ifndef DYNAMIC_STATIC_GCC
    #define DYNAMIC_STATIC_GCC (1)
    #endif
#elif defined(_MSC_BUILD )
    #ifndef DYNAMIC_STATIC_MSVC
    #define DYNAMIC_STATIC_MSVC (1)
    #endif
#endif

#define DYNAMIC_STATIC_CORE_VERSION_MAJOR (1)
#define DYNAMIC_STATIC_CORE_VERSION_MINOR (0)
#define DYNAMIC_STATIC_CORE_VERSION_PATCH (0)

namespace Dynamic_Static {

    static constexpr uint32_t VersionMajor { DYNAMIC_STATIC_CORE_VERSION_MAJOR };
    static constexpr uint32_t VersionMinor { DYNAMIC_STATIC_CORE_VERSION_MINOR };
    static constexpr uint32_t VersionPatch { DYNAMIC_STATIC_CORE_VERSION_PATCH };

    /**
     * Treats a given literal as a size_t.
     * @param [in] value The literal to treat as a size_t
     * @return The given value as a size_t literal
     */
    inline constexpr size_t operator "" _zu(unsigned long long int value)
    {
        return static_cast<size_t>(value);
    }

} // namespace Dynamic_Static

namespace dst = Dynamic_Static;
