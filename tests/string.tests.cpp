
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
Validates that string::Proxy constructs correctly
*/
TEST_CASE("string::Proxy::Proxy()", "[string]")
{
    SECTION("string::Proxy::Proxy(char)")
    {
        string::Proxy proxy('c');
        CHECK(proxy == "c");
    }
    SECTION("string::Proxy::Proxy(std::string)")
    {
        string::Proxy proxy(TheQuickBrownFox);
        CHECK(proxy == TheQuickBrownFox);
    }
    SECTION("string::Proxy::Proxy(const char*) (valid)")
    {
        string::Proxy proxy(TheQuickBrownFox.c_str());
        CHECK(proxy == TheQuickBrownFox);
    }
    SECTION("string::Proxy::Proxy(const char*) (invalid)")
    {
        char* pStr = nullptr;
        string::Proxy proxy(pStr);
        CHECK(proxy == std::string());
    }
}

/**
Validates string::contains()
*/
TEST_CASE("string::contains()", "[string]")
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
Validates string::starts_with()
*/
TEST_CASE("string::starts_with()", "[string]")
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
Validates string::replace()
*/
TEST_CASE("string::replace()", "[string]")
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
Validates string::remove()
*/
TEST_CASE("string::remove()", "[string]")
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
Validates string::reduce_sequence()
*/
TEST_CASE("string::reduce_sequence()", "[string]")
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
Validates string::scrub_path()
*/
TEST_CASE("string::scrub_path()", "[string]")
{
    std::string str = "some//file/\\path/with\\various\\//conventions.txt";
    REQUIRE(string::scrub_path(str) == "some/file/path/with/various/conventions.txt");
}

/**
Validates string::scrub_path()
*/
TEST_CASE("string::is_whitespace()", "[string]")
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
Validates string::trim_leading_whitespace()
*/
TEST_CASE("string::trim_leading_whitespace()", "[string]")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_leading_whitespace(str) == TheQuickBrownFox + "        ");
}

/**
Validates string::trim_trailing_whitespace()
*/
TEST_CASE("string::trim_trailing_whitespace()", "[string]")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_trailing_whitespace(str) == "        " + TheQuickBrownFox);
}

/**
Validates string::trim_whitespace()
*/
TEST_CASE("string::trim_whitespace()", "[string]")
{
    auto str = "        " + TheQuickBrownFox + "        ";
    REQUIRE(string::trim_whitespace(str) == TheQuickBrownFox);
}

/**
Validates string::is_upper()
*/
TEST_CASE("string::is_upper()", "[string]")
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
Validates string::to_upper()
*/
TEST_CASE("string::to_upper()", "[string]")
{
    REQUIRE(string::to_upper(TheQuickBrownFox) == "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!");
}

/**
Validates string::is_lower()
*/
TEST_CASE("string::is_lower()", "[string]")
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
Validates string::to_lower()
*/
TEST_CASE("string::to_lower()", "[string]")
{
    REQUIRE(string::to_lower("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!") == "the quick brown fox jumps over the lazy dog!");
}

/**
Validates string::get_line()
*/
TEST_CASE("string::get_line()", "[string]")
{
    std::vector<std::string> lines {
        { "The quick\n" },
        { "brown fox\n" },
        { "jumps over\n" },
        { "the lazy\n" },
        { "dog." },
    };
    std::string str;
    for (auto const& line : lines) {
        str += line;
    }
    CHECK(string::get_line(str, str.find("quick")) == lines[0]);
    CHECK(string::get_line(str, str.find("brown")) == lines[1]);
    CHECK(string::get_line(str, str.find("over")) == lines[2]);
    CHECK(string::get_line(str, str.find("lazy")) == lines[3]);
    CHECK(string::get_line(str, str.find("dog")) == lines[4]);
}

/**
Validates string::split()
*/
TEST_CASE("string::split()", "[string]")
{
    const std::vector<std::string> Tokens { "The", "quick", "brown", "fox" };
    SECTION("Empty str")
    {
        REQUIRE(string::split(std::string(), " ").empty());
    }
    SECTION("char delimiter")
    {
        REQUIRE(string::split("The;quick;brown;fox", ';') == Tokens);
    }
    SECTION("char delimiter (prefix)")
    {
        REQUIRE(string::split(";The;quick;brown;fox", ';') == Tokens);
    }
    SECTION("char delimiter (postfix)")
    {
        REQUIRE(string::split("The;quick;brown;fox;", ';') == Tokens);
    }
    SECTION("char delimiter (prefix and postfix)")
    {
        REQUIRE(string::split(";The;quick;brown;fox;", ';') == Tokens);
    }
    SECTION("std::string delimiter")
    {
        REQUIRE(string::split("The COW quick COW brown COW fox COW ", " COW ") == Tokens);
    }
}

/**
Validates string::split_snake_case()
*/
TEST_CASE("string::split_snake_case()", "[string]")
{
    const std::vector<std::string> Tokens { "the", "quick", "brown", "fox" };
    REQUIRE(string::split_snake_case("the_quick_brown_fox") == Tokens);
}

/**
Validates string::split_camel_case()
*/
TEST_CASE("string::split_camel_case()", "[string]")
{
    const std::vector<std::string> Tokens { "The", "Quick", "Brown", "FOX" };
    REQUIRE(string::split_camel_case("TheQuickBrownFOX") == Tokens);
}

/**
Validates string::to_hex_string()
*/
TEST_CASE("to_hex_string()", "[string]")
{
    REQUIRE(to_hex_string(3735928559) == "0xdeadbeef");
    REQUIRE(to_hex_string(3735928559, false) == "deadbeef");
}

} // namespace tests
} // namespace dst
