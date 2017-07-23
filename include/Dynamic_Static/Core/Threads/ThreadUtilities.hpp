
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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <condition_variable>
#include <mutex>

namespace Dynamic_Static {

    /**
     * Suspends the calling thread until a given std::condition variable is notified or a time out is reached.
     * @param <PredicateType> The type of the predicate
     * @param [in] lock       A locked std::unique_lock<std::mutex> that will be unlocked on wait and relocked on resume
     * @param [in] condition  The std::condition_variable to wait on
     * @param [in] predicate  The predicate to test before waiting and on spurious or notified resumes
     * @return Whether or not the predicate passed after a time out
     */
    template <typename DurationType, typename PredicateType>
    inline bool wait(
        std::unique_lock<std::mutex>& lock,
        std::condition_variable& condition,
        const DurationType& timeOut,
        PredicateType predicate
    )
    {
        bool predicatePassed = true;
        if (timeOut.count()) {
            predicatePassed = condition.wait_for(lock, timeOut, predicate);
        } else {
            condition.wait(lock, predicate);
        }

        return predicatePassed;
    }

} // Dynamic_Static
