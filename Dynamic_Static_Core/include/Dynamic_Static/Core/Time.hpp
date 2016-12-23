
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
}

namespace Dynamic_Static {
    namespace Time {
        /**
         * TODO : Documentation.
         */
        inline TimePoint<Nanosecond> now()
        {
            return HighResolutionClock::now();
        }
    }
}

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Timer final {
    private:
        TimePoint<Nanosecond> m_begin { Time::now() };

    public:
        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType total() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(Time::now() - m_begin).count());
        }

        /**
         * TODO : Documentation.
         */
        void reset()
        {
            m_begin = Time::now();
        }
    };
}

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
        TimePoint<Nanosecond> m_begin { Time::now() };
        TimePoint<Nanosecond> m_current { Time::now() };
        TimePoint<Nanosecond> m_previous { Time::now() - Nanosecond(1) };

    public:
        /**
         * TODO : Documentation.
         */
        const TimePoint<Nanosecond>& current() const
        {
            return m_current;
        }

        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType total() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(m_current - m_begin).count());
        }

        /**
         * TODO : Documentation.
         */
        template <typename DurationType, typename ReturnType = float>
        ReturnType elapsed() const
        {
            return static_cast<ReturnType>(duration_cast<DurationType>(m_current - m_previous).count());
        }

        /**
         * TODO : Documentation.
         */
        void update()
        {
            m_previous = m_current;
            m_current = Time::now();
        }
    };
}
