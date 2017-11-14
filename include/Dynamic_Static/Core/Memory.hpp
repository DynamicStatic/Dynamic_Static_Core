
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <memory>

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    void* aligned_alloc(size_t size, size_t alignment);

    /**
     * TODO : Documentation.
     */
    void aligned_free(void* data);

} // namespace Dynamic_Static
