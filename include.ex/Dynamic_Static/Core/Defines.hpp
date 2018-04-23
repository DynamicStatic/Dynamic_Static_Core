
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdarg>
#include <cstring>

#if defined(__X86_64__) || defined(_WIN64)
    #ifndef DYNAMIC_STATIC_64_BIT
    #define DYNAMIC_STATIC_64_BIT 1
    #endif
#else
    #ifndef DYNAMIC_STATIC_32_BIT
    #define DYNAMIC_STATIC_32_BIT 1
    #endif
#endif

#if defined(_WIN32) || defined(_WIN64)
    #ifndef DYNAMIC_STATIC_WINDOWS
    #define DYNAMIC_STATIC_WINDOWS 1
    #endif
#elif defined(__linux__)
    #ifndef DYNAMIC_STATIC_LINUX
    #define DYNAMIC_STATIC_LINUX 1
    #endif
#endif

#if defined(__clang__)
    #ifndef DYNAMIC_STATIC_CLANG
    #define DYNAMIC_STATIC_CLANG 1
    #endif
#elif defined(__GNUG__)
    #ifndef DYNAMIC_STATIC_GCC
    #define DYNAMIC_STATIC_GCC 1
    #endif
#elif defined(_MSC_BUILD )
    #ifndef DYNAMIC_STATIC_MSVC
    #define DYNAMIC_STATIC_MSVC 1
    #endif
#endif

#define DYNAMIC_STATIC_CORE_VERSION_MAJOR 1
#define DYNAMIC_STATIC_CORE_VERSION_MINOR 0
#define DYNAMIC_STATIC_CORE_VERSION_PATCH 0

/**
 * TODO : Documentation.
 */
#define dst_stringify(STR) #STR

/**
 * TODO : Documentation.
 */
#define dst_expand(STR) dst_stringify(STR)

/**
 * TODO : Documentation.
 */
#define dst_file_line (__FILE__ " @ " dst_expand(__LINE__))

namespace Dynamic_Static {

    static constexpr int VersionMajor { DYNAMIC_STATIC_CORE_VERSION_MAJOR }; /*!< TODO : Documentation. */
    static constexpr int VersionMinor { DYNAMIC_STATIC_CORE_VERSION_MINOR }; /*!< TODO : Documentation. */
    static constexpr int VersionPatch { DYNAMIC_STATIC_CORE_VERSION_PATCH }; /*!< TODO : Documentation. */

} // namespace Dynamic_Static
namespace dst = Dynamic_Static;
