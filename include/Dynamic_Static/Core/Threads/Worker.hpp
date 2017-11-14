
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Action.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/NonMoveable.hpp"
#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/Core/Threads/ThreadUtilities.hpp"

#include <condition_variable>
#include <queue>
#include <thread>

namespace Dynamic_Static {

    /**
     * Represents a persistent std::thread.
     */
    class Worker final
        : NonCopyable
        , NonMoveable
    {
    public:
        /**
         * Represents a Task for this Worker to process on a child thread.
         */
        typedef Action<> Task;

    private:
        std::thread mThread;
        std::mutex mMutex;
        std::condition_variable mTaskReceived;
        std::condition_variable mTasksComplete;
        std::queue<Worker::Task> mTasks;
        bool mRunning = false;

    public:
        /**
         * Constructs an instance of Worker.
         */

        Worker();

        /**
         * Destroys this instance of Worker.
         */
        ~Worker();

    public:
        /**
         * Gets this Worker's pending Task count
         * \n NOTE : This Workers's Task count may have changed by the time this method returns
         */
        size_t task_count() const;

        /**
         * Pushes a Task for this Worker to process on a child thread.
         */
        void push(Task task);

        /**
         * Suspends the calling thread until this Worker has completed all pending tasks.
         * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
         * @param [in] timeOut The maximum amount of time to wait (optional = 0)
         * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
         */
        template <typename DurationType = Millisecond<>>
        void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            auto predicate = [&]() { return mTasks.empty(); };
            dst::wait(lock, mTasksComplete, timeOut, predicate);
        }
    };

} // namespace Dynamic_Static
