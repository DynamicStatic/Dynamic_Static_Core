
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <string>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("to_string()", "[ToString]")
    {
        auto i = dst::Random.value<int>();
        REQUIRE(dst::to_string(i) == std::to_string(i));

        auto l = dst::Random.value<long>();
        REQUIRE(dst::to_string(l) == std::to_string(l));

        auto ll = dst::Random.value<long long>();
        REQUIRE(dst::to_string(ll) == std::to_string(ll));

        auto ull = dst::Random.value<unsigned long long>();
        REQUIRE(dst::to_string(ull) == std::to_string(ull));

        auto f = dst::Random.value<float>();
        REQUIRE(dst::to_string(f) == std::to_string(f));

        auto d = dst::Random.value<double>();
        REQUIRE(dst::to_string(d) == std::to_string(d));

        auto ld = dst::Random.value<long double>();
        REQUIRE(dst::to_string(ld) == std::to_string(ld));
    }

} // namespace Tests
} // namespace Dynamic_Static
