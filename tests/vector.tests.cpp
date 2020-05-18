
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/core/random.hpp"
#include "dynamic_static/core/vector.hpp"

#include "catch2/catch.hpp"

#include <set>
#include <string>
#include <vector>

namespace dst {
namespace tests {

static constexpr size_t TestCount { 128 };

/**
Validates vector::convert()
*/
TEST_CASE("vector::convert()", "[vector]")
{
    RandomNumberGenerator rng;
    std::vector<int> ints(TestCount);
    for (auto& i : ints) {
        i = rng.value<int>();
    }
    auto strings = vector::convert<int, std::string>(
        ints,
        [](int i)
        {
            return std::to_string(i);
        }
    );
    REQUIRE(strings.size() == ints.size());
    for (size_t i = 0; i < TestCount; ++i) {
        if (strings[i] != std::to_string(ints[i])) {
            FAIL();
        }
    }
}

/**
Validates vector::remove_duplicates()
*/
TEST_CASE("vector::remove_duplicates()", "[vector]")
{
    RandomNumberGenerator rng;
    std::vector<int> ints(TestCount);
    for (auto& i : ints) {
        i = rng.value<int>();
    }
    for (auto& i : ints) {
        if (rng.probability(0.5f)) {
            i = ints[rng.index(ints.size())];
        }
    }
    vector::remove_duplicates(ints);
    std::set<int> intSet;
    for (auto i : ints) {
        if (!intSet.insert(i).second) {
            FAIL();
        }
    }
}

} // namespace tests
} // namespace dst
