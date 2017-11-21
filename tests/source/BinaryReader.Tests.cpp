
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/BinaryReader.hpp"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("----", "[BinaryReader]")
    {
        const char* loremIpsum =
            #include "LoremIpsum.txt"
            ;

        REQUIRE(true);
    }

} // namespace Tests
} // namespace Dynamic_Static
