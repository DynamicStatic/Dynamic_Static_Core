
/*
==========================================
    Copyright 2011-2018 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>

namespace Dynamic_Static {

    /**
    * TODO : Documentation.
    */
    struct Version
    {
        int major { 0 }; /*!< This Version's major value */
        int minor { 0 }; /*!< This Version's minor value */
        int patch { 0 }; /*!< This Version's patch value */

        /**
        * TODO : Documentation.
        */
        inline Version(
            int major = 0,
            int minor = 0,
            int patch = 0
        )
            : major { major }
            , minor { minor }
            , patch { patch }
        {
        }

        /**
        * TODO : Documentation.
        */
        inline std::string to_string() const
        {
            return
                std::to_string(major) + "." +
                std::to_string(minor) + "." +
                std::to_string(patch);
        }

        /**
        * TODO : Documentation.
        */
        inline std::wstring to_wstring() const
        {
            return
                std::to_wstring(major) + L"." +
                std::to_wstring(minor) + L"." +
                std::to_wstring(patch);
        }
    };

} // namespace Dynamic_Static
