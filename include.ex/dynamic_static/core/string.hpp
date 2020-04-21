
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
class Proxy final
    : public std::string
{
public:
    using std::string::basic_string;

    /**
    TODO : Documentation
    */
    Proxy(std::nullptr_t)
    {
    }


    /**
    TODO : Documentation
    */
    Proxy(char c)
        : std::string(1, c)
    {
    }

    /**
    TODO : Documentation
    */
    Proxy(const std::string& str)
        : std::string { str }
    {
    }
};

/**
TODO : Documentation
*/
using Replacement = std::pair<Proxy, Proxy>;

/**
TODO : Documentation
*/
inline bool contains(
    const std::string& str,
    const Proxy& find
)
{
    return str.find(find.c_str()) != std::string::npos;
}

/**
TODO : Documentation
*/
inline bool starts_with(
    const std::string& str,
    const Proxy& find
)
{
    return find.size() <= str.size() && str.substr(0, find.size()) == find;
}

/**
TODO : Documentation
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
TODO : Documentation
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
TODO : Documentation
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
TODO : Documentation
*/
inline std::string reduce_sequence(
    const std::string& str,
    const Proxy& find
)
{
    return replace(str, find + find, find, true);
}

/**
TODO : Documentation
*/
inline std::string scrub_path(const std::string& path)
{
    return reduce_sequence(replace(path, '\\', '/'), '/');
}

/**
TODO : Documentation
*/
inline bool is_whitespace(char c)
{
    return std::isspace((int)c);
}

/**
TODO : Documentation
*/
inline bool is_whitespace(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_whitespace(c); });
}

/**
TODO : Documentation
*/
inline std::string trim_leading_whitespace(const std::string& str)
{
    auto offset = str.find_first_not_of(" \f\n\r\t\v");
    return offset == std::string::npos ? std::string() : str.substr(offset);
}

/**
TODO : Documentation
*/
inline std::string trim_trailing_whitespace(const std::string& str)
{
    auto offset = str.find_last_not_of(" \f\n\r\t\v");
    return offset == std::string::npos ? std::string() : str.substr(0, offset + 1);
}

/**
TODO : Documentation
*/
inline std::string trim_whitespace(const std::string& str)
{
    return trim_leading_whitespace(trim_trailing_whitespace(str));
}

/**
TODO : Documentation
*/
inline bool is_upper(char c)
{
    return std::isupper((int)c);
}

/**
TODO : Documentation
*/
inline bool is_upper(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_upper(c); });
}

/**
TODO : Documentation
*/
inline char to_upper(char c)
{
    return (char)std::toupper((int)c);
}

/**
TODO : Documentation
*/
inline std::string to_upper(const std::string& str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return to_upper(c); });
    return result;
}

/**
TODO : Documentation
*/
inline bool is_lower(char c)
{
    return std::islower((int)c);
}

/**
TODO : Documentation
*/
inline bool is_lower(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](char c) { return is_lower(c); });
}

/**
TODO : Documentation
*/
inline char to_lower(char c)
{
    return (char)std::tolower((int)c);
}

/**
TODO : Documentation
*/
inline std::string to_lower(const std::string& str)
{
    auto result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](char c) { return to_lower(c); });
    return result;
}

/**
TODO : Documentation
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
TODO : Documentation
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
TODO : Documentation
*/
inline std::vector<std::string> split_snake_case(const std::string& str)
{
    return split(str, '_');
}

/**
TODO : Documentation
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
} // namespace dst
