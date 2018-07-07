
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/StringUtilities.hpp"

#include "catch.hpp"

#include <string>

namespace Dynamic_Static {
namespace Tests {

    static const std::string TestString { "The quick brown fox jumps over the lazy dog!" };

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
            str = dst::replace(str, "fox", "fox");
            str = dst::replace(str, nullptr, "cat");
            str = dst::replace(str, std::string(), "bird");
            REQUIRE(str == TestString);
        }
    }

    TEST_CASE("remove()", "[StringUtilities]")
    {
        std::string str = TestString;
        str = dst::remove(str, " brow");
        str = dst::remove(str, 'n');
        str = dst::remove(str, " lazy");
        str = dst::remove(str, "-dog-");
        REQUIRE(str == "The quick fox jumps over the dog!");
    }

    TEST_CASE("reduce_sequence()", "[StringUtilities]")
    {
        std::string str = "some\\ugly\\/\\//\\path\\with\\a/////broken\\\\extension.....ext";
        str = dst::replace(str, '\\', '/');
        str = dst::reduce_sequence(str, '/');
        str = dst::reduce_sequence(str, '.');
        str = dst::replace(str, "ugly", "nice");
        str = dst::replace(str, "broken", "decent");
        REQUIRE(str == "some/nice/path/with/a/decent/extension.ext");
    }

    TEST_CASE("Case conversion works correctly", "[StringUtilities]")
    {
        std::string str = TestString;
        bool upperCase = true;
        for (auto& c : str) {
            c = upperCase ? dst::to_upper(c) : dst::to_lower(c);
            upperCase = !upperCase;
        }
        REQUIRE(str == "ThE QuIcK BrOwN FoX JuMpS OvEr tHe lAzY DoG!");
        REQUIRE(dst::to_upper(str) == "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!");
        REQUIRE(dst::to_lower(str) == "the quick brown fox jumps over the lazy dog!");
    }

} // namespace Tests
} // namespace Dynamic_Static
