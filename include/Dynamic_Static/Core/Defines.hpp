
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
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
    #define DYNAMIC_STATIC_64_BIT
    #endif
#else
    #ifndef DYNAMIC_STATIC_32_BIT
    #define DYNAMIC_STATIC_32_BIT
    #endif
#endif

#if defined(_WIN32) || defined(_WIN64)
    #ifndef DYNAMIC_STATIC_WINDOWS
    #define DYNAMIC_STATIC_WINDOWS
    #endif
#elif defined(__linux__)
    #ifndef DYNAMIC_STATIC_LINUX
    #define DYNAMIC_STATIC_LINUX
    #endif
#endif

#if defined(__clang__)
    #ifndef DYNAMIC_STATIC_CLANG
    #define DYNAMIC_STATIC_CLANG
    #endif
#elif defined(__GNUG__)
    #ifndef DYNAMIC_STATIC_GCC
    #define DYNAMIC_STATIC_GCC
    #endif
#elif defined(_MSC_BUILD)
    #ifndef DYNAMIC_STATIC_MSVC
    #define DYNAMIC_STATIC_MSVC
    #endif
#endif

#define DYNAMIC_STATIC_EXCEPTIONS_ENABLED

#define DYNAMIC_STATIC_CORE_VERSION_MAJOR 1
#define DYNAMIC_STATIC_CORE_VERSION_MINOR 0
#define DYNAMIC_STATIC_CORE_VERSION_PATCH 0

#define dst_stringify(STR) #STR
#define dst_expand(STR) dst_stringify(STR)
#define dst_file_line (__FILE__ " @ line " dst_expand(__LINE__))

namespace Dynamic_Static {

    static constexpr int VersionMajor { DYNAMIC_STATIC_CORE_VERSION_MAJOR }; /*!< Dynamic_Static.Core major version */
    static constexpr int VersionMinor { DYNAMIC_STATIC_CORE_VERSION_MINOR }; /*!< Dynamic_Static.Core minor version */
    static constexpr int VersionPatch { DYNAMIC_STATIC_CORE_VERSION_PATCH }; /*!< Dynamic_Static.Core patch version */

} // namespace Dynamic_Static
namespace dst = Dynamic_Static;
