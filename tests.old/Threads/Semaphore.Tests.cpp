
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/Semaphore.hpp"
#include "Dynamic_Static/Core/Time.hpp"

#include "catch.hpp"

#include <atomic>
#include <thread>

namespace dst {
namespace tests {

    static constexpr size_t ThreadCount { 16 };
    static constexpr size_t NotifyCount { ThreadCount / 4 };
    static constexpr size_t WaitTarget { 5 };
    static constexpr size_t CounterTarget { 10 };

    template <typename FunctionType>
    std::vector<std::thread> create_threads(size_t count, FunctionType function)
    {
        std::vector<std::thread> threads;
        for (size_t i = 0; i < count; ++i) {
            threads.push_back(std::thread(function));
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

    TEST_CASE("Semaphore can wait() and notify() a single thread", "[Semaphore]")
    {
        Semaphore semaphore;
        std::atomic<size_t> counter { 0 };
        auto thread = create_threads(
            1,
            [&]
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

    TEST_CASE("Semaphore can wait() and notify() multiple threads", "[Semaphore]")
    {
        Semaphore semaphore;
        std::atomic<size_t> counter { 0 };
        auto threads = create_threads(
            ThreadCount,
            [&]
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

    TEST_CASE("Semaphore can time out wait()", "[Semaphore]")
    {
        Semaphore semaphore;
        std::atomic<size_t> counter { 0 };
        auto threads = create_threads(
            ThreadCount,
            [&]
            {
                semaphore.wait(Millisecond<>(16));
                ++counter;
            }
        );

        join_threads(threads);
        REQUIRE(counter == threads.size());
    }

    TEST_CASE("notify_all()", "[Semaphore]")
    {
        Semaphore semaphore;
        std::atomic<size_t> counter { 0 };
        auto threads = create_threads(
            ThreadCount,
            [&]
            {
                semaphore.wait();
                ++counter;
            }
        );

        std::this_thread::sleep_for(Millisecond<>(.1f));
        REQUIRE(counter == 0);
        semaphore.notify_all();
        join_threads(threads);
        REQUIRE(counter == threads.size());
    }

    TEST_CASE("Semaphore can pass through wait() on positive value(), then notify_all()", "[Semaphore]")
    {
        Semaphore semaphore(NotifyCount);
        REQUIRE(semaphore.get_signal_count() == NotifyCount);
        semaphore.notify(NotifyCount);
        REQUIRE(semaphore.get_signal_count() == NotifyCount * 2);
        size_t value = semaphore.get_signal_count();

        std::atomic<size_t> counter { 0 };
        auto threads = create_threads(
            ThreadCount,
            [&]
            {
                semaphore.wait();
                ++counter;
            }
        );

        std::this_thread::sleep_for(Millisecond<>(.1f));
        REQUIRE(semaphore.get_signal_count() == 0);
        REQUIRE(counter == value);
        semaphore.notify_all();
        join_threads(threads);
        REQUIRE(counter == threads.size());
    }

    TEST_CASE("Notify waiting threads when Semaphore is destroyed", "[Semaphore]")
    {
        auto semaphore = std::make_unique<Semaphore>();
        std::atomic<size_t> counter { 0 };
        auto threads = create_threads(
            ThreadCount,
            [&]
            {
                semaphore->wait();
                ++counter;
            }
        );

        std::this_thread::sleep_for(Millisecond<>(.1f));
        REQUIRE(counter == 0);
        semaphore.reset();
        join_threads(threads);
        REQUIRE(counter == threads.size());
    }

} // namespace tests
} // namespace dst
