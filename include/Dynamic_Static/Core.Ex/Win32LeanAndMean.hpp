
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core.Ex/Defines.hpp"

#if defined(DYNAMIC_STATIC_WINDOWS)
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN 1
    #endif
    #ifndef NOMINMAX
    #define NOMINMAX 1
    #endif
    #include <Windows.h>
#endif
