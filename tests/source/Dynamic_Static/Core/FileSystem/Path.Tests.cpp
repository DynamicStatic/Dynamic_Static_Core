
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

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

#include "catch.hpp"

#include <string>
#include <vector>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("scrub()", "[Path]")
    {
        auto path = dst::Path::scrub(
            "some//file/\\path/with\\various\\sources/and\\conventions.txt"
        );

        REQUIRE(
            path ==
            "some/file/path/with/various/sources/and/conventions.txt"
        );
    }

    TEST_CASE("combine()", "[Path]")
    {
        SECTION("Combine two paths")
        {
            std::string path0 = "some/file";
            std::string path1 = "path.ext";
            auto path = dst::Path::combine(path0, path1);
            REQUIRE(path == "some/file/path.ext");
        }

        SECTION("Combine several paths")
        {
            auto path = dst::Path::combine(
                std::array<std::string, 4> {
                    "some//file",
                    "/\\path/with",
                    "various\\sources",
                    "and\\conventions.txt"
                }
            );

            REQUIRE(
                path ==
                "some/file/path/with/various/sources/and/conventions.txt"
            );
        }
    }

    TEST_CASE("has_extension()", "[Path]")
    {
        SECTION("Path with extension")
        {
            std::string path = "some/file/path.ext";
            REQUIRE(dst::Path::has_extension(path) == true);
        }

        SECTION("Path without extension")
        {
            std::string path = "some/file/path";
            REQUIRE(dst::Path::has_extension(path) == false);
        }
    }

    TEST_CASE("extension()", "[Path]")
    {
        SECTION("Path with extension")
        {
            std::string path = "some/file/path";
            REQUIRE(dst::Path::extension(path).empty());
        }

        SECTION("Path without extension")
        {
            std::string path = "some/file/path.zip";
            REQUIRE(dst::Path::extension(path) == ".zip");
        }

        SECTION("Path with mult-extension")
        {
            std::string path = "some/file/path.tar.gz";
            REQUIRE(dst::Path::extension(path) == ".gz");
        }
    }

    TEST_CASE("remove_extension()", "[Path]")
    {
        SECTION("Path without extension")
        {
            std::string path = "some/file/path";
            REQUIRE(dst::Path::remove_extension(path) == "some/file/path");
        }

        SECTION("Path with extension")
        {
            std::string path = "some/file/path.zip";
            REQUIRE(dst::Path::remove_extension(path) == "some/file/path");
        }

        SECTION("Path with mult-extension, non-recursive")
        {
            std::string path = "some/file/path.tar.gz";
            REQUIRE(dst::Path::remove_extension(path) == "some/file/path.tar");
        }

        SECTION("Path with mult-extension, recursive")
        {
            std::string path = "some/file/path.tar.gz";
            REQUIRE(dst::Path::remove_extension(path, true) == "some/file/path");
        }
    }

    TEST_CASE("file_name()", "[Path]")
    {
        SECTION("Path without extension")
        {
            std::string path = "some/file/path";
            REQUIRE(dst::Path::file_name(path) == "path");
        }

        SECTION("Path with extension")
        {
            std::string path = "some/file/path.zip";
            REQUIRE(dst::Path::file_name(path) == "path.zip");
        }

        SECTION("Path with mult-extension, non-recursive")
        {
            std::string path = "some/file/path.tar.gz";
            REQUIRE(dst::Path::file_name(path) == "path.tar.gz");
        }
    }

    TEST_CASE("directory_name()", "[Path]")
    {
        SECTION("Path without extension")
        {
            std::string path = "some/file/path";
            REQUIRE(dst::Path::directory_name(path) == "some/file");
        }

        SECTION("Path with extension")
        {
            std::string path = "some/file/path.zip";
            REQUIRE(dst::Path::directory_name(path) == "some/file");
        }

        SECTION("Path with mult-extension, non-recursive")
        {
            std::string path = "some/file/path.tar.gz";
            REQUIRE(dst::Path::directory_name(path) == "some/file");
        }
    }

} // namespace Tests
} // namespace Dynamic_Static
