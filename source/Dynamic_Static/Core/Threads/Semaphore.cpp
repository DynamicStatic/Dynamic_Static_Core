
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/Semaphore.hpp"

#include <thread>

namespace Dynamic_Static {

    Semaphore::Semaphore(size_t count)
        : mValue { count }
    {
    }

    Semaphore::~Semaphore()
    {
        notify_all();
        while (mWaiting) {
            std::this_thread::yield();
        }
    }

    size_t Semaphore::get_value() const
    {
        return mValue;
    }

    void Semaphore::notify(size_t count)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        for (size_t i = 0; i < count; ++i) {
            mCondition.notify_one();
            ++mValue;
        }
    }

    void Semaphore::notify_all()
    {
        notify(mWaiting);
    }

} // namespace Dynamic_Static
