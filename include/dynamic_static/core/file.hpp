
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
Reads all lines from the file at a given file path
@param [in] filePath The path of the file to read
@param [in] lines A reference to an std::vector<std::string> to populate with the lines read from the file at the given file path
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
Reads all lines from the file at a given file path
@param [in] filePath The path of the file to read
@return A std::vector<std::string> populated with the lines read from the file at the given file path
*/
inline std::vector<std::string> read_all_lines(const std::string& filePath)
{
    std::vector<std::string> lines;
    read_all_lines(filePath, lines);
    return lines;
}

/**
Reads all bytes from the file at a given file path
@param [in] filePath The path of the file to read
@param [in] bytes A reference to an std::vector<uint8_t> to populate with the bytes read from the file at the given file path
*/
inline void read_all_bytes(
    const std::string& filePath,
    std::vector<uint8_t>& bytes
)
{
    bytes.clear();
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        bytes.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read((char*)bytes.data(), bytes.size());
    }
}

/**
Reads all bytes from the file at a given file path
@param [in] filePath The path of the file to read
@return A std::vector<uint8_t> populated with the bytes read from the file at the given file path
*/
inline std::vector<uint8_t> read_all_bytes(const std::string& filePath)
{
    std::vector<uint8_t> bytes;
    read_all_bytes(filePath, bytes);
    return bytes;
}

} // namespace file
} // namespace dst
