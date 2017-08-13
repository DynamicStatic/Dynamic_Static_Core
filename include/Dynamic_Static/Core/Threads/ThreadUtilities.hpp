
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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
