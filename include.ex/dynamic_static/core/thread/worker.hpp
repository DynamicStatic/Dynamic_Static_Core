
/*
==========================================
  Copyright (c) 2015-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#include "dynamic_static/core/time.hpp"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

namespace dst {

/**
TODO : Documentation
*/
class Worker final
{
public:
    /**
    TODO : Documentation
    */
    using Task = std::function<void()>;

    /**
    Constructs an instance of Worker
    */
    inline Worker()
    {
        mThread = std::thread(
            [&]()
            {
                Milliseconds<> duration { 0 };
                auto predicate = [&]() { return !mTasks.empty() || !mActive; };
                while (mActive) {
                    std::unique_lock<std::mutex> lock(mMutex);
                    wait(lock, mTaskReceived, duration, predicate);
                    lock.unlock();
                    while (!mTasks.empty()) {
                        lock.lock();
                        auto& task = mTasks.front();
                        lock.unlock();
                        task();
                        lock.lock();
                        mTasks.pop();
                        lock.unlock();
                    }
                    mTasksComplete.notify_all();
                }
            }
        );
    }

    /**
    Destroys this instance of Worker
    */
    inline ~Worker()
    {
        mActive = false;
        mTaskReceived.notify_all();
        if (mThread.joinable()) {
            mThread.join();
        }
    }

    /**
    TODO : Documentation
    */
    inline size_t task_count() const
    {
        return mTasks.size();
    }

    /**
    TODO : Documentation
    */
    inline void push(Task&& task)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mTasks.push(std::move(task));
        mTaskReceived.notify_one();
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType = Milliseconds<>>
    inline bool wait(const DurationType& timeOut = DurationType { 0 })
    {
        std::unique_lock<std::mutex> lock(mMutex);
        auto predicate = [&]() { return mTasks.empty(); };
        return wait(lock, mTasksComplete, timeOut, predicate);
    }

private:
    template <typename DurationType, typename PredicateType>
    inline bool wait(
        std::unique_lock<std::mutex>& lock,
        std::condition_variable& condition,
        const DurationType& timeOut,
        PredicateType predicate
    )
    {
        bool predicateEvaluatedTrue = true;
        if (timeOut.count()) {
            predicateEvaluatedTrue = condition.wait_for(lock, timeOut, predicate);
        } else {
            condition.wait(lock, predicate);
        }
        return predicateEvaluatedTrue;
    }

    std::mutex mMutex;
    std::thread mThread;
    std::condition_variable mTaskReceived;
    std::condition_variable mTasksComplete;
    std::queue<Task> mTasks;
    std::atomic<bool> mActive { true };
};

} // namespace dst
