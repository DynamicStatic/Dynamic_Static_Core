
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#ifdef DYNAMIC_STATIC_WINDOWS
#include "Dynamic_Static/Core/Win32LeanAndMean.hpp"
#include <malloc.h>
#else
#include <stdlib.h>
#endif

namespace dst {

    /*!
    Allocates memory on a given alignment boundary.
    @param [in] size The size of the requested allocation
    @param [in] The alignment value, which must be a multiple of sizeof(void*) and an integer power of 2
    @return A pointer to the memory block that was allocated or nullptr if the operation failed
    */
    inline void* aligned_malloc(size_t size, size_t alignment)
    {
        void* ptr = nullptr;
        #ifdef DYNAMIC_STATIC_WINDOWS
        ptr = _aligned_malloc(size, alignment);
        #else
        int result = posix_memalign(&ptr, alignment, size);
        if (!result) {
            ptr = nullptr;
        }
        #endif
        return ptr;
    }

    /*!
    Frees a block of memory that was allocated with dst::aligned_malloc().
    @param [in] ptr A pointer to the memory block to free
    */
    inline void aligned_free(void* ptr)
    {
        #ifdef DYNAMIC_STATIC_WINDOWS
        _aligned_free(ptr);
        #else
        free(ptr);
        #endif
    }

} // namespace dst
