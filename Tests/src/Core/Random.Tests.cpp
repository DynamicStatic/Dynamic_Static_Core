
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

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

#include "catch.hpp"

#include "Dynamic_Static/Core/Random.hpp"

namespace Dynamic_Static {
    namespace Tests {
        static const int32_t g_test_max = 16;
        static const int32_t g_test_min = -g_test_max;
        static const size_t g_test_count = 1024;

        TEST_CASE("Integer values stay in range", "[Random]")
        {
            SECTION("range()")
            {
                bool in_range = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    int32_t value = Random.range<int32_t>(g_test_min, g_test_max);
                    if (value < g_test_min || g_test_max < value) {
                        in_range = false;
                        break;
                    }
                }

                REQUIRE(in_range);
            }

            SECTION("index()")
            {
                bool count_0_gets_index_0 = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    if (Random.index(0) != 0) {
                        count_0_gets_index_0 = false;
                        break;
                    }
                }

                bool count_1_gets_index_0 = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    if (Random.index(1) != 0) {
                        count_1_gets_index_0 = false;
                        break;
                    }
                }

                size_t count = 8;
                bool count_8_in_range = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    size_t index = Random.index(count);
                    if (index >= count) {
                        count_8_in_range = false;
                        break;
                    }
                }

                REQUIRE(count_0_gets_index_0);
                REQUIRE(count_1_gets_index_0);
                REQUIRE(count_8_in_range);
            }

            SECTION("die_roll()")
            {
                bool d0_rolls_0 = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    if (Random.die_roll(0) != 0) {
                        d0_rolls_0 = false;
                        break;
                    }
                }

                bool d1_rolls_1 = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    if (Random.die_roll(1) != 1) {
                        d1_rolls_1 = false;
                        break;
                    }
                }

                bool d6_rolls_in_range = true;
                for (size_t i = 0; i < g_test_count; ++i) {
                    uint32_t roll = Random.die_roll(6);
                    if (roll < 1u || 6u < roll) {
                        d6_rolls_in_range = false;
                        break;
                    }
                }

                REQUIRE(d0_rolls_0);
                REQUIRE(d1_rolls_1);
                REQUIRE(d6_rolls_in_range);
            }
        }

        TEST_CASE("Floating point values stay in range", "[Random]")
        {
            SECTION("range()")
            {
                bool in_range = true;
                float min = static_cast<float>(g_test_min);
                float max = static_cast<float>(g_test_max);
                for (size_t i = 0; i < g_test_count; ++i) {
                    float value = Random.range<float>(min, max);
                    if (value < min || max < value) {
                        in_range = false;
                        break;
                    }
                }

                REQUIRE(in_range);
            }
        }

        TEST_CASE("Resetting produces deterministic sequences", "[Random]")
        {
            Random.reset();
            float min = static_cast<float>(g_test_min);
            float max = static_cast<float>(g_test_max);
            std::vector<float> sequence(g_test_count);
            for (size_t i = 0; i < g_test_count; ++i) {
                sequence[i] = Random.range<float>(min, max);
            }

            Random.reset();
            bool deterministic = true;
            for (size_t i = 0; i < g_test_count; ++i) {
                if (Random.range<float>(min, max) != sequence[i]) {
                    deterministic = false;
                    break;
                }
            }

            REQUIRE(deterministic);
        }
    }
}
