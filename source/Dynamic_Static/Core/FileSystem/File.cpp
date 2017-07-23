
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

#include "Dynamic_Static/Core/FileSystem/File.hpp"
#include "Dynamic_Static/Core/BinaryReader.hpp"
#include "Dynamic_Static/Core/FileSystem/StdFileSystemInclude.hpp"

namespace Dynamic_Static {

    void File::remove(const std::string& /* filePath */)
    {
        // TODO : Clang compile.
        // dst::filesystem::remove(filePath);
    }

    std::vector<uint8_t> File::read_bytes(const std::string& filePath)
    {
        std::vector<uint8_t> bytes;
        dst::File::read_bytes(filePath, bytes);
        return bytes;
    }

    void File::read_bytes(const std::string& filePath, std::vector<uint8_t>& bytes)
    {
        bytes.clear();
        BinaryReader(filePath).contents(bytes);
    }

    std::string File::read_string(const std::string& filePath)
    {
        std::string str;
        dst::File::read_string(filePath, str);
        return str;
    }

    void File::read_string(const std::string& filePath, std::string& contents)
    {
        if (filePath.empty()) {
            // TODO : https://msdn.microsoft.com/en-us/library/dd383503(v=vs.110).aspx
            throw std::runtime_error("TODO : throw what : dst::File::read_string()");
        }

        contents.clear();
        auto bytes = BinaryReader(filePath).contents();
        char* begin = reinterpret_cast<char*>(&*bytes.begin());
        contents.reserve(bytes.size() + 1);
        contents.insert(0, begin, bytes.size());
        contents.append("\0");
    }

} // namespace Dynamic_Static
