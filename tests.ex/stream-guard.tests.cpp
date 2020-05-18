
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
TODO : Documentation
*/
TEST_CASE("---", "[StreamGuard]")
{
    std::stringstream strStrm;
    strStrm << StreamGuard();
    CHECK(strStrm.str() == std::string());
}

/**
TODO : Documentation
*/
TEST_CASE("---0", "[StreamGuard]")
{
    std::stringstream strStrm;
    strStrm << StreamGuard("The", ' ', "quick", ' ', "brown") << ' ' << "fox";
    CHECK(strStrm.str() == "The quick brown fox");
}

/**
TODO : Documentation
*/
TEST_CASE("---1", "[StreamGuard]")
{
    std::stringstream strStrm;
    strStrm << "The" << StreamGuard(' ', std::string(), ' ', "brown") << ' ' << "fox";
    CHECK(strStrm.str() == "The fox");
}

} // namespace tests
} // namespace dst
