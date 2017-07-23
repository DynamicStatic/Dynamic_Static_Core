
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
