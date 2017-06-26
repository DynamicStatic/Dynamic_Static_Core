
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#include "Dynamic_Static/Core/Threads/Worker.hpp"

namespace Dynamic_Static
{
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
