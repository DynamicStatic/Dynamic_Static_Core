
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/FileSystem/Directory.hpp"
#include "Dynamic_Static/Core/NotImplementedError.hpp"
#include "Dynamic_Static/Core/FileSystem/Path.hpp"
#include "Dynamic_Static/Core/FileSystem/StdFileSystemInclude.hpp"

namespace Dynamic_Static {
namespace Directory {

    std::string current()
    {
        return  dst::Path::scrub(dst::filesystem::current_path().string());
    }

    std::string executable()
    {
        throw dst::NotImplementedError("dst::Directory::executable()");
    }

} // namespace Directory
} // namespace Dynamic_Static
