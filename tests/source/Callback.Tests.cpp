
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Callback.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    class Caller final
    {
    public:
        Callback<Caller> on_action;
    };

    TEST_CASE("operator bool()", "[Callback]")
    {
        Caller caller;
        REQUIRE(caller.on_action == false);
        caller.on_action = []() { };
        REQUIRE(caller.on_action == true);
        caller.on_action = nullptr;
        REQUIRE(caller.on_action == false);
    }

} // namespace Tests
} // namespace Dynamic_Static
