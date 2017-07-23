
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

    size_t Semaphore::value() const
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
