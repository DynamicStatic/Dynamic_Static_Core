
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#include "catch.hpp"

#include "Dynamic_Static/Core/Threads.hpp"

namespace Dynamic_Static {
    namespace Tests {
        static const size_t WaitTarget { 5 };
        static const size_t CounterTarget { 10 };

        TEST_CASE("Semaphore can wait() and notify", "[Threads]")
        {
            size_t counter = 0;
            Semaphore semaphore;
            auto thread = std::thread(
                [&]()
                {
                    while (++counter < CounterTarget) {
                        if (counter == WaitTarget) {
                            semaphore.wait();
                        }
                    }
                }
            );

            // NOTE : This assumes that 500ms sleep is long enough for the
            //        other thread to get to the semaphore.wait() call.
            std::this_thread::sleep_for(Millisecond(500));
            REQUIRE(counter == WaitTarget);
            semaphore.notify();

            // NOTE : This assumes that 500ms sleep is long enough
            //        for the other thread to finish counting.
            std::this_thread::sleep_for(Millisecond(500));
            REQUIRE(counter == CounterTarget);
            thread.join();
        }

        TEST_CASE("Semaphore can release on wait_for()", "[Threads]")
        {
            size_t counter = 0;
            Semaphore semaphore;
            auto thread = std::thread(
                [&]()
                {
                    while (++counter < CounterTarget) {
                        if (counter == WaitTarget) {
                            semaphore.wait_for(Second(0.25f));
                        }
                    }
                }
            );

            while (counter < CounterTarget) {
                std::this_thread::yield();
            }

            REQUIRE(counter == CounterTarget);
            thread.join();
        }

        TEST_CASE("Semaphore can release before wait_for()", "[Threads]")
        {
            size_t counter = 0;
            Semaphore semaphore;
            auto thread = std::thread(
                [&]()
                {
                    while (++counter < CounterTarget) {
                        if (counter == WaitTarget) {
                            semaphore.wait_for(Second(30));
                        }
                    }
                }
            );

            Timer timer;
            std::this_thread::sleep_for(Millisecond(500));
            REQUIRE(counter == WaitTarget);
            semaphore.notify();
            std::this_thread::sleep_for(Second(0.1f));
            REQUIRE(timer.total<Second>() < 30);
            REQUIRE(counter == CounterTarget);
            thread.join();
        }

        TEST_CASE("Worker can push() and join()", "[Threads]")
        {
            size_t counter = 0;
            Worker worker;
            worker.push([&]() { while (++counter < CounterTarget); });
            worker.join();
            REQUIRE(counter == CounterTarget);
        }
    } // namespace Tests
} // namespace Dynamic_Static
