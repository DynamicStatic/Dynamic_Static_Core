
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
    * Reads all lines in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::string> to populate with the lines read from the file
    */
    inline void read_all_lines(
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
    * Reads all lines in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::string> populated with the lines read from the file
    */
    inline std::vector<std::string> read_all_lines(const std::string_view& filePath)
    {
        std::vector<std::string> lines;
        read_all_lines(filePath, lines);
        return lines;
    }

    /*
    * Reads all bytes in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::byte> to populate with the bytes read from the file
    */
    inline void read_all_bytes(
        const std::string_view& filePath,
        std::vector<std::byte>& bytes
    )
    {
        bytes.clear();
        std::ifstream file(filePath.data(), std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            auto size = file.tellg();
            bytes.resize(static_cast<size_t>(size));
            file.seekg(0, std::ios::beg);
            file.read(reinterpret_cast<char*>(bytes.data()), size);
        }
    }

    /*
    * Reads all bytes in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::byte> populated with the bytes read from the file
    */
    inline std::vector<std::byte> read_all_bytes(const std::string_view& filePath)
    {
        std::vector<std::byte> bytes;
        read_all_bytes(filePath, bytes);
        return bytes;
    }

} // namespace File
} // namespace Dynamic_Static