
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <chrono>
#include <ctime>
#include <ratio>

namespace dst {

/**
TODO : Documentation
*/
using SystemClock = std::chrono::system_clock;

/**
TODO : Documentation
*/
using SteadyClock = std::chrono::steady_clock;

/**
TODO : Documentation
*/
using HighResolutionClock = std::chrono::high_resolution_clock;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Hours = std::chrono::duration<Rep, std::ratio<3600>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Minutes = std::chrono::duration<Rep, std::ratio<60>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Seconds = std::chrono::duration<Rep, std::ratio<1>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Milliseconds = std::chrono::duration<Rep, std::milli>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using microseconds = std::chrono::duration<Rep, std::micro>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using nanoseconds = std::chrono::duration<Rep, std::nano>;

/**
TODO : Documentation
*/
template <typename ClockType = HighResolutionClock, typename DurationType = nanoseconds<>>
using TimePoint = std::chrono::time_point<ClockType, DurationType>;

/**
TODO : Documentation
*/
template <typename ToDurationType, typename FromDurationType>
inline constexpr ToDurationType duration_cast(const FromDurationType& duration)
{
    return std::chrono::duration_cast<ToDurationType>(duration);
}

/**
TODO : Documentation
*/
struct DateTime final
{
public:
    /**
    TODO : Documentation
    */
    enum class Day
    {
        Sunday    = 1, //!< TODO : Documentation
        Monday    = 2, //!< TODO : Documentation
        Tuesday   = 3, //!< TODO : Documentation
        Wednesday = 4, //!< TODO : Documentation
        Thursday  = 5, //!< TODO : Documentation
        Friday    = 6, //!< TODO : Documentation
        Saturday  = 7, //!< TODO : Documentation
    };

    /**
    TODO : Documentation
    */
    enum class Month
    {
        January   = 1,  //!< TODO : Documentation
        February  = 2,  //!< TODO : Documentation
        March     = 3,  //!< TODO : Documentation
        April     = 4,  //!< TODO : Documentation
        May       = 5,  //!< TODO : Documentation
        June      = 6,  //!< TODO : Documentation
        July      = 7,  //!< TODO : Documentation
        August    = 8,  //!< TODO : Documentation
        September = 9,  //!< TODO : Documentation
        October   = 10, //!< TODO : Documentation
        November  = 11, //!< TODO : Documentation
        December  = 12, //!< TODO : Documentation
    };

    /**
    TODO : Documentation
    */
    static DateTime now()
    {
        DateTime dateTime;
        auto systemClockNow = SystemClock::to_time_t(SystemClock::now());
        auto pLocalTime = std::localtime(&systemClockNow);
        if (pLocalTime) {
            dateTime.year = 1900 + pLocalTime->tm_year;
            dateTime.month = (Month)(1 + pLocalTime->tm_mon);
            dateTime.dayOfTheMonth = pLocalTime->tm_mday;
            dateTime.dayOfTheWeek = (Day)(1 + pLocalTime->tm_wday);
            dateTime.hour = pLocalTime->tm_hour;
            dateTime.minute = pLocalTime->tm_min;
            dateTime.second = pLocalTime->tm_sec;
        }
        return dateTime;
    }

    int year { };
    Month month { };
    int dayOfTheMonth { };
    Day dayOfTheWeek { };
    int hour { };
    int minute { };
    int second { };
};

/**
TODO : Documentation
*/
class Timer final
{
public:
    /**
    TODO : Documentation
    */
    template <typename DurationType = Milliseconds<>>
    inline auto total() const
    {
        return duration_cast<DurationType>(HighResolutionClock::now() - mBegin).count();
    }

    /**
    TODO : Documentation
    */
    inline void reset()
    {
        mBegin = HighResolutionClock::now();
    }

private:
    TimePoint<> mBegin { HighResolutionClock::now() };
};

/**
TODO : Documentation
*/
class Clock final
{
public:
    /**
    TODO : Documentation
    */
    inline const TimePoint<>& current() const
    {
        return mCurrent;
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType>
    inline auto elapsed() const
    {
        return duration_cast<DurationType>(mCurrent - mPrevious).count();
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType>
    inline auto total() const
    {
        return duration_cast<DurationType>(mCurrent - mBegin).count();
    }

    /**
    TODO : Documentation
    */
    inline void update()
    {
        mPrevious = mCurrent;
        mCurrent = HighResolutionClock::now();
    }

    /**
    TODO : Documentation
    */
    inline void reset()
    {
        mBegin = HighResolutionClock::now();
        mCurrent = mBegin;
        mPrevious = mBegin;
    }

private:
    TimePoint<> mBegin { HighResolutionClock::now() };
    TimePoint<> mPrevious { mBegin };
    TimePoint<> mCurrent { mBegin };
};

} // namespace dst
