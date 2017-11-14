
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Memory.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)
#include "Dynamic_Static/Core/Win32LeanAndMean.hpp"
#endif

namespace Dynamic_Static {

    void* aligned_alloc(size_t size, size_t alignment)
    {
        // FROM : https://github.com/SaschaWillems/Vulkan/tree/master/dynamicuniformbuffer
        void* data = nullptr;
        #if defined(DYNAMIC_STATIC_WINDOWS)
        data = _aligned_malloc(size, alignment);
        #else
        int result = posix_memalign(&data, alignment, size);
        if (!result) {
            data = nullptr;
        }
        #endif

        return data;
    }

    void aligned_free(void* data)
    {
        // FROM : https://github.com/SaschaWillems/Vulkan/tree/master/dynamicuniformbuffer
        #if defined(DYNAMIC_STATIC_WINDOWS)
        _aligned_free(data);
        #else
        free(data);
        #endif
    }

} // namespace Dynamic_Static
