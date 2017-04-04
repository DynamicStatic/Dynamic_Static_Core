
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

#include "Dynamic_Static/Core/StringUtilities.hpp"

#include <algorithm>

namespace Dynamic_Static {
    namespace detail {
        static std::string replace(const std::string& str, const std::string& find, const std::string& replacement, bool recursive);
    } // namespace detail
} // namespace Dynamic_Static

namespace Dynamic_Static {
    std::string remove(const std::string& str, char find)
    {
        return remove(str, std::string { find });
    }

    std::string remove(const std::string& str, const std::string& find)
    {
        return replace(str, find, std::string());
    }

    std::string replace(const std::string& str, char find, char replacement)
    {
        return replace(str, std::string { find }, std::string { replacement });
    }

    std::string replace(const std::string& str, char find, const std::string& replacement)
    {
        return replace(str, std::string { find }, replacement);
    }

    std::string replace(const std::string& str, const std::string& find, char replacement)
    {
        return replace(str, find, std::string { replacement });
    }

    std::string replace(const std::string& str, const std::string& find, const std::string& replacement)
    {
        return detail::replace(str, find, replacement, false);
    }

    std::string reduce_sequence(const std::string& str, char find)
    {
        return detail::replace(str, std::string { find, find }, std::string { find }, true);
    }

    std::string to_lower(const std::string& str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), tolower);
        return result;
    }

    std::string to_upper(const std::string& str)
    {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), toupper);
        return result;
    }
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace detail {
        static std::string replace(const std::string& str, const std::string& find, const std::string& replacement, bool recursive)
        {
            std::string replacedStr = str;
            if (find.length()) {
                size_t index = replacedStr.find(find);
                while (index != std::string::npos) {
                    replacedStr.replace(index, find.size(), replacement);
                    index += recursive ? 0 : replacement.size();
                    index = replacedStr.find(find, index);
                }
            }

            return replacedStr;
        }
    } // namespace detail
} // namespace Dynamic_Static
