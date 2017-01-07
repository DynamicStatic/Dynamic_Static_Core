
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>

namespace Dynamic_Static {
    /**
     * Removes all occurences of a character from an std::string.
     * @param [in] str  The std::string to operate on
     * @param [in] find The character to remove
     * @return An std::string with the completed removal
     */
    std::string remove(const std::string& str, char find);

    /**
     * Removes all occurences of an std::string from another std::string.
     * @param [in] str  The std::string to operate on
     * @param [in] find The std::string to remove
     * @return An std::string with the completed removal
     */
    std::string remove(const std::string& str, const std::string& find);

    /**
     * Replaces all occurences in an std::string of a character with another character.
     * @param [in] str         The std::string to operate on
     * @param [in] find        The character to replace
     * @param [in] replacement The character to replace with
     * @return An std::string with the completed replacement
     */
    std::string replace(const std::string& str, char find, char replacement);

    /**
     * Replaces all occurences in an std::string of a character with an std::string.
     * @param [in] str         The std::string to operate on
     * @param [in] find        The character to replace
     * @param [in] replacement The std::string to replace with
     * @return An std::string with the completed replacement
     */
    std::string replace(const std::string& str, char find, const std::string& replacement);

    /**
     * Replaces all occurences in an std::string of a character with another character.
     * @param [in] str         The std::string to operate on
     * @param [in] find        The std::string to replace
     * @param [in] replacement The character to replace with
     * @return An std::string with the completed replacement
     */
    std::string replace(const std::string& str, const std::string& find, char replacement);

    /**
     * Replaces all occurences in an std::string of a character with another character.
     * @param [in] str         The std::string to operate on
     * @param [in] find        The std::string to replace
     * @param [in] replacement The std::string to replace with
     * @return An std::string with the completed replacement
     */
    std::string replace(const std::string& str, const std::string& find, const std::string& replacement);

    /**
     * Reduces a sequence of characters to one character
     * @param [in] str  The std::string to operate on
     * @param [in] find The character to reduce sequences of
     * @return An std::string with the completed sequence reduction
     */
    std::string reduce_sequence(const std::string& str, char find);

    /**
     * Converts all upper case characters in an std::string to lower case.
     * @param [in] str The std::string to operator on
     * @return An std::string with all upper case characters converted to lower case
     */
    std::string to_lower(const std::string& str);

    /**
     * Converts all lower case characters in an std::string to upper case.
     * @param [in] str The std::string to operator on
     * @return An std::string with all lower case characters converted to upper case
     */
    std::string to_upper(const std::string& str);
}
