
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <experimental/filesystem>

// NOTE : This file can be removed once std::filesystem is fully supported.

namespace Dynamic_Static {

    namespace filesystem = std::experimental::filesystem;

} // namespace Dynamic_Static
