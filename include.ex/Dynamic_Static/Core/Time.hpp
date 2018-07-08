
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <chrono>
#include <ratio>

namespace Dynamic_Static {

    /*
    * Represents the system wide real time wall clock.
    */
    typedef std::chrono::system_clock SystemClock;

    /*
    * Represents a monotonic clock.
    * \n NOTE : This clock is not related to wall clock time (for example, it can be time since last reboot)
    */
    typedef std::chrono::steady_clock SteadyClock;

    /*
    * Represents the clock with the smallest tick period provided by the implementation.
    */
    typedef std::chrono::high_resolution_clock HighResolutionClock;

    /*
    * Represents a time interval.
    * @param <TickType> This Duration's tick type
    * @param <Period> This Duration's period in terms of a ratio of seconds
    */
    template <typename TickType, typename Period>
    using Duration = std::chrono::duration<TickType, Period>;

    /*
    * Represents an hour time interval.
    * @param <TickType> This hour's tick type (optional = double)
    */
    template <typename TickType = double>
    using Hour = Duration<TickType, std::ratio<3600>>;

    /*
    * Represents a minute time interval.
    * @param <TickType> This minute's tick type (optional = double)
    */
    template <typename TickType = double>
    using Minute = Duration<TickType, std::ratio<60>>;

    /*
    * Represents a second time interval.
    * @param <TickType> This second's tick type (optional = double)
    */
    template <typename TickType = double>
    using Second = Duration<TickType, std::ratio<1>>;

    /*
    * Represents a millisecond time interval.
    * @param <TickType> This millisecond's tick type (optional = double)
    */
    template <typename TickType = double>
    using Millisecond = Duration<TickType, std::milli>;

    /*
    * Represents a microsecond time interval.
    * @param <TickType> This microsecond's tick type (optional = double)
    */
    template <typename TickType = double>
    using Microsecond = Duration<TickType, std::micro>;

    /*
    * Represents a nanosecond time interval.
    * @param <TickType> This Nanosecond's tick type (optional = double)
    */
    template <typename TickType = double>
    using Nanosecond = Duration<TickType, std::nano>;

    /*
    * Converts a given Duration from one type to another.
    * @param <ToType> The Duration type to convert to
    * @param <FromType> The Duration type to convert from
    * @param [in] duration The Duration to convert
    * @return The converted Duration
    */
    template <typename ToType, typename FromType>
    constexpr ToType duration_cast(const FromType& duration)
    {
        return std::chrono::duration_cast<ToType>(duration);
    }

    /*
    * Represents a point in time.
    * @param <ClockType> This TimePoint's clock type (optional = HighResolutionClock)
    * @param <DurationType> This TimePoint's Duration type (optional = Nanosecond<>)
    */
    template <typename ClockType = HighResolutionClock, typename DurationType = Nanosecond<>>
    using TimePoint = std::chrono::time_point<HighResolutionClock, DurationType>;

    /*
    * Encapsulates a running time keeper.
    */
    class Timer final
    {
    private:
        TimePoint<> mBegin { HighResolutionClock::now() };

    public:
        /*
        * Gets this Timer's total run time.
        * @param <DurationType> The type of Duration to use
        * @return This Timer's total run time
        */
        template <typename DurationType>
        auto total() const
        {
            return duration_cast<DurationType>(HighResolutionClock::now() - mBegin).count();
        }

        /*
        * Resets this Timer.
        */
        void reset()
        {
            mBegin = HighResolutionClock::now();
        }
    };

    /*
    * Encapsulates a periodic time keeper.
    */
    class Clock final
    {
    private:
        TimePoint<> mBegin { HighResolutionClock::now() };
        TimePoint<> mCurrent { mBegin };
        TimePoint<> mPrevious { mBegin };

    public:
        /*
        * Gets this Clock's current TimePoint.
        * @return This Clock's current TimePoint
        */
        const TimePoint<>& current() const
        {
            return mCurrent;
        }

        /*
        * Gets this Clock's total run time.
        * @param <DurationType> The type of Duration to use
        * @return This Clock's total run time
        */
        template <typename DurationType>
        auto total() const
        {
            return duration_cast<DurationType>(mCurrent - mBegin).count();
        }

        /*
        * Gets the amount of time elapsed since this Clock's last update.
        * @param <DurationType> The type of Duration to use
        * @return This Clock's elapsed time
        */
        template <typename DurationType>
        auto elapsed() const
        {
            return duration_cast<DurationType>(mCurrent - mPrevious).count();
        }

        /*
        * Updates this Clock.
        */
        void update()
        {
            mPrevious = mCurrent;
            mCurrent = HighResolutionClock::now();
        }

        /*
        * Resets this Clock.
        */
        void reset()
        {
            mBegin = HighResolutionClock::now();
            mCurrent = mBegin;
            mPrevious = mBegin;
        }
    };

} // namespace Dynamic_Static
