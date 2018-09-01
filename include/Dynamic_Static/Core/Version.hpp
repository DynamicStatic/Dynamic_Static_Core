
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>

namespace Dynamic_Static {

    /*!
    Represents a Version with major, minor, and patch values.
    */
    struct Version final
    {
        /*!
        This Version's major value
        */
        int major { 0 };

        /*!
        This Version's minor value
        */
        int minor { 0 };

        /*!
        This Version's patch value
        */
        int patch { 0 };

        /*!
        Gets the std::string representation of this Version.
        @return The std::string representation of this Version
        */
        inline std::string to_string() const
        {
            return
                std::to_string(major) + "." +
                std::to_string(minor) + "." +
                std::to_string(patch);
        }
    };

} // namespace Dynamic_Static
