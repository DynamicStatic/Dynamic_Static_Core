
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

#include "Dynamic_Static/System/File.hpp"
#include "Dynamic_Static/Core/FileSystem.hpp"
#include "Dynamic_Static/Core/BinaryReader.hpp"

namespace Dynamic_Static {
    namespace System {
        namespace File {
            void remove(const std::string& filePath)
            {
                dst::filesystem::remove(filePath);
            }

            std::vector<uint8_t> read_bytes(const std::string& filePath)
            {
                std::vector<uint8_t> bytes;
                read_bytes(filePath, bytes);
                return bytes;
            }

            void read_bytes(const std::string& filePath, std::vector<uint8_t>& bytes)
            {
                bytes = BinaryReader(filePath).contents();
            }

            std::string read_string(const std::string& filePath)
            {
                std::string contents;
                read_string(filePath, contents);
                return contents;
            }

            void read_string(const std::string& filePath, std::string& contents)
            {
                contents.clear();
                auto bytes = BinaryReader(filePath).contents();
                char* begin = reinterpret_cast<char*>(&*bytes.begin());
                contents.reserve(bytes.size() + 1);
                contents.insert(0, begin, bytes.size());
                contents.append("\0");
            }
        } // namespace Dynamic_Static
    } // namespace System
} // namespace File
