
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Version.hpp"

#include <iostream>

int main()
{
    dst::Version version(
        dst::VersionMajor,
        dst::VersionMinor,
        dst::VersionPatch
    );

    std::cout << "Dynamic_Static.Core " << version.to_string() << std::endl;
    return 0;
}
