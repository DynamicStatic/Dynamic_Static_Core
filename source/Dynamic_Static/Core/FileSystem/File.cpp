
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
#include "Dynamic_Static/Core/NotImplementedError.hpp"

namespace Dynamic_Static {

    void File::remove(const std::string& /* filePath */)
    {
        // TODO : Clang compile.
        // dst::filesystem::remove(filePath);
        throw dst::NotImplementedError("File::remove()");
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
        BinaryReader(filePath).get_data(bytes);
    }

    std::string File::read_string(const std::string& filePath)
    {
        std::string str;
        dst::File::read_string(filePath, str);
        return str;
    }

    void File::read_string(const std::string& filePath, std::string& str)
    {
        // if (filePath.empty()) {
        //     // TODO : https://msdn.microsoft.com/en-us/library/dd383503(v=vs.110).aspx
        //     throw std::runtime_error("TODO : throw what : dst::File::read_string()");
        // }

        // TODO : This should be using a TextReader...
        str.clear();
        auto bytes = BinaryReader(filePath).get_data();
        char* begin = reinterpret_cast<char*>(&*bytes.begin());
        str.reserve(bytes.size() + 1);
        str.insert(0, begin, bytes.size());
        if (str.back() != '\0') {
            str.append("\0");
        }
    }

} // namespace Dynamic_Static
