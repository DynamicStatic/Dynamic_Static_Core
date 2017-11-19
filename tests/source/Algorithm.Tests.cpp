
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("wrap()", "[Algorithm]")
    {
        REQUIRE(dst::wrap(0, 0, 0) != 0);
    }

} // namespace Tests
} // namespace Dynamic_Static
