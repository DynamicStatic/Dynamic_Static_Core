
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/FileSystem/Path.hpp"
#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/Core/FileSystem/StdFileSystemInclude.hpp"

#include <array>

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
        return dst::Path::combine(
            std::array<std::string, 2> { path0, path1 }
        );
    }

    std::string Path::combine(gsl::span<const std::string> paths)
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
