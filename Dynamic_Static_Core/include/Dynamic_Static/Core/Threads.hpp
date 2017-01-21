
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

#pragma once

#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <queue>
#include <mutex>
#include <memory>
#include <vector>
#include <thread>
#include <functional>
#include <condition_variable>

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Semaphore final
        : NonCopyable {
    private:
        typedef std::condition_variable Condition;
        std::unique_ptr<Condition> mCondition { std::make_unique<Condition>() };
        std::unique_ptr<std::mutex> mMutex { std::make_unique<std::mutex>() };
        size_t mCount { 0 };

    public:
        /**
         * Constructs an instance of Semaphore with an optional starting count.
         * @param [in] count The count to construct this Semaphore with
         */
        Semaphore(size_t count = 0);

    public:
        /**
         * Notifies this Semaphore.
         */
        void notify();

        /**
         * Blocks the calling thread until this Semaphore is notified at least once for each call to wait().
         */
        void wait();

        /**
         * Blocks the calling thread until this Semaphore is notified at least once for each call to wait() or a specified time out is reached.
         * @param <DurationType> The type of the Duration to use for the time out
         * @param [in] time_out  The amount of time to wait before releasing this Semaphore
         */
        template <typename DurationType = Millisecond>
        void wait_for(const DurationType& timeOut)
        {
            std::unique_lock<std::mutex> lock(*mMutex);
            mCondition->wait_for(lock, timeOut, [&]() { return mCount > 0; });
            --mCount;
        }
    };
}

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Worker final
        : NonCopyable {
    public:
        /**
         * Alias for an std::function with no parameters and no return value.
         */
        typedef std::function<void()> Task;

    private:
        std::thread mThread;
        Semaphore mSemaphore;
        std::unique_ptr<std::mutex> mMutex { std::make_unique<std::mutex>() };
        std::queue<Task> mTasks;
        bool mRunning { false };

    public:
        /**
         * Constructs an instance of Worker.
         */
        Worker();

        /**
         * Destroys this Worker.
         */
        ~Worker();

    public:
        /**
         * Gets the number of Tasks waiting for processing by this Worker.
         * \n NOTE : This method may return inaccurate values
         * @return The number of Tasks waiting for processing by this Worker
         */
        size_t task_count() const;

        /**
         * Blocks the calling thread until this Worker has no Tasks to process.
         */
        void join() const;

        /**
         * Pushes a Task to this Worker for processing.
         * @param [in] task The Task to push to this Worker for processing
         */
        void push(const Task& task);
    };
}

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class ThreadPool final
        : NonCopyable {
    private:
        std::vector<Worker> mWorkers;
        size_t mWorkerIndex { 0 };

    public:
        /**
         * Constructs an instance of ThreadPool with an optional worker count.
         * \n NOTE : If worker_count is 0 it will be set to the number of cores reported by the operating system.
         */
        ThreadPool(size_t workerCount = 0);

        /**
         * Destroys this instance of ThreadPool.
         */
        ~ThreadPool();

    public:
        /**
         * Gets the number of Workers used by this ThreadPool.
         * @return The number of Workers used by this ThreadPool
         */
        size_t worker_count() const;

        /**
         * Gets the number of Worker::Tasks waiting for processing by this ThreadPool.
         * \n NOTE : This method may return inaccurate values
         * @return The number of Worker::Tasks waiting for processing by this ThreadPool
         */
        size_t task_count() const;

        /**
         * Blocks the calling thread until this ThreadPool has no Worker::Tasks to process.
         */
        void join() const;

        /**
         * Pushes a Worker::Task to this ThreadPool for processing.
         * @param [in] task The Worker::Task to push to this ThreadPool for processing
         */
        void push(Worker::Task task);
    };
}
