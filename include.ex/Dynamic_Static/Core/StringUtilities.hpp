
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

#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <string_view>

namespace Dynamic_Static {

    class string_view
        : public std::string_view
    {
    public:
        string_view(const std::string_view& strView)
            : std::string_view(strView)
        {
        }

        string_view(const std::string& str)
            : std::string_view(str)
        {
        }

        string_view(const char* cStr)
            : std::string_view(cStr, cStr ? strlen(cStr) : 0)
        {
        }

        string_view(const char& c)
            : std::string_view(&c, 1)
        {
        }
    };

    /*
    * Replaces all occurences of a given substring from a given string.
    * @param [in] str The source string
    * @param [in] find The string to find and replace in the source string
    * @param [in] replacement The string to replace found occurences with
    * @param [in] recursive (default = false) Whether or not to recursively replace occurences of the find string
    * @return The resulting string
    */
    inline std::string replace(
        const dst::string_view& str,
        const dst::string_view& find,
        const dst::string_view& replacement,
        bool recursive = false
    )
    {
        std::string result(str.begin(), str.end());
        if (!find.empty() && find != replacement) {
            auto index = result.find(find);
            while (index != std::string::npos) {
                result.replace(index, find.size(), replacement);
                index += recursive ? 0 : replacement.size();
                index = result.find(find, index);
            }
        }
        return result;
    }

    /*
    * Removes all occurences of a given substring from a given string.
    * @param [in] str The source string
    * @param [in] find The string to find and remove from the source string
    * @param [in] recursive (default = false) Whether or not to recursively remove occurences of the find string
    * @return The resulting string
    */
    inline std::string remove(
        const dst::string_view& str,
        const dst::string_view& find,
        bool recursive = false
    )
    {
        return dst::replace(str, find, nullptr, recursive);
    }

    /**
    * Reduces repetitive occurences of a given substring to single occurences.
    * @param [in] str The source string
    * @param [in] find The string to find and reduce
    * @return The resulting string
    */
    inline std::string reduce_sequence(
        const dst::string_view& str,
        const dst::string_view& find
    )
    {
        std::string sequence(find.begin(), find.end());
        return dst::replace(str, sequence + sequence, find, true);
    }

    /**
    * Scrubs a given path.
    * @param [in] path The path to scrub
    * @reutrn The scrubbed path
    */
    inline std::string scrub_path(const std::string_view& path)
    {
        return dst::reduce_sequence(dst::replace(path, '\\', '/'), '/');
    }

    /**
    * Converts a char to upper case.
    * @param [in] c The char to convert to upper case
    * @return The resulting char
    */
    inline char to_upper(char c)
    {
        return static_cast<char>(std::toupper(static_cast<int>(c)));
    }

    /**
    * Converts a string to upper case.
    * @param [in] str The string to convert to upper case
    * @return The resulting string
    */
    inline std::string to_upper(const dst::string_view& str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_upper(c);
        }
        return result;
    }

    /**
    * Converts a char to lower case.
    * @param [in] c The char to convert to lower case
    * @return The resulting char
    */
    inline char to_lower(char c)
    {
        return static_cast<char>(std::tolower(static_cast<int>(c)));
    }

    /**
    * Converts a string to lower case.
    * @param [in] str The string to convert to lower case
    * @return The resulting string
    */
    inline std::string to_lower(const std::string_view& str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_lower(c);
        }
        return result;
    }

    /**
    * Gets the string representation of the hex value of a given integral value.
    * @param <T> The type of the given value
    * @return The string representation of the hex value of the given integral value
    */
    template <typename T>
    inline std::string to_hex_string(const T& value)
    {
        static_assert(
            std::is_integral<T>::value,
            "dst::to_hex_string() can only be used with integer types"
        );
        std::stringstream strStr;
        strStr << "0x" << std::hex << value;
        return strStr.str();
    }

} // namespace Dynamic_Static
