
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>
#include <vector>

namespace Dynamic_Static {
namespace File {

    /**
     * Deletes the file at a given path.
     * @param [in] filePath The path of the file to delete
     */
    void remove(const std::string& filePath);

    /**
     * Gets a std::vector populated with the contents of the file at a given path.
     * @param [in] filePath The path of the file to read
     * @return The contents of the file
     */
    std::vector<uint8_t> read_bytes(const std::string& filePath);

    /**
     * Populates a std::vector with the contents of the file at a given path.
     * @param [in]      filePath The path of the file to read
     * @param [in, out] bytes    The std::vector to populate with the file's contents
     */
    void read_bytes(const std::string& filePath, std::vector<uint8_t>& bytes);

    /**
     * Gets a std::string populated with the contents of the file at a given path.
     * @param [in] filePath The path of the file to read
     * @return The contents of the file
     */
    std::string read_string(const std::string& filePath);

    /**
     * Populates a std::string with the contents of the file at a given path.
     * @param [in]      filePath The path of the file to read
     * @param [in, out] contents The std::string to populate with the file's contents
     */
    void read_string(const std::string& filePath, std::string& contents);

} // namespace File
} // namespace Dynamic_Static
