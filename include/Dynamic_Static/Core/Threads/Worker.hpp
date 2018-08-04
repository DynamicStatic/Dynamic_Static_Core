
/*
==========================================
  Copyright (c) 2015-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Threads/ThreadUtilities.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/Time.hpp"

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>

namespace Dynamic_Static {

    /*
    * Provides high level control over queueing tasks for a persistent std::thread.
    */
    class Worker final
        : NonCopyable
    {
    public:
        /*
        * Represents a Task for a Worker to process on a child thread.
        */
        using Task = std::function<void()>;

    private:
        std::thread mThread;
        std::mutex mMutex;
        std::condition_variable mTaskReceived;
        std::condition_variable mTasksComplete;
        std::queue<Task> mTasks;
        bool mRunning { false };

    public:
        /*
        * Constructs an instance of Worker.
        */
        inline Worker()
        {
            mThread = std::thread(
                [&]
                {
                    Millisecond<> duration { 0 };
                    auto predicate = [&] { return !mTasks.empty() || !mRunning; };
                    mRunning = true;
                    while (mRunning) {
                        std::unique_lock<std::mutex> lock(mMutex);
                        dst::wait(lock, mTaskReceived, duration, predicate);
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
            while (!mRunning) {
                std::this_thread::yield();
            }
        }

        /*
        * Destroys this instance of Worker.
        */
        inline ~Worker()
        {
            mRunning = false;
            mTaskReceived.notify_all();
            if (mThread.joinable()) {
                mThread.join();
            }
        }

    public:
        /*
        * Gets this Worker's pending Task count
        * \n NOTE : This Workers's Task count may have changed by the time this method returns
        * @return This Worker's Task count
        */
        inline size_t get_task_count() const
        {
            return mTasks.size();
        }

        /*
        * Pushes a Task for this Worker to process on a child thread.
        * @param [in] task The Task to push
        */
        inline void push(Task task)
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mTaskReceived.notify_one();
            mTasks.push(task);
        }

        /*
        * Suspends the calling thread until this Worker has completed all pending tasks.
        * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        * @param [in] timeOut The maximum amount of time to wait (optional = 0)
        * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            auto predicate = [&] { return mTasks.empty(); };
            dst::wait(lock, mTasksComplete, timeOut, predicate);
        }
    };

} // namespace Dynamic_Static
