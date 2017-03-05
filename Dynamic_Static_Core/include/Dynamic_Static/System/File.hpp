
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <string>
#include <vector>

namespace Dynamic_Static {
    namespace System {
        namespace File {
            /**
             * Removes a specified file.
             * @param [in] filePath The path to the file to remove
             */
            void remove(const std::string& filePath);

            /**
             * Gets all of the bytes in a specified file.
             * @param [in] filePath The path to the file to read bytes from
             * @return An std::vector<uint8_t> of all bytes from the file
             */
            std::vector<uint8_t> read_bytes(const std::string& filePath);

            /**
             * Gets all of the bytes in a specified file.
             * @param [in] filePath The path to the file to read bytes from
             * @param [out] bytes An std::vector<uint8_t> to fill with all bytes from the file
             */
            void read_bytes(const std::string& filePath, std::vector<uint8_t>& bytes);

            /**
             * Gets the contents of a specified file as an std::string.
             * @param [in] filePath The path to the file to get the contents from
             * @return An std::string containing the contents of the specified file
             */
            std::string read_string(const std::string& filePath);

            /**
             * Gets the contents of a specified file as an std::string.
             * @param [in] filePath The path to the file to get the contents from
             * @param [out] contents An std::string to fill with the contents of the file
             */
            void read_string(const std::string& filePath, std::string& contents);
        } // namespace File
    } // namespace System
} // namespace Dynamic_Static
