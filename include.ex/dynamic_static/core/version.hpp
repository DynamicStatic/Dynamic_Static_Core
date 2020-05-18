
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#include "dynamic_static/core/string.hpp"

#include <ostream>
#include <string>

namespace dst {

/**
Represents a version with major, minor, and patch values
*/
struct Version final
{
    int major { 0 }; //!< This Version object's major value
    int minor { 0 }; //!< This Version object's minor value
    int patch { 0 }; //!< This Version object's patch value
};

/**
Gets the std::string representation of a given Version
@param [in] tab The Version to get the std::representation of
@return The std::string representation of the given Version
*/
template <>
inline std::string to_string<Version>(const Version& version)
{
    return
        std::to_string(version.major) + "." +
        std::to_string(version.minor) + "." +
        std::to_string(version.patch);
}

/**
Gets the std::wstring representation of a given Version
@param [in] tab The Version to get the std::wstring representation of
@return The std::wstring representation of the given Version
*/
template <>
inline std::wstring to_wstring<Version>(const Version& version)
{
    return
        std::to_wstring(version.major) + L"." +
        std::to_wstring(version.minor) + L"." +
        std::to_wstring(version.patch);
}

/**
Writes a given Version to a a given std::ostream
@param [in] stream The std::ostream to write the given Version to
@param [in] tab The Version to write to the given std::ostream
@return A reference to the given std::ostream
*/
inline std::ostream& operator<<(std::ostream& stream, const Version& version)
{
    stream << to_string(version);
    return stream;
}

} // namespace dst
