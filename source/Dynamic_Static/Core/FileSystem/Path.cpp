
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

#include "Dynamic_Static/Core/FileSystem/Path.hpp"
#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/Core/FileSystem/StdFileSystemInclude.hpp"

namespace Dynamic_Static {

    std::string Path::scrub(const std::string& path)
    {
        return dst::reduce_sequence(dst::replace(path, '\\', '/'),'/');
    }

    std::string Path::absolute(const std::string& path)
    {
        return dst::Path::scrub(dst::filesystem::canonical(path).string());
    }

    std::string Path::combine(const std::string& path0, const std::string& path1)
    {
        return dst::Path::combine({ path0, path1 });
    }

    std::string Path::combine(const Collection<std::string>& paths)
    {
        dst::filesystem::path combinedPath;
        for (const auto& path : paths) {
            combinedPath /= path;
        }

        return dst::Path::scrub(combinedPath.string());
    }

    bool Path::has_extension(const std::string& path)
    {
        return dst::filesystem::path(path).has_extension();
    }

    std::string Path::extension(const std::string& path)
    {
        return dst::filesystem::path(path).extension().string();
    }

    std::string Path::remove_extension(const std::string& path, bool recursive)
    {
        auto result = path;
        auto extension = dst::Path::extension(path);
        if (!extension.empty()) {
            result = dst::remove(result, extension);
            if (recursive) {
                result = dst::Path::remove_extension(result, recursive);
            }
        }

        return dst::Path::scrub(result);
    }

    std::string Path::file_name(const std::string& path)
    {
        return dst::filesystem::path(path).filename().string();
    }

    std::string Path::directory_name(const std::string& path)
    {
        return dst::Path::scrub(dst::filesystem::path(path).parent_path().string());
    }

} // namespace Dynamic_Static
