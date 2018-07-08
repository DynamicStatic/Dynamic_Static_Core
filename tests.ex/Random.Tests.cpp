
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {

    static constexpr int MaxValue { 4 };
    static constexpr int MinValue { -MaxValue };
    static constexpr int TestCount = 1024;

    TEST_CASE("range()", "[Random]")
    {
        RandomNumberGenerator rng;

        SECTION("Integer values")
        {
            bool inRange = true;
            for (int i = 0; i < TestCount; ++i) {
                auto value = rng.range(MinValue, MaxValue);
                if (value < MinValue || MaxValue <= value) {
                    inRange = false;
                    break;
                }
            }
            REQUIRE(inRange);
        }

        SECTION("Floating point values")
        {
            bool inRange = true;
            float min = static_cast<float>(MinValue);
            float max = static_cast<float>(MaxValue);
            for (int i = 0; i < TestCount; ++i) {
                auto value = rng.range(min, max);
                if (value < MinValue || MaxValue <= value) {
                    inRange = false;
                    break;
                }
            }
        }
    }

    TEST_CASE("probability()", "[Random]")
    {
        RandomNumberGenerator rng;

        SECTION("Integer 0 always fails")
        {
            bool integer0AlwaysFails = true;
            for (int i = 0; i < TestCount; ++i) {
                if (rng.probability(0)) {
                    integer0AlwaysFails = false;
                }
            }
            REQUIRE(integer0AlwaysFails);
        }

        SECTION("Integer 100 always passes")
        {
            bool integer100AlwaysPasses = true;
            for (int i = 0; i < TestCount; ++i) {
                if (!rng.probability(100)) {
                    integer100AlwaysPasses = false;
                }
            }
            REQUIRE(integer100AlwaysPasses);
        }

        SECTION("Floating point 0 always fails")
        {
            bool floatingPoint0AlwaysFails = true;
            for (int i = 0; i < TestCount; ++i) {
                if (rng.probability(0.)) {
                    floatingPoint0AlwaysFails = false;
                }
            }
            REQUIRE(floatingPoint0AlwaysFails);
        }

        SECTION("Floating point 1 always passes")
        {
            bool floatingPoint1AlwaysPasses = true;
            for (int i = 0; i < TestCount; ++i) {
                if (!rng.probability(1.)) {
                    floatingPoint1AlwaysPasses = false;
                }
            }
            REQUIRE(floatingPoint1AlwaysPasses);
        }
    }

    TEST_CASE("index()", "[Random]")
    {
        RandomNumberGenerator rng;

        bool count0GetsIndex0 = true;
        for (int i = 0; i < TestCount; ++i) {
            if (rng.index(0) != 0) {
                count0GetsIndex0 = false;
                break;
            }
        }

        bool count1GetsIndex0 = true;
        for (int i = 0; i < TestCount; ++i) {
            if (rng.index(1) != 0) {
                count1GetsIndex0 = false;
                break;
            }
        }

        int count = 8;
        bool count8InRange = true;
        for (int i = 0; i < TestCount; ++i) {
            if (rng.index(count) >= count) {
                count8InRange = false;
                break;
            }
        }

        REQUIRE(count0GetsIndex0);
        REQUIRE(count1GetsIndex0);
        REQUIRE(count8InRange);
    }

    TEST_CASE("die_roll()", "[Random]")
    {
        RandomNumberGenerator rng;

        bool d0Rolls0 = true;
        for (int i = 0; i < TestCount; ++i) {
            if (rng.die_roll(0) != 0) {
                d0Rolls0 = false;
                break;
            }
        }

        bool d1Rolls1 = true;
        for (int i = 0; i < TestCount; ++i) {
            if (rng.die_roll(1) != 1) {
                d1Rolls1 = false;
                break;
            }
        }

        int dieSize = 6;
        bool d6RollsInRange = true;
        for (int i = 0; i < TestCount; ++i) {
            auto roll = rng.die_roll(dieSize);
            if (roll < 1 || dieSize < roll) {
                d6RollsInRange = false;
                break;
            }
        }

        REQUIRE(d0Rolls0);
        REQUIRE(d1Rolls1);
        REQUIRE(d6RollsInRange);
    }

    TEST_CASE("Resetting produces deterministic sequences", "[Random]")
    {
        RandomNumberGenerator rng;

        float min = static_cast<float>(MinValue);
        float max = static_cast<float>(MaxValue);
        std::vector<float> sequence(TestCount);
        for (size_t i = 0; i < TestCount; ++i) {
            sequence[i] = rng.range(min, max);
        }

        rng.reset();
        bool deterministic = true;
        for (size_t i = 0; i < TestCount; ++i) {
            if (rng.range(min, max) != sequence[i]) {
                deterministic = false;
                break;
            }
        }

        REQUIRE(deterministic);
    }

} // namespace Tests
} // namespace Dynamic_Static
