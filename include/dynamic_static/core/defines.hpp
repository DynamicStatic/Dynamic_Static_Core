
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include <cstddef>
#include <cstdint>

#if defined(__X86_64__) || defined(_WIN64)
#ifndef DYNAMIC_STATIC_ARCHITECTURE_64_BIT
#define DYNAMIC_STATIC_ARCHITECTURE_64_BIT
#endif
#else
#ifndef DYNAMIC_STATIC_ARCHITECTURE_32_BIT
#define DYNAMIC_STATIC_ARCHITECTURE_32_BIT
#endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifndef DYNAMIC_STATIC_PLATFORM_WINDOWS
#define DYNAMIC_STATIC_PLATFORM_WINDOWS
#endif
#elif defined(__linux__)
#ifndef DYNAMIC_STATIC_PLATFORM_LINUX
#define DYNAMIC_STATIC_PLATFORM_LINUX
#endif
#endif

#if defined(__clang__)
#ifndef DYNAMIC_STATIC_COMPILER_CLANG
#define DYNAMIC_STATIC_COMPILER_CLANG
#endif
#elif defined(__GNUG__)
#ifndef DYNAMIC_STATIC_COMPILER_GCC
#define DYNAMIC_STATIC_COMPILER_GCC
#endif
#elif defined(_MSC_BUILD)
#ifndef DYNAMIC_STATIC_COMPILER_MSVC
#define DYNAMIC_STATIC_COMPILER_MSVC
#endif
#endif

#define DYNAMIC_STATIC_CORE_VERSION_MAJOR 2
#define DYNAMIC_STATIC_CORE_VERSION_MINOR 0
#define DYNAMIC_STATIC_CORE_VERSION_PATCH 0

#define dst_stringify(STR) #STR
#define dst_expand(STR) dst_stringify(STR)
#define dst_file_line (__FILE__ " @ line " dst_expand(__LINE__))

namespace dst {

static constexpr int VersionMajor { DYNAMIC_STATIC_CORE_VERSION_MAJOR };
static constexpr int VersionMinor { DYNAMIC_STATIC_CORE_VERSION_MINOR };
static constexpr int VersionPatch { DYNAMIC_STATIC_CORE_VERSION_PATCH };

} // namespace dst
