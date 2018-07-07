
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)
#include "Dynamic_Static/Core/Win32LeanAndMean.hpp"
#endif

#include <malloc.h>

namespace Dynamic_Static {

    /*
    * Allocates memory on a specified alignment boundary.
    * @param [in] size The size of the requested allocation
    * @param [in] The alignment value, which must be a multiple of sizeof(void*) and an integer power of 2
    * @return A pointer to the memory block that was allocated or nullptr if the operation failed
    */
    void* aligned_malloc(size_t size, size_t alignment)
    {
        // FROM : https://github.com/SaschaWillems/Vulkan/tree/master/dynamicuniformbuffer
        void* ptr = nullptr;
        #if defined(DYNAMIC_STATIC_WINDOWS)
        ptr = _aligned_malloc(size, alignment);
        #else
        int result = posix_memalign(&ptr, alignment, size);
        if (!result) {
            ptr = nullptr;
        }
        #endif
        return ptr;
    }

    /*
    * Frees a block of memory that was allocated with dst::aligned_malloc().
    * @param [in] ptr A pointer to the memory block to free
    */
    void aligned_free(void* ptr)
    {
        // FROM : https://github.com/SaschaWillems/Vulkan/tree/master/dynamicuniformbuffer
        #if defined(DYNAMIC_STATIC_WINDOWS)
        _aligned_free(ptr);
        #else
        free(ptr);
        #endif
    }

} // namespace Dynamic_Static
