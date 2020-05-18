
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/core/random.hpp"
#include "dynamic_static/core/span.hpp"

#include "catch2/catch.hpp"

#include <vector>

namespace dst {
namespace tests {

static constexpr int TestCount { 8 };

/**
Validates that empty Span<> objects behave correctly
*/
TEST_CASE("Empty Span<>", "[Span<>]")
{
    SECTION("Default constructed Span<>")
    {
        Span<int> span;
        CHECK(span.empty());
        CHECK(span.size() == 0);
        CHECK(span.data() == nullptr);
        for (auto& i : span) {
            FAIL();
        }
    }
    SECTION("Span<> constructed with a nullptr and 0 count")
    {
        Span<int> span(nullptr, 0);
        CHECK(span.empty());
        CHECK(span.size() == 0);
        CHECK(span.data() == nullptr);
        for (auto& i : span) {
            FAIL();
        }
    }
    SECTION("Span<> constructed with a nullptr and TestCount count")
    {
        Span<int> span(nullptr, TestCount);
        CHECK(span.empty());
        CHECK(span.size() == 0);
        CHECK(span.data() == nullptr);
        for (auto& i : span) {
            FAIL();
        }
    }
    SECTION("Span<> constructed with a garbage pointer and 0 count")
    {
        Span<int> span((int*)(size_t)TestCount, 0);
        CHECK(span.empty());
        CHECK(span.size() == 0);
        CHECK(span.data() == nullptr);
        for (auto& i : span) {
            FAIL();
        }
    }
}

/**
Validates that iterating a Span<> iterates the referenced data correctly
*/
TEST_CASE("Iteration", "[Span<>]")
{
    RandomNumberGenerator rng;
    std::vector<float> floats(TestCount);
    for (auto& f : floats) {
        f = rng.value<float>();
    }
    Span<float> span = floats;
    SECTION("Index for")
    {
        CHECK(span.data() == floats.data());
        REQUIRE(span.size() == floats.size());
        for (size_t i = 0; i < span.size(); ++i) {
            if (span[i] != floats[i]) {
                FAIL();
            }
        }
    }
    SECTION("Iterator for()")
    {
        auto spanItr = span.begin();
        auto floatsItr = floats.begin();
        for (; spanItr != span.end() && floatsItr != floats.end(); ++spanItr, ++floatsItr) {
            if (*spanItr != *floatsItr) {
                FAIL();
            }
        }
        CHECK(spanItr == span.end());
        CHECK(floatsItr == floats.end());
    }
    SECTION("Range for()")
    {
        for (auto& f : span) {
            f = 3.14f;
        }
        for (auto f : floats) {
            if (f != 3.14f) {
                FAIL();
            }
        }
    }
}

/**
Validates Span<> comparison operators
*/
TEST_CASE("Comparison operators", "[Span<>]")
{
    RandomNumberGenerator rng;
    std::vector<std::vector<int>> intVectors(TestCount);
    for (auto& intVector : intVectors) {
        intVector.resize(rng.range(0, TestCount));
        for (auto& i : intVector) {
            i = rng.value<int>();
        }
    }
    for (auto itr = intVectors.begin(); itr != intVectors.end(); ++itr) {
        for (auto jtr = intVectors.begin(); jtr != intVectors.end(); ++jtr) {
            Span<int> span0 = *itr;
            Span<int> span1 = *jtr;
            if ((span0 == span1) != (*itr == *jtr) ||
                (span0 != span1) != (*itr != *jtr) ||
                (span0 <  span1) != (*itr <  *jtr) ||
                (span0 <= span1) != (*itr <= *jtr) ||
                (span0 >  span1) != (*itr >  *jtr) ||
                (span0 >= span1) != (*itr >= *jtr)) {
                FAIL();
            }
        }
    }
}

} // namespace tests
} // namespace dst
