
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
        int major { 0 }; /*!< TODO : Documentation. */
        int minor { 0 }; /*!< TODO : Documentation. */
        int patch { 0 }; /*!< TODO : Documentation. */

        /**
         * TODO : Documentation.
         */
        Version(int major = 0, int minor = 0, int patch = 0);

        /**
         * TODO : Documentation.
         */
        std::string to_string() const;

        /**
         * TODO : Documentation.
         */
        std::wstring to_wstring() const;
    };

} // namespace Dynamic_Static
