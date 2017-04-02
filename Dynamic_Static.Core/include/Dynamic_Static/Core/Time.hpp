
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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <chrono>

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    typedef std::chrono::system_clock SystemClock;

    /**
     * TODO : Documentation.
     */
    typedef std::chrono::steady_clock SteadyClock;

    /**
     * TODO : Documentation.
     */
    typedef std::chrono::high_resolution_clock HighResolutionClock;

    /**
     * TODO : Documentation.
     */
    template <typename ...Args>
    using Duration = std::chrono::duration<Args...>;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double, std::ratio<3600>> Hour;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double, std::ratio<60>> Minute;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double> Second;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double, std::milli> Millisecond;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double, std::micro> Microsecond;

    /**
     * TODO : Documentation.
     */
    typedef Duration<double, std::nano> Nanosecond;

    /**
     * TODO : Documentation.
     */
    template <typename DurationType>
    using TimePoint = std::chrono::time_point<HighResolutionClock, DurationType>;

    /**
     * TODO : Documentation.
     */
    template <typename ToType, typename FromType>
    constexpr ToType duration_cast(const FromType& duration)
    {
        return std::chrono::duration_cast<ToType>(duration);
    }
} // namespace Dynamic_Static

namespace Dynamic_Static {
    namespace Time {
        /**
         * Gets the current system time in nano seconds.
         * \n NOTE : This value may not provide nano second resolution, this is implementation and system specific
         * @return The current system time in nano seconds
         */
        inline TimePoint<Nanosecond> now()
        {
            // TODO : Provide interface for distinction between steady clock and system clock.
            return HighResolutionClock::now();
        }
    } // namespace Time
} // namespace Dynamic_Static

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Timer final {
    private:
        TimePoint<Nanosecond> mBegin { Time::now() };

    public:
        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType total() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(Time::now() - mBegin).count());
        }

        /**
         * TODO : Documentation.
         */
        void reset()
        {
            mBegin = Time::now();
        }
    };
} // namespace Dynamic_Static

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Clock final {
    public:
        /**
         * TODO : Documentation.
         */
        typedef SystemClock System;

        /**
         * TODO : Documentation.
         */
        typedef SteadyClock Steady;

        /**
         * TODO : Documentation.
         */
        typedef HighResolutionClock HighResolution;

    private:
        TimePoint<Nanosecond> mBegin { Time::now() };
        TimePoint<Nanosecond> mCurrent { Time::now() };
        TimePoint<Nanosecond> mPrevious { Time::now() - Nanosecond(1) };

    public:
        /**
         * TODO : Documentation.
         */
        const TimePoint<Nanosecond>& current() const
        {
            return mCurrent;
        }

        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType total() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(mCurrent - mBegin).count());
        }

        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType elapsed() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(mCurrent - mPrevious).count());
        }

        /**
         * TODO : Documentation.
         */
        void update()
        {
            mPrevious = mCurrent;
            mCurrent = Time::now();
        }
    };
} // namespace Dynamic_Static
