
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Version.hpp"

namespace Dynamic_Static {

    Version::Version(int major, int minor, int patch)
        : major { major }
        , minor { minor }
        , patch { patch }
    {
    }

    std::string Version::to_string() const
    {
        return
            std::to_string(major) + "." +
            std::to_string(minor) + "." +
            std::to_string(patch);
    }

    std::wstring Version::to_wstring() const
    {
        return
            std::to_wstring(major) + L"." +
            std::to_wstring(minor) + L"." +
            std::to_wstring(patch);
    }

} // namespace Dynamic_Static
