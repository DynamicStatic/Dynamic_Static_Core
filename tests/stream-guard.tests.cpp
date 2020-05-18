
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/core/stream-guard.hpp"

#include "catch2/catch.hpp"

#include <sstream>
#include <string>

namespace dst {
namespace tests {

/**
Validates that an empty StreamGuard<> produces an empty std::string
*/
TEST_CASE("Empty StreamGuard<>", "[StreamGuard<>]")
{
    std::stringstream strStrm;
    strStrm << StreamGuard();
    CHECK(strStrm.str() == std::string());
}

/**
Validates that a StreamGuard<> with no empty std::string elements passes all elements through
*/
TEST_CASE("StreamGuard<> with no empty elements", "[StreamGuard<>]")
{
    std::stringstream strStrm;
    strStrm << StreamGuard("The", ' ', "quick", ' ', "brown") << ' ' << "fox";
    CHECK(strStrm.str() == "The quick brown fox");
}

/**
Validates that a StreamGuard<> with an empty std::string element produces an empty std::string
*/
TEST_CASE("StreamGuard<> with empty element", "[StreamGuard<>]")
{
    std::stringstream strStrm;
    strStrm << "The" << StreamGuard(' ', std::string(), ' ', "brown") << ' ' << "fox";
    CHECK(strStrm.str() == "The fox");
}

} // namespace tests
} // namespace dst
