
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
#include <filesystem>
#endif

namespace dst {

#ifdef DYNAMIC_STATIC_PLATFORM_WINDOWS
namespace filesystem = std::filesystem;
#endif

} // namespace dst
