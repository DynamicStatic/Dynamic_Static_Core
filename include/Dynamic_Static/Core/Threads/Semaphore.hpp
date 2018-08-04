
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
#include <mutex>
#include <thread>

namespace Dynamic_Static {

    /*
    * Provides high level control over signaling and synchronization between threads.
    */
    class Semaphore final
        : NonCopyable
    {
    private:
        std::mutex mMutex;
        std::condition_variable mCondition;
        int mWaitingThreadCount { 0 };
        int mSignalCount { 0 };

    public:
        /*
        * Constructs an instance of Semaphore.
        * @param [in] signalCount This Semaphore's initial signalCount (optional = 0)
        */
        inline Semaphore(int signalCount = 0)
            : mSignalCount { signalCount }
        {
        }

        /*
        * Destroys this instance of Semphore.
        * \n NOTE : This will cause all threads waiting on this Semaphore to resume execution.
        */
        inline ~Semaphore()
        {
            notify_all();
            while (mWaitingThreadCount) {
                std::this_thread::yield();
            }
        }

    public:
        /*
        * Gets this Semaphore's current signal count.
        * \n NOTE : This Semaphore's signal count may have changed by the time this method returns
        * @return This Semaphore's current signal count
        */
        inline int get_signal_count() const
        {
            return mSignalCount;
        }

        /*
        * Notifies a given number of threads waiting on this Semaphore and increments this Semaphore's signal count once for each thread notified.
        * @param [in] count The number of threads to notify (optional = 1)
        */
        inline void notify(int count = 1)
        {
            std::unique_lock<std::mutex> lock(mMutex);
            for (int i = 0; i < count; ++i) {
                mCondition.notify_one();
                ++mSignalCount;
            }
        }

        /*
        * Notifies each thread waiting on this Semaphore and increments this Semaphore's signal count once for each thread notified.
        */
        inline void notify_all()
        {
            notify(mWaitingThreadCount);
        }

        /*
        * Suspends the calling thread if this Semaphore's signal count is zero and decrements this Semaphore's signal count by one.
        * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        * @param [in] timeOut The maximum amount of time to wait (optional = 0)
        * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            ++mWaitingThreadCount;
            auto predicate = [&] { return mSignalCount > 0; };
            if (dst::wait(lock, mCondition, timeOut, predicate)) {
                --mSignalCount;
            }
            --mWaitingThreadCount;
        }
    };

} // namespace Dynamic_Static
