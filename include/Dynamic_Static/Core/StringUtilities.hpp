
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
#include "Dynamic_Static/Core/String.hpp"

#include <string>

namespace Dynamic_Static {

    /**
     * Removes all occurences of a given character sequence from a given std::string.
     * @param [in] str  The std::string to remove the given character sequence from
     * @param [in] find The character sequence to find and remove
     * @return An std::string with the completed removal
     */
    std::string remove(const std::string& str, const dst::String& find);

    /**
     * Replaces all occurences of a given character sequence in a given std::string with another character sequence.
     * @param [in] str         The std::string to replace the given character sequence in
     * @param [in] find        The character sequence to find and replace
     * @param [in] replacement The character sequence to replace with
     * @return An std::string with the completed replacement
     */
    std::string replace(const std::string& str, const dst::String& find, const dst::String& replacement);

    /**
     * Reduces a repetitive sequence of characters to one character.
     * @param [in] str  The std::string to reduce sequence in
     * @param [in] find The character to reduce sequences of
     * @return An std::string with the completed sequence reduction
     */
    std::string reduce_sequence(const std::string& str, char find);

    /**
     * Converts an std::string to upper case.
     * @param [in] str The std::string to convert to upper case
     * @return An std::string with the completed case conversion
     */
    std::string to_upper(const std::string& str);

    /**
     * Converts an std::string to lower case.
     * @param [in] str The std::string to convert to lower case
     * @return An std::string with the completed case conversion
     */
    std::string to_lower(const std::string& str);

} // namespace Dynamic_Static
