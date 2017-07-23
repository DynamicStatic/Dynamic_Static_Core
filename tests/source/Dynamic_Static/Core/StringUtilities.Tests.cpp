
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

#include "Dynamic_Static/Core/StringUtilities.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <cctype>
#include <string>

namespace Dynamic_Static {
namespace Tests {

    static const std::string TestString { "The quick brown fox jumps over the lazy dog!" };

    TEST_CASE("remove()", "[StringUtilities]")
    {
        std::string str = TestString;
        str = dst::remove(str, " brow");
        str = dst::remove(str, 'n');
        str = dst::remove(str, " lazy");
        str = dst::remove(str, "-dog-");
        REQUIRE(str == "The quick fox jumps over the dog!");
    }

    TEST_CASE("replace()", "[StringUtilities]")
    {
        SECTION("Valid input")
        {
            std::string str = TestString;
            str = dst::replace(str, '!', '.');
            str = dst::replace(str, "quick", "slow");
            str = dst::replace(str, "jumps", "trips");
            str = dst::replace(str, "lazy", "sleeping");
            REQUIRE(str == "The slow brown fox trips over the sleeping dog.");
        }

        SECTION("Invalid input")
        {
            std::string str = TestString;
            str = dst::replace(str, nullptr, "cat");
            str = dst::replace(str, std::string(), "bird");
            REQUIRE(str == TestString);
        }
    }

    TEST_CASE("reduce_sequence()", "[StringUtilities]")
    {
        std::string str = "some\\ugly\\/\\//\\path\\with\\a/////broken\\\\extension.....ext";
        str = dst::replace(str, '\\', '/');
        str = dst::reduce_sequence(str, '/');
        str = dst::reduce_sequence(str, '.');
        REQUIRE(str == "some/ugly/path/with/a/broken/extension.ext");
    }

    TEST_CASE("Case conversion works correctly", "[StringUtilities]")
    {
        std::string str = TestString;
        for (auto& c : str) {
            c = static_cast<char>(
                dst::Random.probability(50) ? std::toupper(c) : std::tolower(c)
            );
        }

        REQUIRE(dst::to_upper(str) == "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!");
        REQUIRE(dst::to_lower(str) == "the quick brown fox jumps over the lazy dog!");
    }

} // namespace Tests
} // namespace Dynamic_Static
