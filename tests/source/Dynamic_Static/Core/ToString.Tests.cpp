
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
