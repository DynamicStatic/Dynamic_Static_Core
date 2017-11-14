
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/NonMoveable.hpp"
#include "Dynamic_Static/Core/Time.hpp"
#include "Dynamic_Static/Core/Threads/ThreadUtilities.hpp"

#include <condition_variable>
#include <mutex>

namespace Dynamic_Static {

    /**
     * Provides signaling and synchronization between threads.
     */
    class Semaphore final
        : NonCopyable
        , NonMoveable
    {
    private:
        std::mutex mMutex;
        std::condition_variable mCondition;
        size_t mWaiting { 0 };
        size_t mValue { 0 };

    public:
        /**
         * Constructs an instance of Semaphore.
         * @param [in] value This Semaphore's initial value (optional = 0)
         */
        Semaphore(size_t value = 0);

        /**
         * Destroys this instance of Semphore.
         * \n NOTE : This will cause all threads waiting on this Semaphore to resume execution.
         */
        ~Semaphore();

    public:
        /**
         * Gets this Semaphore's current value.
         * \n NOTE : This Semaphore's value may have changed by the time this method returns
         * @return This Semaphore's current value
         */
        size_t value() const;

        /**
         * Notifies on thread wiating on this Semaphore and increments this Semaphore's value by one.
         * @param [in] count The number of threads to notify (optional = 1)
         */
        void notify(size_t count = 1);

        /**
         * Notifies and increments once for each thread waiting on this Semaphore.
         */
        void notify_all();

        /**
         * Suspends the calling thread if this Semaphore's value is zero and decrements this Semaphore's value by one.
         * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
         * @param [in] timeOut The maximum amount of time to wait (optional = 0)
         * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
         */
        template <typename DurationType = Millisecond<>>
        void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            ++mWaiting;
            auto predicate = [&]() { return mValue > 0; };
            if (dst::wait(lock, mCondition, timeOut, predicate)) {
                --mValue;
            }

            --mWaiting;
        }
    };

} // namespace Dynamic_Static
