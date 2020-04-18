
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#include "dynamic_static/core/to-string.hpp"

#include <string>

namespace dst {

/*!
TODO : Documentation
*/
struct Version final
{
    /**
    This Version object's major value
    */
    int major { 0 };

    /**
    This Version object's minor value
    */
    int minor { 0 };

    /**
    This Version objects's patch value
    */
    int patch { 0 };
};

/**
TODO : Documentation
*/
template <>
inline std::string to_string<Version>(const Version& version)
{
    return
        std::to_string(version.major) + "." +
        std::to_string(version.minor) + "." +
        std::to_string(version.patch);
}

} // namespace dst
