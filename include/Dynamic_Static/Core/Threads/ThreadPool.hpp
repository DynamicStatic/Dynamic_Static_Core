
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Threads/Worker.hpp"

#include <vector>

namespace Dynamic_Static {

    /**
     * Represents a pool of one or more Workers.
     */
    class ThreadPool final
        : NonCopyable
        , NonMoveable
    {
    private:
        std::vector<Worker> mWorkers;
        size_t mIndex { 0 };

    public:
        /**
         * Constructs an instance of ThreadPool.
         * @param [in] workerCount This ThreadPool's worker count (optional = 0)
         * \n NOTE : A value of 0 for workerCount results in using the value returned from std::thread::hardware_concurrency()
         */
        ThreadPool(size_t workerCount = 0);

        /**
         * Destroys this instance of ThreadPool.
         */
        ~ThreadPool();

    public:
        size_t worker_count() const;

        /**
         * Gets this ThreadPool's pending Worker::Task count.
         * \n NOTE : This ThreadPool's Worker::Task count may have changed by the time this method returns
         */
        size_t task_count() const;

        /**
         * Pushes a Task for this ThreadPool to process on a child thread.
         */
        void push(Worker::Task task);

        /**
         * Suspends the calling thread until this ThreadPool has completed all pending tasks.
         */
        void wait();
    };

} // namespace Dynamic_Static
