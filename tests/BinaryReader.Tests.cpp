
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/BinaryReader.hpp"
#include "LoremIpsum.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Throws on bad file path", "[BinaryReader]")
    {
        BinaryReader reader;
        REQUIRE_THROWS(reader.open("BOGUS!"));
    }

    TEST_CASE("get_size()", "[BinaryReader]")
    {
        BinaryReader reader(LoremIpsumFilePath);
        REQUIRE(reader.get_size() == sizeof(LoremIpsumLiteral) - sizeof('\0'));
        reader.close();
        REQUIRE(reader.get_size() == 0);
    }

    TEST_CASE("get_data()", "[BinaryReader]")
    {
        auto data = BinaryReader(LoremIpsumFilePath).get_data();
        REQUIRE(memcmp(LoremIpsumLiteral, data.data(), data.size()) == 0);
    }

} // namespace Tests
} // namespace Dynamic_Static
