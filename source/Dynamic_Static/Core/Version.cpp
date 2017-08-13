
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Version.hpp"

namespace Dynamic_Static {

    Version::Version(uint32_t major, uint32_t minor, uint32_t patch)
        : major { major }
        , minor { minor }
        , patch { patch }
    {
    }

    std::string Version::to_string() const
    {
        return
            dst::to_string(major) + "." +
            dst::to_string(minor) + "." +
            dst::to_string(patch);
    }

} // namespace Dynamic_Static
