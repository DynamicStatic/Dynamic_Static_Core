
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/core/string.hpp"

#include "catch2/catch.hpp"

#include <string>

namespace dst {
namespace tests {

static const std::string TheQuickBrownFox { "The quick brown fox jumps over the lazy dog!" };

/**
TODO : Documentation
*/
TEST_CASE("string::contains()")
{
    SECTION("Successful true")
    {
        REQUIRE(string::contains(TheQuickBrownFox, "fox"));
        REQUIRE(string::contains(TheQuickBrownFox, "rown fox ju"));
        REQUIRE(string::contains(TheQuickBrownFox, 'j'));
        REQUIRE(string::contains(TheQuickBrownFox, '!'));
    }

    SECTION("Successful false")
    {
        REQUIRE_FALSE(string::contains(TheQuickBrownFox, "bat"));
        REQUIRE_FALSE(string::contains(TheQuickBrownFox, '7'));
        REQUIRE_FALSE(string::contains(TheQuickBrownFox, '?'));
    }

    SECTION("Empty str true")
    {
        REQUIRE(string::contains(TheQuickBrownFox, std::string()));
        REQUIRE(string::contains(std::string(), std::string()));
    }

    SECTION("Empty str false")
    {
        REQUIRE_FALSE(string::contains(std::string(), TheQuickBrownFox));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::starts_with()")
{
    SECTION("Successful true")
    {
        REQUIRE(string::starts_with(TheQuickBrownFox, 'T'));
        REQUIRE(string::starts_with(TheQuickBrownFox, "The"));
        REQUIRE(string::starts_with(TheQuickBrownFox, "The quick"));
        REQUIRE(string::starts_with(TheQuickBrownFox, TheQuickBrownFox));
    }

    SECTION("Successful false")
    {
        REQUIRE_FALSE(string::starts_with(TheQuickBrownFox, "he quick brown fox"));
        REQUIRE_FALSE(string::starts_with(TheQuickBrownFox, "the"));
        REQUIRE_FALSE(string::starts_with(TheQuickBrownFox, '8'));
    }

    SECTION("Empty str true")
    {
        REQUIRE(string::starts_with(TheQuickBrownFox, std::string()));
        REQUIRE(string::starts_with(std::string(), std::string()));
    }

    SECTION("Empty str false")
    {
        REQUIRE_FALSE(string::starts_with(std::string(), TheQuickBrownFox));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::replace()")
{
    SECTION("Successful replace")
    {
        auto str = TheQuickBrownFox;
        str = string::replace(str, '!', '.');
        str = string::replace(str, "quick", "slow");
        str = string::replace(str, "jumps", "trips");
        str = string::replace(str, "lazy", "sleeping");
        REQUIRE(str == "The slow brown fox trips over the sleeping dog.");
    }

    SECTION("Unsuccessful replace")
    {
        auto str = TheQuickBrownFox;
        str = string::replace(str, "fox", "fox");
        str = string::replace(str, std::string(), "bird");
        str = string::replace(str, "cat", "dog");
        str = string::replace(str, "frog", std::string());
        REQUIRE(str == TheQuickBrownFox);
    }

    SECTION("Empty str replace")
    {
        auto str = std::string();
        str = string::replace(str, '!', '.');
        str = string::replace(str, "quick", "slow");
        str = string::replace(str, "jumps", "trips");
        str = string::replace(str, "lazy", "sleeping");
        REQUIRE(str == std::string());
    }

    SECTION("Successful multi Replacement")
    {
        auto str = string::replace(
            TheQuickBrownFox,
            {
                { '!', '.' },
                { "quick", "slow" },
                { "jumps", "trips" },
                { "lazy", "sleeping" },
            }
        );
        REQUIRE(str == "The slow brown fox trips over the sleeping dog.");
    }

    SECTION("Unsuccessful multi Replacement")
    {
        auto str = string::replace(
            TheQuickBrownFox,
            {
                { "fox", "fox" },
                { std::string(), "bird" },
                { "cat", "dog" },
                { "frog", std::string() },
            }
        );
        REQUIRE(str == TheQuickBrownFox);
    }

    SECTION("Empty str multi Replacement")
    {
        auto str = string::replace(
            std::string(),
            {
                { "!", "." },
                { "quick", "slow" },
                { "jumps", "trips" },
                { "lazy", "sleeping" },
            }
        );
        REQUIRE(str == std::string());
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::remove()")
{
    SECTION("Successful remove")
    {
        auto str = TheQuickBrownFox;
        str = string::remove(str, "The ");
        str = string::remove(str, '!');
        str = string::remove(str, "brown ");
        str = string::remove(str, "lazy ");
        REQUIRE(str == "quick fox jumps over the dog");
    }

    SECTION("Unsuccessful remove")
    {
        auto str = TheQuickBrownFox;
        str = string::remove(str, '9');
        str = string::remove(str, "antelope");
        str = string::remove(str, "The  ");
        str = string::remove(str, "  fox  ");
        REQUIRE(str == TheQuickBrownFox);
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::reduce_sequence()")
{
    std::string str = "some\\ugly\\/\\//\\path\\with\\a/////broken\\\\extension.....ext";
    str = string::replace(str, '\\', "/");
    str = string::reduce_sequence(str, '/');
    str = string::reduce_sequence(str, ".");
    str = string::replace(str, "ugly", "nice");
    str = string::replace(str, "broken", "decent");
    REQUIRE(str == "some/nice/path/with/a/decent/extension.ext");
}

/**
TODO : Documentation
*/
TEST_CASE("string::scrub_path()")
{
    std::string str = "some//file/\\path/with\\various\\//conventions.txt";
    REQUIRE(string::scrub_path(str) == "some/file/path/with/various/conventions.txt");
}

/**
TODO : Documentation
*/
TEST_CASE("string::is_whitespace()")
{
    SECTION("Successful true")
    {
        REQUIRE(string::is_whitespace(' '));
        REQUIRE(string::is_whitespace('\f'));
        REQUIRE(string::is_whitespace('\n'));
        REQUIRE(string::is_whitespace('\r'));
        REQUIRE(string::is_whitespace('\t'));
        REQUIRE(string::is_whitespace('\v'));
        REQUIRE(string::is_whitespace(" \f\n\r\t\v"));
    }

    SECTION("Successful false")
    {
        REQUIRE_FALSE(string::is_whitespace('0'));
        REQUIRE_FALSE(string::is_whitespace(" \f\n\r  text \t\v"));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::trim_leading_whitespace()")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_leading_whitespace(str) == TheQuickBrownFox + "        ");
}

/**
TODO : Documentation
*/
TEST_CASE("string::trim_trailing_whitespace()")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_trailing_whitespace(str) == "        " + TheQuickBrownFox);
}

/**
TODO : Documentation
*/
TEST_CASE("string::trim_whitespace()")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_whitespace(str) == TheQuickBrownFox);
}

/**
TODO : Documentation
*/
TEST_CASE("string::is_upper()")
{
    SECTION("Successful true")
    {
        REQUIRE(string::is_upper('Z'));
        REQUIRE(string::is_upper("THE"));
    }

    SECTION("Successful false")
    {
        REQUIRE_FALSE(string::is_upper('z'));
        REQUIRE_FALSE(string::is_upper(TheQuickBrownFox));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::to_upper()")
{
    REQUIRE(string::to_upper(TheQuickBrownFox) == "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!");
}

/**
TODO : Documentation
*/
TEST_CASE("string::is_lower()")
{
    SECTION("Successful true")
    {
        REQUIRE(string::is_lower('z'));
        REQUIRE(string::is_lower("the"));
    }

    SECTION("Successful false")
    {
        REQUIRE_FALSE(string::is_lower('Z'));
        REQUIRE_FALSE(string::is_lower(TheQuickBrownFox));
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::to_lower()")
{
    REQUIRE(string::to_lower("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!") == "the quick brown fox jumps over the lazy dog!");
}

/**
TODO : Documentation
*/
TEST_CASE("string::split()")
{
    static const std::vector<std::string> Tokens { "The", "quick", "brown", "fox" };

    SECTION("Empty str")
    {
        REQUIRE(string::split(std::string(), " ").empty());
    }

    SECTION("Char delimiter")
    {
        REQUIRE(string::split("The;quick;brown;fox", ';') == Tokens);
    }

    SECTION("Char delimiter (prefix)")
    {
        REQUIRE(string::split(";The;quick;brown;fox", ';') == Tokens);
    }

    SECTION("Char delimiter (postfix)")
    {
        REQUIRE(string::split("The;quick;brown;fox;", ';') == Tokens);
    }

    SECTION("Char delimiter (prefix and postfix)")
    {
        REQUIRE(string::split(";The;quick;brown;fox;", ';') == Tokens);
    }

    SECTION("Str delimiter")
    {
        REQUIRE(string::split("The COW quick COW brown COW fox COW ", " COW ") == Tokens);
    }
}

/**
TODO : Documentation
*/
TEST_CASE("string::split_snake_case()")
{
    static const std::vector<std::string> Tokens { "the", "quick", "brown", "fox" };
    REQUIRE(string::split_snake_case("the_quick_brown_fox") == Tokens);
}

/**
TODO : Documentation
*/
TEST_CASE("string::split_camel_case()")
{
    static const std::vector<std::string> Tokens { "The", "Quick", "Brown", "FOX" };
    REQUIRE(string::split_camel_case("TheQuickBrownFOX") == Tokens);
}

/**
TODO : Documentation
*/
TEST_CASE("to_hex_string()")
{
    REQUIRE(to_hex_string(3735928559) == "0xdeadbeef");
    REQUIRE(to_hex_string(3735928559, false) == "deadbeef");
}

} // namespace tests
} // namespace dst
