
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/StringUtilities.hpp"

#include <algorithm>
#include <cctype>

namespace Dynamic_Static {

    static std::string replace(
        const std::string& str,
        const std::string& find,
        const std::string& replacement,
        bool recursive = false
    )
    {
        std::string replacedStr = str;
        if (!find.empty()) {
            auto index = replacedStr.find(find);
            while (index != std::string::npos) {
                replacedStr.replace(index, find.size(), replacement);
                index += recursive ? 0 : replacement.size();
                index = replacedStr.find(find, index);
            }
        }

        return replacedStr;
    }

} // namespace Dynamic_Static

namespace Dynamic_Static {

    std::string remove(const std::string& str, const String& find)
    {
        return dst::replace(str, find, std::string(), false);
    }

    std::string replace(const std::string& str, const String& find, const String& replacement)
    {
        return dst::replace(str, find, replacement, false);
    }

    std::string reduce_sequence(const std::string& str, char find)
    {
        return dst::replace(str, std::string { find, find }, std::string { find }, true);
    }

    std::string to_upper(const std::string& str)
    {
        std::string result = str;
        for (auto& c : result) {
            c = static_cast<char>(std::toupper(c));
        }

        return result;
    }

    std::string to_lower(const std::string& str)
    {
        std::string result = str;
        for (auto& c : result) {
            c = static_cast<char>(std::tolower(c));
        }

        return result;
    }

} // namespace Dynamic_Static
