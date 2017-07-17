
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

#include <string>

namespace Dynamic_Static
{
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
