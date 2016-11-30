
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#include "Dynamic_Static/Core/Threads.hpp"

#include <algorithm>

namespace Dynamic_Static {
    Semaphore::Semaphore(size_t count)
        : m_count { count }
    {
    }

    void Semaphore::wait()
    {
        std::unique_lock<std::mutex> lock(*m_mutex);
        m_condition->wait(lock, [&] { return m_count > 0; });
        --m_count;
    }

    void Semaphore::notify()
    {
        std::unique_lock<std::mutex> lock(*m_mutex);
        m_condition->notify_one();
        ++m_count;
    }
}

namespace Dynamic_Static {
    Worker::Worker()
    {
        m_thread = std::thread(
            [&]()
            {
                m_running = true;
                while (m_running) {
                    m_semaphore.wait();
                    while (!m_tasks.empty()) {
                        m_mutex->lock();
                        Task& task = m_tasks.front();
                        m_mutex->unlock();
                        task();
                        m_mutex->lock();
                        m_tasks.pop();
                        m_mutex->unlock();
                    }
                }
            }
        );

        while (!m_running) {
            std::this_thread::yield();
        }
    }

    Worker::~Worker()
    {
        m_running = false;
        m_semaphore.notify();
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

    size_t Worker::task_count() const
    {
        return m_tasks.size();
    }

    void Worker::join() const
    {
        while (m_tasks.size()) {
            std::this_thread::yield();
        }
    }

    void Worker::push(const Task& task)
    {
        std::lock_guard<std::mutex> lock(*m_mutex);
        m_tasks.push(task);
        m_semaphore.notify();
    }
}

namespace Dynamic_Static {
    ThreadPool::ThreadPool(size_t worker_count)
    {
        size_t max_worker_count = std::thread::hardware_concurrency();
        worker_count = worker_count ? worker_count : max_worker_count;
        worker_count = std::min(std::max(size_t { 1 }, worker_count), max_worker_count);
        m_workers = std::vector<Worker>(worker_count);
    }

    ThreadPool::~ThreadPool()
    {
        join();
    }

    size_t ThreadPool::worker_count() const
    {
        return m_workers.size();
    }

    size_t ThreadPool::task_count() const
    {
        size_t task_count = 0;
        for (const auto& worker : m_workers) {
            task_count += worker.task_count();
        }

        return task_count;
    }

    void ThreadPool::join() const
    {
        for (const auto& worker : m_workers) {
            worker.join();
        }
    }

    void ThreadPool::push(Worker::Task task)
    {
        m_workers[m_worker_index++].push(task);
        if (m_worker_index >= m_workers.size()) {
            m_worker_index = 0;
        }
    }
}
