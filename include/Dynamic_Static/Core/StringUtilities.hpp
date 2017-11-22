
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/String.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

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
