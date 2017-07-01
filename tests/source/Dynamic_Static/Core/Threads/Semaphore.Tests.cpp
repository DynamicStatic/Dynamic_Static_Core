
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

#include "Dynamic_Static/Core/Threads/Semaphore.hpp"
#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/Core/Action.hpp"

#include "catch.hpp"

#include <thread>
#include <atomic>

#include <iostream>

namespace Dynamic_Static
{
    namespace Tests
    {
        static constexpr size_t ThreadCount { 16 };
        static constexpr size_t NotifyCount { ThreadCount / 4 };
        static constexpr size_t WaitTarget { 5 };
        static constexpr size_t CounterTarget { 10 };

        template <typename ActionType>
        std::vector<std::thread> create_threads(size_t count, ActionType action)
        {
            std::vector<std::thread> threads;
            for (size_t i = 0; i < count; ++i) {
                threads.push_back(std::thread(action));
            }

            return threads;
        }

        void join_threads(std::vector<std::thread>& threads)
        {
            for (auto& thread : threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
        }

        TEST_CASE("Semaphore ctor() and dtor()", "[Threads.Semaphore]")
        {
            REQUIRE_NOTHROW(Semaphore());
        }

        TEST_CASE("Semaphore can wait() and notify() a single thread", "[Threads.Semaphore]")
        {
            Semaphore semaphore;
            std::atomic<size_t> counter = 0;
            auto thread = create_threads(
                1,
                [&]()
                {
                    while (++counter < CounterTarget) {
                        if (counter == WaitTarget) {
                            semaphore.wait();
                        }
                    }
                }
            );

            std::this_thread::sleep_for(Second<>(0.1));
            REQUIRE(counter == WaitTarget);
            semaphore.notify();

            std::this_thread::sleep_for(Second<>(0.1));
            REQUIRE(counter == CounterTarget);
            join_threads(thread);
        }

        TEST_CASE("Semaphore can wait() and notify() multiple threads", "[Threads.Semaphore]")
        {
            Semaphore semaphore;
            std::atomic<size_t> counter = 0;
            auto threads = create_threads(
                ThreadCount,
                [&]()
                {
                    semaphore.wait();
                    ++counter;
                }
            );

            float sleepTime = 1.0f / threads.size();
            for (size_t i = 0; i < threads.size(); ++i) {
                std::this_thread::sleep_for(Millisecond<>(sleepTime));
                REQUIRE(counter == i);
                semaphore.notify();
            }

            join_threads(threads);
        }

        TEST_CASE("Semaphore can time out wait()", "[Threads.Semaphore]")
        {
            Semaphore semaphore;
            std::atomic<size_t> counter = 0;
            auto threads = create_threads(
                ThreadCount,
                [&]()
                {
                    semaphore.wait(Millisecond<>(16));
                    ++counter;
                }
            );

            join_threads(threads);
            REQUIRE(counter == threads.size());
        }

        TEST_CASE("Semaphore can notify_all()", "[Threads.Semaphore]")
        {
            Semaphore semaphore;
            std::atomic<size_t> counter = 0;
            auto threads = create_threads(
                ThreadCount,
                [&]()
                {
                    semaphore.wait();
                    ++counter;
                }
            );

            std::this_thread::sleep_for(Millisecond<>(0.1f));
            REQUIRE(counter == 0);
            semaphore.notify_all();
            join_threads(threads);
            REQUIRE(counter == threads.size());
        }

        TEST_CASE("Semaphore can pass through wait() on positive value() then notify_all()", "[Threads.Semaphore]")
        {
            Semaphore semaphore(NotifyCount);
            REQUIRE(semaphore.value() == NotifyCount);
            semaphore.notify(NotifyCount);
            REQUIRE(semaphore.value() == NotifyCount * 2);
            size_t value = semaphore.value();

            std::atomic<size_t> counter = 0;
            auto threads = create_threads(
                ThreadCount,
                [&]()
                {
                    semaphore.wait();
                    ++counter;
                }
            );

            std::this_thread::sleep_for(Millisecond<>(0.1f));
            REQUIRE(semaphore.value() == 0);
            REQUIRE(counter == value);
            semaphore.notify_all();
            join_threads(threads);
            REQUIRE(counter == threads.size());
        }

        TEST_CASE("Notify waiting threads when Semaphore is destroyed", "[Threads.Semaphore]")
        {
            auto semaphore = std::make_unique<Semaphore>();
            std::atomic<size_t> counter = 0;
            auto threads = create_threads(
                ThreadCount,
                [&]()
                {
                    semaphore->wait();
                    ++counter;
                }
            );

            std::this_thread::sleep_for(Millisecond<>(0.1f));
            REQUIRE(counter == 0);
            semaphore.reset();
            join_threads(threads);
            REQUIRE(counter == threads.size());
        }
    } // namespace Tests
} // namespace Dynamic_Static
