
/*
==========================================
    Copyright 2020 Dynamic_Static
        Patrick Purcell
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <string>

namespace dst {

/**
TODO : Documentation
*/
template <typename T>
inline std::string to_string(const T& obj)
{
    return std::to_string(obj);
}

/**
TODO : Documentation
*/
template <typename T>
inline std::wstring to_wstring(const T& obj)
{
    return std::to_wstring(obj);
}

} // namespace dst
