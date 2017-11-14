
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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
