
/*
==========================================
    Copyright (c) 20167 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/Worker.hpp"
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

    TEST_CASE("Worker ctor() and dtor()", "[Threads.Worker]")
    {
        REQUIRE_NOTHROW(Worker());
    }

    TEST_CASE("Worker push() and wait()", "[Threads.Worker]")
    {
        int i = 0;
        char c = 0;
        float f = 0;
        bool b = false;
        Worker worker;
        worker.push([&]() { sleep(); i = 1; });
        worker.push([&]() { sleep(); c = 1; });
        worker.push([&]() { sleep(); f = 1; });
        worker.push([&]() { sleep(); b = true; });
        REQUIRE(i == 0);
        REQUIRE(c == 0);
        REQUIRE(f == 0);
        REQUIRE(b == false);
        worker.wait();
        REQUIRE(i == 1);
        REQUIRE(c == 1);
        REQUIRE(f == 1);
        REQUIRE(b == true);
    }

    TEST_CASE("Worker passes through wait() if no tasks are pending", "[Threads.Worker]")
    {
        Worker worker;
        bool passed = false;
        worker.wait();
        passed = true;
        REQUIRE(passed);
    }

    TEST_CASE("Worker can time out wait()", "[Threads.Worker]")
    {
        size_t counter = 0;
        Worker worker;
        worker.push(
            [&]()
            {
                std::this_thread::sleep_for(Millisecond<>(100));
                ++counter;
            }
        );

        worker.wait(Millisecond<>(1));
        REQUIRE(counter == 0);
        worker.wait();
        REQUIRE(counter == 1);
    }

    TEST_CASE("Worker completes pending tasks before destruction", "[Threads.Worker]")
    {
        int i = 0;
        char c = 0;
        float f = 0;
        bool b = false;
        auto worker = std::make_unique<Worker>();
        worker->push([&]() { sleep(); i = 1; });
        worker->push([&]() { sleep(); c = 1; });
        worker->push([&]() { sleep(); f = 1; });
        worker->push([&]() { sleep(); b = true; });
        REQUIRE(i == 0);
        REQUIRE(c == 0);
        REQUIRE(f == 0);
        REQUIRE(b == false);
        worker.reset();
        REQUIRE(i == 1);
        REQUIRE(c == 1);
        REQUIRE(f == 1);
        REQUIRE(b == true);
    }

} // namespace Tests
} // namespace Dynamic_Static
