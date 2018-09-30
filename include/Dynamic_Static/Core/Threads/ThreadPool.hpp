
/*
==========================================
  Copyright (c) 2015-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Threads/Worker.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <algorithm>
#include <vector>

namespace dst {

    /*!
    Provides high level control over a pool of Workers.
    */
    class ThreadPool final
        : NonCopyable
    {
    private:
        std::vector<Worker> mWorkers;
        size_t mIndex { 0 };

    public:
        /*!
        Constructs an instance of ThreadPool.
        @param [in] workerCount This ThreadPool's worker count (optional = 0)
        \n NOTE : A value of 0 for workerCount results in using the value returned from std::thread::hardware_concurrency()
        */
        inline ThreadPool(size_t workerCount = 0)
        {
            size_t maxWorkerCount = std::thread::hardware_concurrency();
            workerCount = workerCount ? workerCount : maxWorkerCount;
            workerCount = std::clamp(workerCount, size_t { 1 }, maxWorkerCount);
            mWorkers = std::vector<Worker>(workerCount);
        }

        /*!
        Destroys this instance of ThreadPool.
        */
        inline ~ThreadPool()
        {
            wait();
        }

    public:
        /*!
        Gets this ThreadPool' Worker count.
        @return This ThreadPool's Worker count
        */
        inline size_t get_worker_count() const
        {
            return mWorkers.size();
        }

        /*!
        Gets this ThreadPool's pending Worker::Task count.
        \n NOTE : This ThreadPool's pending Worker::Task count may have changed by the time this method returns
        */
        inline size_t get_task_count() const
        {
            size_t taskCount = 0;
            for (const auto& worker : mWorkers) {
                taskCount += worker.get_task_count();
            }
            return taskCount;
        }

        /*!
        Pushes a Worker::Task for this ThreadPool to process on a child thread.
        */
        inline void push(Worker::Task task)
        {
            mWorkers[mIndex++].push(task);
            if (mIndex >= mWorkers.size()) {
                mIndex = 0;
            }
        }

        /*!
        Suspends the calling thread until this ThreadPool has completed all pending tasks.
        @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        @param [in] timeOut The maximum amount of time to wait (optional = 0)
        \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            for (auto& worker : mWorkers) {
                worker.wait(timeOut);
            }
        }
    };

} // namespace dst
