
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

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

#define DYNAMIC_STATIC_CORE_VERSION_MAJOR (0)
#define DYNAMIC_STATIC_CORE_VERSION_MINOR (1)
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
