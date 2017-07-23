
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
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
