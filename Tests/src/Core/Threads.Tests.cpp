
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
        static const size_t g_wait_target { 5 };
        static const size_t g_counter_target { 10 };

        TEST_CASE("Semaphore can wait and notify", "[Threads]")
        {
            size_t counter = 0;
            Semaphore semaphore;
            auto thread = std::thread(
                [&]()
                {
                    while (++counter < g_counter_target) {
                        if (counter == g_wait_target) {
                            semaphore.wait();
                        }
                    }
                }
            );

            // NOTE : This assumes that 500ms sleep is long enough for
            //        the other thread to get to the semaphore().wait() call.
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            REQUIRE(counter == g_wait_target);
            semaphore.notify();

            // NOTE : This assumes that 500ms sleep is long enough for
            //        the other thread to finish counting.
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            REQUIRE(counter == g_counter_target);
            thread.join();
        }

        TEST_CASE("Worker can process task and join", "[Threads]")
        {
            size_t counter = 0;
            Worker worker;
            worker.push(
                [&]()
                {
                    while (++counter < g_counter_target);
                }
            );
            
            worker.join();
            REQUIRE(counter == g_counter_target);
        }
    }
}
