
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/FileSystem/StdFileSystemInclude.hpp"

#include <string>

namespace Dynamic_Static {
namespace Directory {

    /**
     * Gets the current working directory.
     * @return The current working directory
     */
    std::string current();

    /**
     * Gets the executable directory.
     * @return The executable directory
     */
    std::string executable();

} // namespace Directory
} // namespace Dynamic_Static
