
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/FileSystem/File.hpp"
#include "../LoremIpsum.hpp"

#include "catch.hpp"
#include "gsl/span"

#include <string>
#include <vector>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("read_bytes()", "[File]")
    {
        SECTION("std::vector")
        {
            auto bytes = File::read_bytes(LoremIpsumFilePath);
            REQUIRE(memcmp(LoremIpsumLiteral, bytes.data(), bytes.size()) == 0);
        }
    }

    TEST_CASE("read_string()", "[File]")
    {
        auto str = File::read_string(LoremIpsumFilePath);
        REQUIRE(memcmp(LoremIpsumLiteral, str.data(), str.size()) == 0);
    }

} // namespace Tests
} // namespace Dynamic_Static
