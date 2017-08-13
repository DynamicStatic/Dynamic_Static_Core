
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Threads/Worker.hpp"

namespace Dynamic_Static {

    Worker::Worker()
    {
        mThread = std::thread(
            [&]()
            {
                Millisecond<> duration { 0 };
                auto predicate = [&]() { return !mTasks.empty() || !mRunning; };
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

    Worker::~Worker()
    {
        mRunning = false;
        mTaskReceived.notify_all();
        if (mThread.joinable()) {
            mThread.join();
        }
    }

    size_t Worker::task_count() const
    {
        return mTasks.size();
    }

    void Worker::push(Task task)
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mTaskReceived.notify_one();
        mTasks.push(task);
    }

} // namespace Dynamic_Static
