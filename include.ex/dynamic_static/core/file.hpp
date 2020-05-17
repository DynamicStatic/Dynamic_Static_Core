
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

#include <fstream>
#include <string>
#include <vector>

namespace dst {
namespace file {

/**
TODO : Documentation
*/
inline void read_all_lines(
    const std::string& filePath,
    std::vector<std::string>& lines
)
{
    lines.clear();
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    }
}

/**
TODO : Documentation
*/
inline std::vector<std::string> read_all_lines(const std::string& filePath)
{
    std::vector<std::string> lines;
    read_all_lines(filePath, lines);
    return lines;
}

/**
TODO : Documentation
*/
inline void read_all_bytes(
    const std::string& filePath,
    std::vector<uint8_t>& bytes
)
{
    bytes.clear();
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        auto size = file.tellg();
        bytes.resize((size_t)size);
        file.seekg(0, std::ios::beg);
        file.read((char*)bytes.data(), size);
    }
}

/**
TODO : Documentation
*/
inline std::vector<uint8_t> read_all_bytes(const std::string& filePath)
{
    std::vector<uint8_t> bytes;
    read_all_bytes(filePath, bytes);
    return bytes;
}

} // namespace file
} // namespace dst
