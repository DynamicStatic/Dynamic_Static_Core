
/*
==========================================
  Copyright (c) 2015-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/threads/worker.hpp"
#include "dynamic_static/core/algorithm.hpp"
#include "dynamic_static/core/defines.hpp"

#include <algorithm>
#include <thread>
#include <utility>
#include <vector>

namespace dst {

/**
TODO : Documentation
*/
class ThreadPool final
{
public:
    /**
    Constructs an instance of ThreadPool
    TODO : Documentation
    */
    inline ThreadPool(size_t workerCount = 0)
    {
        size_t maxWorkerCount = std::thread::hardware_concurrency();
        workerCount = workerCount ? workerCount : maxWorkerCount;
        workerCount = clamp(workerCount, size_t(1), maxWorkerCount);
        mWorkers = std::vector<Worker>(workerCount);
    }

    /**
    Destroys this instance of ThreadPool
    */
    inline ~ThreadPool()
    {
        wait();
    }

    /**
    TODO : Documentation
    */
    inline size_t worker_count() const
    {
        return mWorkers.size();
    }

    /**
    TODO : Documentation
    */
    inline size_t task_count() const
    {
        size_t taskCount = 0;
        for (const auto& worker : mWorkers) {
            taskCount += worker.task_count();
        }
        return taskCount;
    }

    /**
    TODO : Documentation
    */
    inline void push(Worker::Task&& task)
    {
        Worker* pWorker = &mWorkers[0];
        for (auto& worker : mWorkers) {
            if (worker.task_count() < pWorker->task_count()) {
                pWorker = &worker;
            }
        }
        pWorker->push(std::move(task));
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType = Milliseconds<>>
    inline void wait(const DurationType& timeOut = DurationType { 0 })
    {
        for (auto& worker : mWorkers) {
            worker.wait(timeOut);
        }
    }

private:
    std::vector<Worker> mWorkers;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};

} // namespace dst
