
/*
==========================================
  Copyright (c) 2017-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
#include <malloc.h>
#else
#include <stdlib.h>
#endif // DYNAMIC_STATIC_PLATFORM_WINDOS

namespace dst {

/**
Allocates memory on a given alignment boundary
@param [in] size The size of the requested allocation
@param [in] The alignment value, which must be a multiple of sizeof(void*) and an integer power of 2
@return A pointer to the memory block that was allocated or nullptr if the operation failed
*/
inline void* aligned_malloc(size_t size, size_t alignment)
{
    void* ptr = nullptr;
    #ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
    ptr = _aligned_malloc(size, alignment);
    #else
    auto result = posix_memalign(&ptr, alignment, size);
    if (!result) {
        ptr = nullptr;
    }
    #endif // DYNAMIC_STATIC_PLATFORM_WINDOS
    return ptr;
}

/**
Frees a block of memory that was allocated with dst::aligned_malloc()
@param [in] ptr A pointer to the memory block to free
*/
inline void aligned_free(void* ptr)
{
    #ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
    _aligned_free(ptr);
    #else
    free(ptr);
    #endif // DYNAMIC_STATIC_PLATFORM_WINDOS
}

} // namespace dst
