
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

#include "Dynamic_Static/System/Path.hpp"
#include "Dynamic_Static/Core/FileSystem.hpp"
#include "Dynamic_Static/Core/StringUtilities.hpp"

namespace Dynamic_Static {
    namespace System {
        namespace Path {
            std::string scrub(const std::string& path)
            {
                std::string scrubbedPath = path;
                scrubbedPath = dst::filesystem::canonical(dst::filesystem::path(scrubbedPath)).string();
                scrubbedPath = dst::replace(scrubbedPath, '\\', '/');
                scrubbedPath = dst::reduce_sequence(scrubbedPath, '/');
                return scrubbedPath;
            }

            std::string combine(const std::string& path0, const std::string& path1)
            {
                return combine({ path0, path1 });
            }

            std::string combine(const Collection<std::string>& paths)
            {
                dst::filesystem::path combinedPath;
                for (const auto& path : paths) {
                    combinedPath /= path;
                }

                return scrub(combinedPath.string());
            }

            std::string extension(const std::string& path)
            {
                return dst::filesystem::path(path).extension().string();
            }

            bool has_extension(const std::string& path)
            {
                return dst::filesystem::path(path).has_extension();
            }

            std::string remove_extension(const std::string& path, bool recursive)
            {
                auto result = path;
                if (has_extension(path)) {
                    result = dst::remove(path, extension(path));
                    if (recursive) {
                       result = remove_extension(result, recursive);
                    }
                }

                return result;
            }

            std::string file_name(const std::string& path)
            {
                return dst::filesystem::path(path).filename().string();
            }

            std::string directory_name(const std::string& path)
            {
                return scrub(dst::filesystem::path(path).parent_path().string());
            }
        } // namespace Path
    } // namespace System
} // namespace Dynamic_Static
