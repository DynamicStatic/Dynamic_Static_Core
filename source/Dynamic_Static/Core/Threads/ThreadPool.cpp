
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/ThreadPool.hpp"
#include "Dynamic_Static/Core/Algorithm.hpp"

namespace Dynamic_Static {

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
