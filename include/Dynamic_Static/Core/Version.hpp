
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

#include <string>

namespace Dynamic_Static {

    /**
     * Represents a Version with major, minor, and patch values.
     */
    struct Version final
    {
    public:
        uint32_t major { 0 };
        uint32_t minor { 0 };
        uint32_t patch { 0 };

        /**
         * Constructs an instance of Version.
         */
        Version() = default;

        /**
         * Constructs an instance of Version.
         * @param [in] major This Version's major value
         * @param [in] minor This Version's minor value
         * @param [in] patch This Version's patch value
         */
        Version(uint32_t major, uint32_t minor, uint32_t patch);

    public:
        /**
         * Gets the std::string representation of this Version.
         * @return The std::string representation of this Version
         */
        std::string to_string() const;
    };

} // namespace Dynamic_Static
