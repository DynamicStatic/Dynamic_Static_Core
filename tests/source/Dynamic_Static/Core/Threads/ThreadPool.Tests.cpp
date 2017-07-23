
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

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
