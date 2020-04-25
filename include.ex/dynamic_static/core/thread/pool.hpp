
/*
==========================================
  Copyright (c) 2015-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/thread/worker.hpp"
#include "dynamic_static/core/algorithm.hpp"
#include "dynamic_static/core/defines.hpp"

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
        : mWorkers(workerCount ? workerCount : std::thread::hardware_concurrency())
    {
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
        assert(!mWorkers.empty());
        Worker* pWorker = &mWorkers[0];
        for (auto& worker : mWorkers) {
            if (worker.task_count() < pWorker->task_count()) {
                pWorker = &worker;
            }
        }
        assert(pWorker);
        pWorker->push(std::move(task));
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType = Milliseconds<>>
    inline bool wait(const DurationType& timeOut = DurationType { 0 })
    {
        // TODO : This needs to be reworked so that each Worker doesn't have timeout
        // TODO : Workers should expose their task complete std::condition_variable
        bool allTasksFinished = true;
        for (auto& worker : mWorkers) {
            if (!worker.wait(timeOut)) {
                allTasksFinished = false;
                break;
            }
        }
        return allTasksFinished;
    }

private:
    std::vector<Worker> mWorkers;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
};

} // namespace dst
