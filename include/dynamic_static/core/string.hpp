
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <algorithm>
#include <initializer_list>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace dst {
namespace string {

/**
TODO : Documentation
*/
static constexpr char WhiteSpaceCharacters[] = " \f\n\r\t\v";

/**
Provides a mechanism for safely constructing a tempory std::string
*/
class Proxy final
    : public std::string
{
public:
    using std::string::basic_string;

    /**
    Constructs an instance of string::Proxy
    @param [in] c The char to construct this string::Proxy from
    */
    Proxy(char c)
        : std::string(1, c)
    {
    }

    /**
    Constructs an instance of string::Proxy
    @param [in] str The std::string to construct this string::Proxy from
    */
    Proxy(const std::string& str)
        : std::string { str }
    {
    }

    /**
    Constructs an instance of string::Proxy
    @param [in] pStr The C string to construct this string::Proxy from
    */
    Proxy(const char* pStr)
        : std::string(pStr ? pStr : std::string())
    {
    }
};

/**
TODO : Documentation
*/
class Guard final
    : public std::string
{
public:
    /**
    TODO : Documentation
    */
    inline Guard(const std::initializer_list<Proxy>& strs)
    {
        for (auto const& str : strs) {
            if (!str.empty()) {
                operator+=(str);
            } else {
                clear();
                break;
            }
        }
    }
};

/**
Alias for std::pair<string::Proxy, string::Proxy> used for replace() operations
*/
using Replacement = std::pair<Proxy, Proxy>;

/**
Gets a value indicating whether or not a given string contains given find string
@param [in] str The string to search
@param [in] find The string to find
@return Whether or not the given string contains the given find string
*/
inline bool contains(
    const std::string& str,
    const Proxy& find
)
{
    return str.find(find.c_str()) != std::string::npos;
}

/**
Gets a value indicating whether or not a given string starts with a given find string
@param [in] str The string to search
@param [in] find The string to find
@return Whether or not the given string starts with the given find string
*/
inline bool starts_with(
    const std::string& str,
    const Proxy& find
)
{
    return find.size() <= str.size() && str.substr(0, find.size()) == find;
}

/**
Gets a copy of a string with all occurences of a given substring replaced with another
@param [in] str The source string
@param [in] find The string to find and replace in the source string
@param [in] replacement The string to replace occurences of the find string with
@param [in] recursive (optional = false) Whether or not to recursively replace occurences of the find string
@return The resulting std::string
*/
inline std::string replace(
    const std::string& str,
    const Proxy& find,
    const Proxy& replacement,
    bool recursive = false
)
{
    auto result = str;
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

/**
Gets a copy of a string with a all occurences of a given collection of substrings replaced with a paired replacement
@param [in] str The source string
@param [in] replacements The collection of find and replace pairs
@return The resulting std::string
*/
inline std::string replace(
    const std::string& str,
    const std::vector<Replacement>& replacements
)
{
    auto result = str;
    auto sortedReplacements = replacements;
    std::sort(
        sortedReplacements.begin(),
        sortedReplacements.end(),
        [](const auto& lhs, const auto& rhs)
        {
            return lhs.first.length() > rhs.first.length();
        }
    );
    for (const auto& replacement : sortedReplacements) {
        result = replace(result, replacement.first, replacement.second);
    }
    return result;
}

/**
Gets a copy of a string with all occurences of a given substring removed
@param [in] str The source string
@param [in] find The string to find and remove from the source string
@param [in] recursive (optional = false) Whether or not to recursively remove occurences of the find string
@return The resulting std::string
*/
inline std::string remove(
    const std::string& str,
    const Proxy& find,
    bool recurisve = false
)
{
    return replace(str, find, std::string(), recurisve);
}

/**
Gets a copy of a string with a all occurences of a given collection of substrings removed
@param [in] str The source string
@param [in] finds The collection of strings to remove
@return The resulting std::string
*/
inline std::string remove(
    const std::string& str,
    const std::initializer_list<Proxy>& finds
)
{
    auto result = str;
    for (const auto& find : finds) {
        result = remove(result, find);
    }
    return result;
}

/**
Gets a copy of a string with all repetitive occurences of a given substring reduced to single occurences
@param [in] str The source string
@param [in] find The string to find sequences of and reduce
@return The resulting std::string
*/
inline std::string reduce_sequence(
    const std::string& str,
    const Proxy& find
)
{
    return replace(str, find + find, find, true);
}

/**
Gets a copy of a string containing a path with back slashes replaced with forward slashes and slash sequences reduced
@param [in] path The path to scrub
@return The resulting std::string
*/
inline std::string scrub_path(const std::string& path)
{
    return reduce_sequence(replace(path, '\\', '/'), '/');
}

/**
Gets a value indicating whether or not a specified char is a whitespace character
@param [in] c The char to check
@return Whether or not the specified char is a whitespace character
*/
inline bool is_whitespace(char c)
{
    return std::isspace((int)c);
}

/**
Gets a value indicating whether or not a given string is all whitespace characters
@param [in] str The string to check
@return Whether or not the given string is all whitespace characters
*/
inline bool is_whitespace(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_whitespace(c); });
}

/**
Gets a copy of string with all leading whitespace characters removed
@param [in] str The string to remove leading whitespace characters from
@return The resulting std::string
*/
inline std::string trim_leading_whitespace(const std::string& str)
{
    auto offset = str.find_first_not_of(WhiteSpaceCharacters);
    return offset == std::string::npos ? std::string() : str.substr(offset);
}

/**
Gets a copy of string with all trailing whitespace characters removed
@param [in] str The string to remove trailing whitespace characters from
@return The resulting std::string
*/
inline std::string trim_trailing_whitespace(const std::string& str)
{
    auto offset = str.find_last_not_of(WhiteSpaceCharacters);
    return offset == std::string::npos ? std::string() : str.substr(0, offset + 1);
}

/**
Gets a copy of string with all leading and trailing whitespace characters removed
@param [in] str The string to remove leading and trailing whitespace characters from
@return The resulting std::string
*/
inline std::string trim_whitespace(const std::string& str)
{
    return trim_leading_whitespace(trim_trailing_whitespace(str));
}

/**
Gets a value indicating whether or not a specified char is an upper case character
@param [in] c The char to check
@return Whether or not the specified char is an upper case character
*/
inline bool is_upper(char c)
{
    return std::isupper((int)c);
}

/**
Gets a value indicating whether or not a given string is all upper case characters
@param [in] str The string to check
@return Whether or not the given string is all upper case characters
*/
inline bool is_upper(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_upper(c); });
}

/**
Gets the upper case equivalent of a specififed character
@param [in] c The character to get the upper case equivalent of
@retuern The upper case equivalent of the specified character
*/
inline char to_upper(char c)
{
    return (char)std::toupper((int)c);
}

/**
Gets a copy of a given string with all characters converted to their upper case equivalents
@param [in] str The string to convert to upper case
@return The resulting std::string
*/
inline std::string to_upper(const std::string& str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return to_upper(c); });
    return result;
}

/**
Gets a value indicating whether or not a specified char is a lower case character
@param [in] c The char to check
@return Whether or not the specified char is a lower case character
*/
inline bool is_lower(char c)
{
    return std::islower((int)c);
}

/**
Gets a value indicating whether or not a given string is all lower case characters
@param [in] str The string to check
@return Whether or not the given string is all lower case characters
*/
inline bool is_lower(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_lower(c); });
}

/**
Gets the lower case equivalent of a specififed character
@param [in] c The character to get the lower case equivalent of
@retuern The lower case equivalent of the specified character
*/
inline char to_lower(char c)
{
    return (char)std::tolower((int)c);
}

/**
Gets a copy of a given string with all characters converted to their lower case equivalents
@param [in] str The string to convert to lower case
@return The resulting std::string
*/
inline std::string to_lower(const std::string& str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return to_lower(c); });
    return result;
}

/**
Gets a std::string populated with the line containing a specified index from a given string
@param [in] str The string to search for the line containing the specified index
@param [in] index The index to get the containing line for
@return The line containing the specified index from the given string
*/
inline std::string get_line(const std::string& str, size_t index)
{
    if (!str.empty() && index < str.size() - 1) {
        auto begin = index;
        while (0 < begin && str[begin--] != '\n') {
            if (str[begin] == '\n') {
                ++begin;
                break;
            }
        }
        auto end = index;
        while (end < str.size() && str[end++] != '\n');
        if (begin < end) {
            return str.substr(begin, end - begin);
        }
        return str;
    }
    return { };
}

/**
Gets a std::vector<std::string> populated with substrings of a given string using a given delimiter
@param [in] str The string to split
@param [in] delimiter The delimiter to search for
@return A std::vector<std::string> populated with split tokens
*/
inline std::vector<std::string> split(
    const std::string& str,
    const Proxy& delimiter
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

/**
Gets a std::vector<std::string> populated with substrings of a given string using a '_' as a delimiter
@param [in] str The string to split
@return A std::vector<std::string> populated with split tokens
*/
inline std::vector<std::string> split_snake_case(const std::string& str)
{
    return split(str, '_');
}

/**
Gets a std::vector<std::string> populated with substrings of a given string split on CamelCase
@param [in] str The string to split
@return A std::vector<std::string> populated with split tokens
*/
inline std::vector<std::string> split_camel_case(const std::string& str)
{
    std::vector<std::string> tokens;
    if (!str.empty()) {
        auto begin = std::find_if_not(str.begin(), str.end(), [](char c) { return c == '_'; });
        while (begin != str.end()) {
            auto end = std::find_if(std::next(begin), str.end(), [](char c) { return c == '_' || is_upper(c); });
            tokens.emplace_back(begin, end);
            begin = std::find_if_not(end, str.end(), [](char c) { return c == '_'; });
        }
        for (size_t leadToken_i = 0; leadToken_i < tokens.size(); ++leadToken_i) {
            auto& leadToken = tokens[leadToken_i];
            if (leadToken.size() == 1) {
                size_t followToken_i = leadToken_i + 1;
                while (followToken_i < tokens.size() && tokens[followToken_i].size() == 1) {
                    leadToken += tokens[followToken_i];
                    tokens.erase(tokens.begin() + followToken_i);
                }
            }
        }
    }
    return tokens;
}

} // namespace string

/**
Gets the hex std::string representation of a specified value
@param <T> The type of value to get the hex std::string representation of
@param [in] value The value to get the hex std::string representation of
@param [in] prepend0x (optional = true) Whether or not to prepend the resulting std::string with "0x"
@return The hex std::string representation of the specified value
*/
template <typename T>
inline std::string to_hex_string(const T& value, bool prepend0x = true)
{
    static_assert(
        std::is_integral<T>::value,
        "dst::string::to_hex_string() may only be used with integer types"
    );
    std::stringstream strStr;
    if (prepend0x) {
        strStr << "0x";
    }
    strStr << std::hex << value;
    return strStr.str();
}

/**
Gets the std::string representation of a given object
@param <T> The type of object to get the std::string representation of
@param [in] obj The object to get the std::string representation of
@return The std::string representation of the given object
    @note This function may be specialized for arbitrary types
*/
template <typename T>
inline std::string to_string(const T& obj)
{
    return std::to_string(obj);
}

/**
Gets the std::wstring representation of a given object
@param <T> The type of object to get the std::wstring representation of
@param [in] obj The object to get the std::wstring representation of
@return The std::wstring representation of the given object
    @note This function may be specialized for arbitrary types
*/
template <typename T>
inline std::wstring to_wstring(const T& obj)
{
    return std::to_wstring(obj);
}

/**
TODO : Documentation
*/
template <>
inline std::wstring to_wstring<std::wstring>(const std::wstring& str)
{
    return str;
}

} // namespace dst
