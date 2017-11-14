
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/String.hpp"

namespace Dynamic_Static {

    String::String(char c)
        : mStr { c }
    {
    }

    String::String(const char* str)
        : mStr { str ? std::string(str) : std::string() }
    {
    }

    String::String(const std::string& str)
        : mStr { str }
    {
    }

    String::operator std::string&()
    {
        return mStr;
    }

    String::operator const std::string&() const
    {
        return mStr;
    }

} // namespace Dynamic_Static
