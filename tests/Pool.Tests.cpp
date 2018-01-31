
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Dynamic_Static
        Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Pool.hpp"

#include "catch.hpp"

#include <iostream>

namespace Dynamic_Static {
namespace Tests {

    class Foo final
    {
    private:
        float* mData { nullptr };

    public:
        void on_check_out()
        {
            std::cout << "Foo" << std::endl;
        }
    };

    class Bar final
    {
        friend Pool<Bar>;

    private:
        float* mData { nullptr };

    private:
        void on_check_out() const
        {
            std::cout << "Bar" << std::endl;
        }
    };

    class Baz final
    {
    private:
        float* mData { nullptr };
    };

    TEST_CASE("----", "[Pool]")
    {
        Pool<Foo> fooPool(4);
        Pool<Bar> barPool(4);
        Pool<Baz> bazPool(4);
        auto foo = fooPool.check_out();
        auto bar = barPool.check_out();
        auto baz = bazPool.check_out();
        bool passes = false;
        REQUIRE(passes);
    }

} // namespace Tests
} // namespace Dynamic_Static
