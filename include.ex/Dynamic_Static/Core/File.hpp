
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

#include <fstream>
#include <string>
#include <string_view>
#include <vector>

namespace Dynamic_Static {
namespace File {

    /*
    * TODO : Documentation.
    */
    inline void read_lines(
        const std::string_view& filePath,
        std::vector<std::string>& lines
    )
    {
        lines.clear();
        std::ifstream file(filePath.data());
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
        }
    }

    /*
    * TODO : Documentation.
    */
    inline std::vector<std::string> read_lines(const std::string_view& filePath)
    {
        std::vector<std::string> result;
        read_lines(filePath, result);
        return result;
    }

} // namespace File
} // namespace Dynamic_Static
