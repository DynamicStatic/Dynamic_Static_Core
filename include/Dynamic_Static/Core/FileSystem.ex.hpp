#if 0
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

#include <experimental/filesystem>

// NOTE : dst::filesystem should be remove once std::filesystem is fully supported.

namespace dst {

    namespace filesystem = std::experimental::filesystem;

} // namespace dst
#endif