
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
#include "Dynamic_Static/Core/Algorithm.hpp"

namespace Dynamic_Static
{
    ThreadPool::ThreadPool(size_t workerCount)
    {
        size_t maxWorkerCount = std::thread::hardware_concurrency();
        workerCount = workerCount ? workerCount : maxWorkerCount;
        workerCount = dst::clamp(workerCount, 1_zu, maxWorkerCount);
        mWorkers = std::vector<Worker>(workerCount);
    }

    ThreadPool::~ThreadPool()
    {
        wait();
    }

    size_t ThreadPool::worker_count() const
    {
        return mWorkers.size();
    }

    size_t ThreadPool::task_count() const
    {
        size_t taskCount = 0;
        for (const auto& worker : mWorkers) {
            taskCount += worker.task_count();
        }

        return taskCount;
    }

    void ThreadPool::push(Worker::Task task)
    {
        mWorkers[mIndex++].push(task);
        if (mIndex >= mWorkers.size()) {
            mIndex = 0;
        }
    }

    void ThreadPool::wait()
    {
        // TODO : Optional timeOut.
        for (auto& worker : mWorkers) {
            worker.wait();
        }
    }
} // namespace Dynamic_Static
