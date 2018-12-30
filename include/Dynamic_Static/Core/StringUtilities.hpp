
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
#include "Dynamic_Static/Core/StringView.hpp"

#include <cctype>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace dst {

    /*!
    Gets a value indicating whether or not a given string contains another given string.
    @param [in] str The string to search
    @param [in] find The string to find
    @param [in] offset The offset to start searching from (optional = 0)
    */
    inline bool contains(
        dst::StringView str,
        dst::StringView find,
        size_t offset = 0
    )
    {
        // TODO : Why does std::basic_string_view find() not select
        //  dst::BasicStringView's conversion to const char*?
        return str.find(find.c_str(), offset) != std::string::npos;
    }

    /*!
    Gets a copy of a string with all occurences of a given substring replaced with another.
    @param [in] str The source string
    @param [in] find The string to find and replace in the source string
    @param [in] replacement The string to replace found occurences with
    @param [in] recursive (default = false) Whether or not to recursively replace occurences of the find string
    @return The resulting string
    */
    inline std::string replace(
        dst::StringView str,
        dst::StringView find,
        dst::StringView replacement,
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

    /*!
    Gets a copy of a string with a all occurences of a given collection of substrings replaced with a paired replacement.
    @param [in] str The source string
    @param [in] replacements The collection of  find and replace pairs
    @return The resulting string
    */
    inline std::string replace(
        dst::StringView str,
        std::vector<std::pair<std::string, std::string>> replacements
    )
    {
        std::string result = str;
        std::sort(replacements.begin(), replacements.end(),
            [](const auto& lhs, const auto& rhs)
            {
                return lhs.first.length() > rhs.first.length();
            }
        );
        for (const auto& replacement : replacements) {
            const auto& find = replacement.first;
            const auto& replace = replacement.second;
            result = dst::replace(result, find, replace);
        }
        return result;
    }

    /*!
    Gets a copy of a string with all occurences of a given substring removed.
    @param [in] str The source string
    @param [in] find The string to find and remove from the source string
    @param [in] recursive (default = false) Whether or not to recursively remove occurences of the find string
    @return The resulting string
    */
    inline std::string remove(
        dst::StringView str,
        dst::StringView find,
        bool recursive = false
    )
    {
        return dst::replace(str, find, nullptr, recursive);
    }

    /*!
    Gets a copy of a string with all repetitive occurences of a given substring reduced to single occurences.
    @param [in] str The source string
    @param [in] find The string to find and reduce
    @return The resulting string
    */
    inline std::string reduce_sequence(
        dst::StringView str,
        dst::StringView find
    )
    {
        std::string sequence(find.begin(), find.end());
        return dst::replace(str, sequence + sequence, find, true);
    }

    /*!
    Gets a copy of a string containing a path with back slashes replaced with forward slashes and slash sequences reduced.
    @param [in] path The path to scrub
    @reutrn The scrubbed path
    */
    inline std::string scrub_path(dst::StringView path)
    {
        return dst::reduce_sequence(dst::replace(path, "\\", "/"), "/");
    }

    /*!
    Gets an std::vector<std::string> populated with substrings of a given string using a given delimiter.
    @param [in] str The string to search for delimiters
    @param [in] delimiter The delimiter to search for
    @return An std::vector<std::string> populated with split tokens
    */
    inline std::vector<std::string> split(
        dst::StringView str,
        dst::StringView delimiter
    )
    {
        std::vector<std::string> tokens;
        if (!str.empty() && !delimiter.empty()) {
            size_t index = 0;
            size_t offset = 0;
            while ((index = str.find(delimiter.c_str(), offset)) != std::string::npos) {
                if (index - offset > 0) {
                    tokens.push_back(std::string(str.substr(offset, index - offset)));
                }
                offset = index + delimiter.size();
            }
            if (offset < str.length()) {
                tokens.push_back(std::string(str.substr(offset, str.length() - offset)));
            }
        }
        return tokens;
    }

    /*!
    Gets a value indicating whether or not a given string contains only whitespace
    @param [in] str The string to search
    @param [in] find The string to find
    @param [in] offset The offset to start searching from (optional = 0)
    */
    inline bool is_whitespace(dst::StringView str)
    {
        return std::all_of(str.begin(), str.end(), std::isspace);
    }

    /*!
    Gets the upper case version of a given char.
    @param [in] c The char to convert to upper case
    @return The resulting char
    */
    inline char to_upper(char c)
    {
        return (char)std::toupper((int)c);
    }

    /*!
    Gets a copy of an std::string with all characters converted to upper case.
    @param [in] str The string to convert to upper case
    @return The resulting string
    */
    inline std::string to_upper(dst::StringView str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_upper(c);
        }
        return result;
    }

    /*!
    Gets the lower case version of a given char.
    @param [in] c The char to convert to lower case
    @return The resulting char
    */
    inline char to_lower(char c)
    {
        return (char)std::tolower((int)c);
    }

    /*!
    Gets a copy of an std::string with all characters converted to lower case.
    @param [in] str The string to convert to lower case
    @return The resulting string
    */
    inline std::string to_lower(dst::StringView str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_lower(c);
        }
        return result;
    }

    /*!
    Gets the std::string representation of the hex value of a given integral value.
    @param <T> The type of the given value
    @return The string representation of the hex value of the given integral value
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

} // namespace dst
