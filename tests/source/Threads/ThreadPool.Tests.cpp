
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/ThreadPool.hpp"
#include "Dynamic_Static/Core/Time.hpp"

#include "catch.hpp"

#include <thread>

namespace Dynamic_Static {
namespace Tests {

    static constexpr size_t WaitTarget { 5 };
    static constexpr size_t CounterTarget { 10 };

    static void sleep()
    {
        std::this_thread::sleep_for(Millisecond<>(16));
    }

    TEST_CASE("ThreadPool ctor() and dtor()", "[Threads.ThreadPool]")
    {
        REQUIRE_NOTHROW(ThreadPool());
    }

    TEST_CASE("ThreadPool push() and wait()", "[Threads.ThreadPool]")
    {
        int i = 0;
        char c = 0;
        float f = 0;
        bool b = false;
        ThreadPool threadPool;
        threadPool.push([&]() { sleep(); i = 1; });
        threadPool.push([&]() { sleep(); c = 1; });
        threadPool.push([&]() { sleep(); f = 1; });
        threadPool.push([&]() { sleep(); b = true; });
        REQUIRE(i == 0);
        REQUIRE(c == 0);
        REQUIRE(f == 0);
        REQUIRE(b == false);
        threadPool.wait();
        REQUIRE(i == 1);
        REQUIRE(c == 1);
        REQUIRE(f == 1);
        REQUIRE(b == true);
    }

    TEST_CASE("ThreadPool passes through wait() if no tasks are pending", "[Threads.ThreadPool]")
    {
        ThreadPool threadPool;
        bool passed = false;
        threadPool.wait();
        passed = true;
        REQUIRE(passed);
    }

    TEST_CASE("ThreadPool completes pending tasks before destruction", "[Threads.ThreadPool]")
    {
        int i = 0;
        char c = 0;
        float f = 0;
        bool b = false;
        auto threadPool = std::make_unique<ThreadPool>();
        threadPool->push([&]() { sleep(); i = 1; });
        threadPool->push([&]() { sleep(); c = 1; });
        threadPool->push([&]() { sleep(); f = 1; });
        threadPool->push([&]() { sleep(); b = true; });
        REQUIRE(i == 0);
        REQUIRE(c == 0);
        REQUIRE(f == 0);
        REQUIRE(b == false);
        threadPool.reset();
        REQUIRE(i == 1);
        REQUIRE(c == 1);
        REQUIRE(f == 1);
        REQUIRE(b == true);
    }

} // namespace Tests
} // namespace Dynamic_Static
