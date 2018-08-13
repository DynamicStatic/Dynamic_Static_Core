
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#define _USE_MATH_DEFINES
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <experimental/filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <limits>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>


#if defined(__X86_64__) || defined(_WIN64)
#ifndef DYNAMIC_STATIC_64_BIT
#define DYNAMIC_STATIC_64_BIT
#endif
#else
#ifndef DYNAMIC_STATIC_32_BIT
#define DYNAMIC_STATIC_32_BIT
#endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifndef DYNAMIC_STATIC_WINDOWS
#define DYNAMIC_STATIC_WINDOWS
#endif
#elif defined(__linux__)
#ifndef DYNAMIC_STATIC_LINUX
#define DYNAMIC_STATIC_LINUX
#endif
#endif

#if defined(__clang__)
#ifndef DYNAMIC_STATIC_CLANG
#define DYNAMIC_STATIC_CLANG
#endif
#elif defined(__GNUG__)
#ifndef DYNAMIC_STATIC_GCC
#define DYNAMIC_STATIC_GCC
#endif
#elif defined(_MSC_BUILD)
#ifndef DYNAMIC_STATIC_MSVC
#define DYNAMIC_STATIC_MSVC
#endif
#endif

#define DYNAMIC_STATIC "Dynamic_Static"
#define DYNAMIC_STATIC_CORE_VERSION_MAJOR 1
#define DYNAMIC_STATIC_CORE_VERSION_MINOR 0
#define DYNAMIC_STATIC_CORE_VERSION_PATCH 0

#define dst_stringify(STR) #STR
#define dst_expand(STR) dst_stringify(STR)
#define dst_file_line (__FILE__ " @ line " dst_expand(__LINE__))

namespace Dynamic_Static {

    static constexpr int VersionMajor { DYNAMIC_STATIC_CORE_VERSION_MAJOR }; /*!< Dynamic_Static.Core major version */
    static constexpr int VersionMinor { DYNAMIC_STATIC_CORE_VERSION_MINOR }; /*!< Dynamic_Static.Core minor version */
    static constexpr int VersionPatch { DYNAMIC_STATIC_CORE_VERSION_PATCH }; /*!< Dynamic_Static.Core patch version */

} // namespace Dynamic_Static
namespace dst = Dynamic_Static;

#ifndef DYNAMIC_STATIC_CORE_GLM_DISABLED
#ifndef DYNAMIC_STATIC_CORE_GLM_ENABLED
#define DYNAMIC_STATIC_CORE_GLM_ENABLED
#endif
#endif

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#ifdef DYNAMIC_STATIC_MSVC
#pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"
#ifdef DYNAMIC_STATIC_MSVC
#pragma warning(pop)
#endif

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED

#ifdef DYNAMIC_STATIC_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#endif

#ifdef DYNAMIC_STATIC_WINDOWS
#include <malloc.h>
#else
#include <stdlib.h>
#endif

namespace Dynamic_Static {

    /*
    * Allocates memory on a given alignment boundary.
    * @param [in] size The size of the requested allocation
    * @param [in] The alignment value, which must be a multiple of sizeof(void*) and an integer power of 2
    * @return A pointer to the memory block that was allocated or nullptr if the operation failed
    */
    inline void* aligned_malloc(size_t size, size_t alignment)
    {
        void* ptr = nullptr;
        #ifdef DYNAMIC_STATIC_WINDOWS
        ptr = _aligned_malloc(size, alignment);
        #else
        int result = posix_memalign(&ptr, alignment, size);
        if (!result) {
            ptr = nullptr;
        }
        #endif
        return ptr;
    }

    /*
    * Frees a block of memory that was allocated with dst::aligned_malloc().
    * @param [in] ptr A pointer to the memory block to free
    */
    inline void aligned_free(void* ptr)
    {
        #ifdef DYNAMIC_STATIC_WINDOWS
        _aligned_free(ptr);
        #else
        free(ptr);
        #endif
    }

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Represents an std::function<> with no return value.
    */
    template <typename ...Args>
    using Action = std::function<void(Args...)>;

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Rounds a given floating point value to the nearest whole number then casts the result to a given type.
    * @param <RT> The type to cast the rounded result to
    * @param <T> The type of the value to round and cast
    * @param [in] The value to round and cast
    * @return The value after rounding and casting
    */
    template <typename RT, typename T>
    inline RT round_cast(const T& value)
    {
        return static_cast<RT>(std::round(value));
    }

    /*
    * Gets a linear interpolation from one given floating point value to another using a 0 - 1 weighting.
    * @param <T> The type of the value to interpolate
    * @param [in] v0 The value to interpolate from
    * @param [in] v1 The value to interpolate to
    * @param [in] t The weight of the interpolation
    * @return The interpolated value
    */
    template <typename T>
    inline T lerp(T v0, T v1, T t)
    {
        // FROM : https://devblogs.nvidia.com/parallelforall/lerp-faster-cuda/
        // TLDR : std::fma() (fused multiply-add) is commonly implemented as a
        //        single CPU instruction which will be used if available.  In
        //        addition to a performance benefit, accuracy is improved since
        //        there is no rounding performed until std::fma() returns.
        //
        //        In this lerp function there are 4 rounding errors...
        //            (static_cast<T>(1) - t) * v0 + t * v1
        //
        //        ...this version has 3 rounding errors and no guarantee that
        //        the result equals v1 when t equals 1 due to rounding error.
        //            v0 + t * (v1 - v0)
        //
        //        std::fma() computes...
        //        x * y + z
        //        so our operation is...
        //        t * v1 + (-t * v0 + v0)
        return std::fma(t, v1, std::fma(-t, v0, v0));
    }

    /*
    * Gets the first element in a given range that is equal to a given value.
    * @param [in] range The range to search
    * @param [in] value The value to search for
    * @param <RangeType> The type of the range to search
    * \n NOTE : RangeType must provide begin() and end() methods
    * @param <ValueType> The type of the value to search for
    * @return Iterator to the first element equal to the given value
    */
    template <typename RangeType, typename ValueType>
    inline auto find(RangeType& range, const ValueType& value)
    {
        return std::find(range.begin(), range.end(), value);
    }

    /*
    * Gets the first element in a given range that is equal to a given value.
    * @param [in] range The range to search
    * @param [in] value The value to search for
    * @param <RangeType> The type of the range to search
    * \n NOTE : RangeType must provide begin() and end() methods
    * @param <ValueType> The type of the value to search for
    * @return Iterator to the first element equal to the given value
    */
    template <typename RangeType, typename ValueType>
    inline auto find(const RangeType& range, const ValueType& value)
    {
        return std::find(range.begin(), range.end(), value);
    }

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Removes copy constructors from derived classes.
    */
    class NonCopyable
    {
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;

    private:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides tracking of mutual subscription between objects.
    */
    class Subscribable
        : NonCopyable
    {
    private:
        std::vector<Subscribable*> mSubscribers;
        std::vector<Subscribable*> mSubscriptions;

    public:
        /*
        * Constructs an instance of Subscribable.
        */
        inline Subscribable() = default;

        /*
        * Moves an instance of Subscribable.
        * @param [in] other The Subscribable to move from
        */
        inline Subscribable(Subscribable&& other)
        {
            *this = std::move(other);
        }

        /*
        * Destroys this instance of Subscribable.
        */
        virtual inline ~Subscribable()
        {
            clear();
        }

        /*
        * Moves an instance of Subscribable.
        * @param [in] other The Subscribable to move from
        * @return This Subscribable
        */
        inline Subscribable& operator=(Subscribable&& other)
        {
            if (this != &other) {
                mSubscribers = std::move(other.mSubscribers);
                for (auto subscriber : mSubscribers) {
                    auto itr = dst::find(subscriber->mSubscriptions, &other);
                    assert(itr != subscriber->mSubscriptions.end());
                    *itr = this;
                }
                mSubscriptions = std::move(other.mSubscriptions);
                for (auto subscription : mSubscriptions) {
                    auto itr = dst::find(subscription->mSubscribers, &other);
                    assert(itr != subscription->mSubscribers.end());
                    *itr = this;
                }
            }
            return *this;
        }

        /*
        * Subscribes a given Subscribable to this Subscribable.
        * @param [in] subscriber The Subscribable subscribing to this Subscribable
        * @return This Subscribable
        */
        inline Subscribable& operator+=(Subscribable& subscriber)
        {
            if (!subscriber.is_subscribed_to(*this)) {
                mSubscribers.push_back(&subscriber);
                subscriber.mSubscriptions.push_back(this);
            }
            return *this;
        }

        /*
        * Unsubscribes a given Subscribable from this Subscribable.
        * @param [in] subscriber The Subscribable unsubscribing from this Subscribable
        * @return This Subscribable
        */
        inline Subscribable& operator-=(Subscribable& subscriber)
        {
            auto itr = dst::find(mSubscribers, &subscriber);
            if (itr != mSubscribers.end()) {
                mSubscribers.erase(itr);
                itr = dst::find(subscriber.mSubscriptions, this);
                assert(itr != subscriber.mSubscriptions.end());
                subscriber.mSubscriptions.erase(itr);
            }
            return *this;
        }

    public:
        /*
        * Gets of this Subscribable's subscribers.
        * @return This Subscribable's subscribers
        */
        inline const std::vector<Subscribable*>& get_subscribers() const
        {
            return mSubscribers;
        }

        /*
        * Gets of this Subscribable's subscriptions.
        * @return This Subscribable's subscrpitions
        */
        inline const std::vector<Subscribable*>& get_subscriptions() const
        {
            return mSubscriptions;
        }

        /*
        * Gets a value indicating whether or not this Subscribable is subscribed to a given Subscribable.
        * @return Whether or not this Subscribable is subscribed to a given Subscribable
        */
        inline bool is_subscribed_to(const Subscribable& other) const
        {
            return dst::find(mSubscriptions, &other) != mSubscriptions.end();
        }

        /*
        * Removes all of this Subscribable's subscribers.
        */
        inline void clear_subscribers()
        {
            for (auto subscriber : mSubscribers) {
                auto itr = dst::find(subscriber->mSubscriptions, this);
                assert(itr != subscriber->mSubscriptions.end());
                subscriber->mSubscriptions.erase(itr);
            }
            mSubscribers.clear();
        }

        /*
        * Removes all of this Subscribable's subscriptions.
        */
        inline void clear_subscriptions()
        {
            for (auto& subscription : mSubscriptions) {
                auto itr = dst::find(subscription->mSubscribers, this);
                assert(itr != subscription->mSubscribers.end());
                subscription->mSubscribers.erase(itr);
            }
            mSubscriptions.clear();
        }

        /*
        * Removes all of this Subscribable's subscribers and subscriptions.
        */
        inline void clear()
        {
            clear_subscribers();
            clear_subscriptions();
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Encapsulates a Subscribable multicast Action<>.
    */
    template <typename ...Args>
    class Delegate
        : Subscribable
    {
    private:
        Action<Args...> mAction;

    public:
        /*
        * Constructs an instance of Delegate.
        */
        inline Delegate() = default;

        /*
        * Constructs an instance of Delegate.
        * @param [in] action This Delegate's Action<>
        */
        inline Delegate(const Action<Args...>& action)
            : mAction { action }
        {
        }

        /*
        * Assigns this Delegate's Action<>.
        * @return This Delegate
        */
        inline Delegate& operator=(const Action<Args...>& action)
        {
            mAction = action;
            return *this;
        }

        /*
        * Removes this Delegate's Action<> and all subscribers.
        * \n NOTE : This method doesn't remove subscriptions
        * @return This Delegate
        */
        inline Delegate& operator=(nullptr_t)
        {
            clear_subscribers();
            mAction = nullptr;
            return *this;
        }

        /*
        * Subscribes a given Delegate to this Delegate.
        * @param [in] other The Delegate to subscribe to this Delegate
        * @return This Delegate
        */
        inline Delegate& operator+=(Delegate<Args...>& other)
        {
            Subscribable::operator+=(other);
            return *this;
        }

        /*
        * Unsubscribes a given Delegate from this Delegate.
        * @param [in] other The Delegate to unsubscribe from this Delegate
        * @return This Delegate
        */
        inline Delegate& operator-=(Delegate<Args...>& other)
        {
            Subscribable::operator-=(other);
            return *this;
        }

        /*
        * Executes this Delegate.
        * @param [in] args The arguments to execute this Delegate with
        */
        inline void operator()(Args... args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
            for (auto subscriber : Subscribable::get_subscribers()) {
                const Delegate<Args...>& delegate = *reinterpret_cast<Delegate<Args...>*>(subscriber);
                delegate(std::forward<Args>(args)...);
            }
        }

        /*
        * Gets a value indicating whether or not this Delegate has a valid Action<>.
        * @return Whether or not this Delegate has a valid Action<>
        */
        inline operator bool() const
        {
            return mAction != nullptr;
        }

    public:
        /*
        * Gets this Delegate's subscribers.
        * @return This Delegate's subscribers
        */
        inline const std::vector<Subscribable*>& get_subscribers() const
        {
            return Subscribable::get_subscribers();
        }

        /*
        * Gets this Delegate's subscriptions.
        * @return This Delegate's subscrpitions
        */
        inline const std::vector<Subscribable*>& get_subscriptions() const
        {
            return Subscribable::get_subscriptions();
        }

        /*
        * Removes all of this Delegate's subscribers.
        */
        inline void clear_subscribers()
        {
            Subscribable::clear_subscribers();
        }

        /*
        * Removes all of this Delegate's subscriptions.
        */
        inline void clear_subscriptions()
        {
            Subscribable::clear_subscriptions();
        }

        /*
        * Removes all of this Delegate's subscriptions.
        */
        inline void clear()
        {
            Subscribable::clear();
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Encapsulates a collection of Delegates<> that are callable by a given type.
    * @param <CallerType> The type of object that can excute this Event
    * @param <Args> This Event's argument types
    */
    template <typename CallerType, typename ...Args>
    class Event
        : Delegate<Args...>
    {
    public:
        /*
        * Constructs an instance of Event.
        */
        inline Event() = default;

        /*
        * Constructs an instance of Event.
        * @param [in] action This Event's Action<>
        */
        inline Event(const Action<Args...>& action)
            : mAction { action }
        {
        }

        /*
        * Assigns this Event's Action<>.
        * @return This Event
        */
        inline Event& operator=(const Action<Args...>& action)
        {
            Delegate<Args...>::operator=(action);
            return *this;
        }

        /*
        * Removes this Event's Action<> and all subscribers.
        * \n NOTE : This method doesn't remove subscriptions
        * @return This Event
        */
        inline Event& operator=(nullptr_t)
        {
            Delegate<Args...>::operator=(nullptr);
            return *this;
        }

        /*
        * Subscribes a given Delegate<> to this Event.
        * @param [in] delegate The Delegate<> to subscribe to this Event
        * @return This Event
        */
        inline Event<CallerType, Args...>& operator+=(Delegate<Args...>& delegate)
        {
            Delegate<Args...>::operator+=(delegate);
            return *this;
        }

        /*
        * Unsubscribes a given Delegate<> from this Event.
        * @param [in] delegate The Delegate<> to unsubscribe from this Event
        * @return This Event
        */
        inline Event<CallerType, Args...>& operator-=(Delegate<Args...>& delegate)
        {
            Delegate<Args...>::operator-=(delegate);
            return *this;
        }

    private:
        /*
        * Executes all of this Event's subscribed Delegates<>.
        * \n NOTE : This method can only be called by an object of type CallerType
        * @param [in] args The arguments to execute this Event with
        */
        inline void operator()(Args&&... args) const
        {
            Delegate<Args...>::operator()(std::forward<Args>(args)...);
        }

    public:
        /*
        * Gets this Event's subscribers.
        * @return This Event's subscribers
        */
        inline const std::vector<dst::Subscribable*>& get_subscribers() const
        {
            return Delegate<Args...>::get_subscribers();
        }

    private:
        /*
        * Removes all of this Events's subscribers.
        * \n NOTE : This method can only be called by an object of type CallerType
        */
        inline void clear()
        {
            Delegate<Args...>::clear();
        }

    private:
        friend CallerType;
    };

} // namespace Dynamic_Static

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
    inline constexpr ToType duration_cast(const FromType& duration)
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
        inline auto total() const
        {
            return duration_cast<DurationType>(HighResolutionClock::now() - mBegin).count();
        }

        /*
        * Resets this Timer.
        */
        inline void reset()
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
        inline const TimePoint<>& current() const
        {
            return mCurrent;
        }

        /*
        * Gets this Clock's total run time.
        * @param <DurationType> The type of Duration to use
        * @return This Clock's total run time
        */
        template <typename DurationType>
        inline auto total() const
        {
            return duration_cast<DurationType>(mCurrent - mBegin).count();
        }

        /*
        * Gets the amount of time elapsed since this Clock's last update.
        * @param <DurationType> The type of Duration to use
        * @return This Clock's elapsed time
        */
        template <typename DurationType>
        inline auto elapsed() const
        {
            return duration_cast<DurationType>(mCurrent - mPrevious).count();
        }

        /*
        * Updates this Clock.
        */
        inline void update()
        {
            mPrevious = mCurrent;
            mCurrent = HighResolutionClock::now();
        }

        /*
        * Resets this Clock.
        */
        inline void reset()
        {
            mBegin = HighResolutionClock::now();
            mCurrent = mBegin;
            mPrevious = mBegin;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Suspends the calling thread until a given std::condition variable is notified or a time out is reached.
    * @param <PredicateType> The type of the predicate
    * @param [in] lock A locked std::unique_lock<std::mutex> that will be unlocked on wait and relocked on resume
    * @param [in] condition The std::condition_variable to wait on
    * @param [in] predicate The predicate to test before waiting and on spurious or notified resumes
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

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides high level control over signaling and synchronization between threads.
    */
    class Semaphore final
        : NonCopyable
    {
    private:
        std::mutex mMutex;
        std::condition_variable mCondition;
        int mWaitingThreadCount { 0 };
        int mSignalCount { 0 };

    public:
        /*
        * Constructs an instance of Semaphore.
        * @param [in] signalCount This Semaphore's initial signalCount (optional = 0)
        */
        inline Semaphore(int signalCount = 0)
            : mSignalCount { signalCount }
        {
        }

        /*
        * Destroys this instance of Semphore.
        * \n NOTE : This will cause all threads waiting on this Semaphore to resume execution.
        */
        inline ~Semaphore()
        {
            notify_all();
            while (mWaitingThreadCount) {
                std::this_thread::yield();
            }
        }

    public:
        /*
        * Gets this Semaphore's current signal count.
        * \n NOTE : This Semaphore's signal count may have changed by the time this method returns
        * @return This Semaphore's current signal count
        */
        inline int get_signal_count() const
        {
            return mSignalCount;
        }

        /*
        * Notifies a given number of threads waiting on this Semaphore and increments this Semaphore's signal count once for each thread notified.
        * @param [in] count The number of threads to notify (optional = 1)
        */
        inline void notify(int count = 1)
        {
            std::unique_lock<std::mutex> lock(mMutex);
            for (int i = 0; i < count; ++i) {
                mCondition.notify_one();
                ++mSignalCount;
            }
        }

        /*
        * Notifies each thread waiting on this Semaphore and increments this Semaphore's signal count once for each thread notified.
        */
        inline void notify_all()
        {
            notify(mWaitingThreadCount);
        }

        /*
        * Suspends the calling thread if this Semaphore's signal count is zero and decrements this Semaphore's signal count by one.
        * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        * @param [in] timeOut The maximum amount of time to wait (optional = 0)
        * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            ++mWaitingThreadCount;
            auto predicate = [&] { return mSignalCount > 0; };
            if (dst::wait(lock, mCondition, timeOut, predicate)) {
                --mSignalCount;
            }
            --mWaitingThreadCount;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides high level control over queueing tasks for a persistent std::thread.
    */
    class Worker final
        : NonCopyable
    {
    public:
        /*
        * Represents a Task for a Worker to process on a child thread.
        */
        using Task = std::function<void()>;

    private:
        std::thread mThread;
        std::mutex mMutex;
        std::condition_variable mTaskReceived;
        std::condition_variable mTasksComplete;
        std::queue<Task> mTasks;
        bool mRunning { false };

    public:
        /*
        * Constructs an instance of Worker.
        */
        inline Worker()
        {
            mThread = std::thread(
                [&]
                {
                    Millisecond<> duration { 0 };
                    auto predicate = [&] { return !mTasks.empty() || !mRunning; };
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

        /*
        * Destroys this instance of Worker.
        */
        inline ~Worker()
        {
            mRunning = false;
            mTaskReceived.notify_all();
            if (mThread.joinable()) {
                mThread.join();
            }
        }

    public:
        /*
        * Gets this Worker's pending Task count
        * \n NOTE : This Workers's Task count may have changed by the time this method returns
        * @return This Worker's Task count
        */
        inline size_t get_task_count() const
        {
            return mTasks.size();
        }

        /*
        * Pushes a Task for this Worker to process on a child thread.
        * @param [in] task The Task to push
        */
        inline void push(Task task)
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mTaskReceived.notify_one();
            mTasks.push(task);
        }

        /*
        * Suspends the calling thread until this Worker has completed all pending tasks.
        * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        * @param [in] timeOut The maximum amount of time to wait (optional = 0)
        * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            std::unique_lock<std::mutex> lock(mMutex);
            auto predicate = [&] { return mTasks.empty(); };
            dst::wait(lock, mTasksComplete, timeOut, predicate);
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides high level control over a pool of Workers.
    */
    class ThreadPool final
        : NonCopyable
    {
    private:
        std::vector<Worker> mWorkers;
        size_t mIndex { 0 };

    public:
        /*
        * Constructs an instance of ThreadPool.
        * @param [in] workerCount This ThreadPool's worker count (optional = 0)
        * \n NOTE : A value of 0 for workerCount results in using the value returned from std::thread::hardware_concurrency()
        */
        inline ThreadPool(size_t workerCount = 0)
        {
            size_t maxWorkerCount = std::thread::hardware_concurrency();
            workerCount = workerCount ? workerCount : maxWorkerCount;
            workerCount = std::clamp(workerCount, size_t { 1 }, maxWorkerCount);
            mWorkers = std::vector<Worker>(workerCount);
        }

        /*
        * Destroys this instance of ThreadPool.
        */
        inline ~ThreadPool()
        {
            wait();
        }

    public:
        /*
        * Gets this ThreadPool' Worker count.
        * @return This ThreadPool's Worker count
        */
        inline size_t get_worker_count() const
        {
            return mWorkers.size();
        }

        /*
        * Gets this ThreadPool's pending Worker::Task count.
        * \n NOTE : This ThreadPool's pending Worker::Task count may have changed by the time this method returns
        */
        inline size_t get_task_count() const
        {
            size_t taskCount = 0;
            for (const auto& worker : mWorkers) {
                taskCount += worker.get_task_count();
            }
            return taskCount;
        }

        /*
        * Pushes a Worker::Task for this ThreadPool to process on a child thread.
        */
        inline void push(Worker::Task task)
        {
            mWorkers[mIndex++].push(task);
            if (mIndex >= mWorkers.size()) {
                mIndex = 0;
            }
        }

        /*
        * Suspends the calling thread until this ThreadPool has completed all pending tasks.
        * @param <DurationType> The type of the timeOut Duration (optional = Millisecond<>)
        * @param [in] timeOut The maximum amount of time to wait (optional = 0)
        * \n NOTE : A Duration of 0 for timeOut results in an infinite maximum wait
        */
        template <typename DurationType = Millisecond<>>
        inline void wait(const DurationType& timeOut = DurationType { 0 })
        {
            for (auto& worker : mWorkers) {
                worker.wait(timeOut);
            }
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Encapsulates an Action<> that is callable by a given type.
    * @param <CallerType> The type of object that can execute this Callback
    * @param <Args> This Callback's argument types
    */
    template <typename CallerType, typename ...Args>
    class Callback
    {
        friend CallerType;

    private:
        Action<Args...> mAction;

    public:
        /*
        * Assigns this Callback's Action<>.
        * @return This Callback
        */
        inline Callback<CallerType, Args...>& operator=(const Action<Args...>& action)
        {
            mAction = action;
            return *this;
        }

        /*
        * Gets a value indicating whether or not this Callback has a valid Action<>.
        * @return Whether or not this Callback has a valid Action<>
        */
        inline operator bool() const
        {
            return mAction != nullptr;
        }

    private:
        /*
        * Executes this Callback.
        * \n NOTE : This method can only be called by an object of type CallerType
        * @param [in] args The arguments to execute this Callback with
        */
        inline void operator()(Args&&... args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Represents a non-owning reference to a contiguous sequence of objects.
    */
    template <typename T>
    class Span
    {
        // FROM : Modified ArrayProxy https://github.com/KhronosGroup/Vulkan-Hpp

    private:
        T* mData { nullptr };
        size_t mCount { 0 };

    public:
        /*
        * Constructs an instance of Span.
        */
        Span() = default;

        /*
        * Constructs an instance of Span.
        */
        constexpr Span(std::nullptr_t)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        Span(T& data)
            : mData { &data }
            , mCount { 1 }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        * @param [in] count This Span's count
        */
        Span(T* data, size_t count)
            : mData { data }
            , mCount { count }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param <N> This Span's count
        * @param [in] data This Span's data
        */
        template <size_t N>
        Span(std::array<typename std::remove_const<T>::type, N>& data)
            : mData(data.data())
            , mCount(N)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param <N> This Span's count
        * @param [in] data This Span's data
        */
        template <size_t N>
        Span(const std::array<typename std::remove_const<T>::type, N>& data)
            : mData(data.data())
            , mCount(N)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Span(std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : mData { data.data() }
            , mCount { data.size() }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Span(const std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : mData { data.data() }
            , mCount { data.size() }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        Span(const std::initializer_list<T>& data)
            : mData { data.begin() }
            , mCount { data.end() - data.begin() }
        {
        }

        /*
        * Gets a reference to an element at a given index.
        * @param [in] index The index of the element to get
        * @return The element at the given index
        */
        T& operator[](size_t index)
        {
            return mData[index];
        }

        /*
        * Gets a reference to an element at a given index.
        * @param [in] index The index of the element to get
        * @return The element at the given index
        */
        const T& operator[](size_t index) const
        {
            return mData[index];
        }

    public:
        /*
        * Gets an iterator to the beginning of this Span's sequence.
        * @return An iterator to the beginning of this Span's sequence
        */
        const T* begin() const
        {
            return mData;
        }

        /*
        * Gets an iterator to the end of this Span's sequence.
        * @return An iterator to the end of this Span's sequence
        */
        const T* end() const
        {
            return mData + mCount;
        }

        /*
        * Gets a reference to this Span's first element.
        * @return A reference to this Span's first element
        */
        const T& front() const
        {
            assert(mData && mCount);
            return *mData;
        }

        /*
        * Gets a reference to this Span's last element.
        * @return A reference to this Span's last element
        */
        const T& back() const
        {
            assert(mData && mCount);
            return *(mData + mCount - 1);
        }

        /*
        * Gets a value indicating whether or not this Span is empty.
        * @return A value indicating whether or not this Span is empty
        */
        bool empty() const
        {
            return (mCount == 0);
        }

        /*
        * Gets this Span's count.
        * @return This Span's count
        */
        size_t size() const
        {
            return mCount;
        }

        /*
        * Gets this Span's size in bytes.
        * @return This Span's size in bytes
        */
        size_t size_bytes() const
        {
            return mCount * sizeof(T);
        }

        /*
        * Gets a pointer to this Span's underlying storage.
        * @return A pointer to this Span's underlying storage
        */
        T* data() const
        {
            return mData;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace File {

    /*
    * Reads all lines in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::string> to populate with the lines read from the file
    */
    inline void read_all_lines(
        const std::string_view& filePath,
        std::vector<std::string>& lines
    )
    {
        lines.clear();
        std::ifstream file(filePath.data());
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
        }
    }

    /*
    * Reads all lines in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::string> populated with the lines read from the file
    */
    inline std::vector<std::string> read_all_lines(const std::string_view& filePath)
    {
        std::vector<std::string> lines;
        read_all_lines(filePath, lines);
        return lines;
    }

    /*
    * Reads all bytes in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::byte> to populate with the bytes read from the file
    */
    inline void read_all_bytes(
        const std::string_view& filePath,
        std::vector<std::byte>& bytes
    )
    {
        bytes.clear();
        std::ifstream file(filePath.data(), std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            auto size = file.tellg();
            bytes.resize(static_cast<size_t>(size));
            file.seekg(0, std::ios::beg);
            file.read(reinterpret_cast<char*>(bytes.data()), size);
        }
    }

    /*
    * Reads all bytes in the file at the given file path.
    * @param [in] filePath The path to the file to read
    * @param [in] lines An std::vector<std::byte> populated with the bytes read from the file
    */
    inline std::vector<std::byte> read_all_bytes(const std::string_view& filePath)
    {
        std::vector<std::byte> bytes;
        read_all_bytes(filePath, bytes);
        return bytes;
    }

} // namespace File
} // namespace Dynamic_Static

// NOTE : This file should be removed once std::filesystem is fully supported.

namespace Dynamic_Static {

    namespace filesystem = std::experimental::filesystem;

} // namespace Dynamic_Static

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

namespace Dynamic_Static {
namespace detail {

    template <typename Void>
    struct ColorConstants
    {
        // FROM : https://docs.microsoft.com/en-us/previous-versions/windows/xna/ff433752(v%3dxnagamestudio.41)

        static const glm::vec4 White;                /*!< Constant color { 1.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Black;                /*!< Constant color { 0.0f,       0.0f,       0.0f,       1.0f } */
        static const glm::vec4 Transparent;          /*!< Constant color { 0.0f,       0.0f,       0.0f,       0.0f } */
        static const glm::vec4 AliceBlue;            /*!< Constant color { 0.941177f,  0.972549f,  1.0f,       1.0f } */
        static const glm::vec4 AntiqueWhite;         /*!< Constant color { 0.980392f,  0.921569f,  0.843137f,  1.0f } */
        static const glm::vec4 Aqua;                 /*!< Constant color { 0.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Aquamarine;           /*!< Constant color { 0.498039f,  1.0f,       0.831373f,  1.0f } */
        static const glm::vec4 Azure;                /*!< Constant color { 0.941177f,  1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Beige;                /*!< Constant color { 0.960784f,  0.960784f,  0.862745f,  1.0f } */
        static const glm::vec4 Bisque;               /*!< Constant color { 1.0f,       0.894118f,  0.768628f,  1.0f } */
        static const glm::vec4 BlanchedAlmond;       /*!< Constant color { 1.0f,       0.921569f,  0.803922f,  1.0f } */
        static const glm::vec4 Blue;                 /*!< Constant color { 0.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 BlueViolet;           /*!< Constant color { 0.541176f,  0.168627f,  0.886275f,  1.0f } */
        static const glm::vec4 Brown;                /*!< Constant color { 0.647059f,  0.164706f,  0.164706f,  1.0f } */
        static const glm::vec4 BurlyWood;            /*!< Constant color { 0.870588f,  0.721569f,  0.529412f,  1.0f } */
        static const glm::vec4 CadetBlue;            /*!< Constant color { 0.372549f,  0.619608f,  0.627451f,  1.0f } */
        static const glm::vec4 Chartreuse;           /*!< Constant color { 0.498039f,  1.0f,       0.0f,       1.0f } */
        static const glm::vec4 Chocolate;            /*!< Constant color { 0.823529f,  0.411765f,  0.117647f,  1.0f } */
        static const glm::vec4 Coral;                /*!< Constant color { 1.0f,       0.498039f,  0.313726f,  1.0f } */
        static const glm::vec4 CornflowerBlue;       /*!< Constant color { 0.392157f,  0.584314f,  0.929412f,  1.0f } */
        static const glm::vec4 Cornsilk;             /*!< Constant color { 1.0f,       0.972549f,  0.862745f,  1.0f } */
        static const glm::vec4 Crimson;              /*!< Constant color { 0.862745f,  0.0784314f, 0.235294f,  1.0f } */
        static const glm::vec4 Cyan;                 /*!< Constant color { 0.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 DarkBlue;             /*!< Constant color { 0.0f,       0.0f,       0.545098f,  1.0f } */
        static const glm::vec4 DarkCyan;             /*!< Constant color { 0.0f,       0.545098f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkGoldenrod;        /*!< Constant color { 0.721569f,  0.52549f,   0.0431373f, 1.0f } */
        static const glm::vec4 DarkGray;             /*!< Constant color { 0.662745f,  0.662745f,  0.662745f,  1.0f } */
        static const glm::vec4 DarkGreen;            /*!< Constant color { 0.0f,       0.392157f,  0.0f,       1.0f } */
        static const glm::vec4 DarkKhaki;            /*!< Constant color { 0.741176f,  0.717647f,  0.419608f,  1.0f } */
        static const glm::vec4 DarkMagenta;          /*!< Constant color { 0.545098f,  0.0f,       0.545098f,  1.0f } */
        static const glm::vec4 DarkOliveGreen;       /*!< Constant color { 0.333333f,  0.419608f,  0.184314f,  1.0f } */
        static const glm::vec4 DarkOrange;           /*!< Constant color { 1.0f,       0.54902f,   0.0f,       1.0f } */
        static const glm::vec4 DarkOrchid;           /*!< Constant color { 0.6f,       0.196078f,  0.8f,       1.0f } */
        static const glm::vec4 DarkRed;              /*!< Constant color { 0.545098f,  0.0f,       0.0f,       1.0f } */
        static const glm::vec4 DarkSalmon;           /*!< Constant color { 0.913726f,  0.588235f,  0.478431f,  1.0f } */
        static const glm::vec4 DarkSeaGreen;         /*!< Constant color { 0.560784f,  0.737255f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkSlateBlue;        /*!< Constant color { 0.282353f,  0.239216f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkSlateGray;        /*!< Constant color { 0.184314f,  0.309804f,  0.309804f,  1.0f } */
        static const glm::vec4 DarkTurquoise;        /*!< Constant color { 0.0f,       0.807843f,  0.819608f,  1.0f } */
        static const glm::vec4 DarkViolet;           /*!< Constant color { 0.580392f,  0.0f,       0.827451f,  1.0f } */
        static const glm::vec4 DeepPink;             /*!< Constant color { 1.0f,       0.0784314f, 0.576471f,  1.0f } */
        static const glm::vec4 DeepSkyBlue;          /*!< Constant color { 0.0f,       0.74902f,   1.0f,       1.0f } */
        static const glm::vec4 DimGray;              /*!< Constant color { 0.411765f,  0.411765f,  0.411765f,  1.0f } */
        static const glm::vec4 DodgerBlue;           /*!< Constant color { 0.117647f,  0.564706f,  1.0f,       1.0f } */
        static const glm::vec4 Firebrick;            /*!< Constant color { 0.698039f,  0.133333f,  0.133333f,  1.0f } */
        static const glm::vec4 FloralWhite;          /*!< Constant color { 1.0f,       0.980392f,  0.941177f,  1.0f } */
        static const glm::vec4 ForestGreen;          /*!< Constant color { 0.133333f,  0.545098f,  0.133333f,  1.0f } */
        static const glm::vec4 Fuchsia;              /*!< Constant color { 1.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 Gainsboro;            /*!< Constant color { 0.862745f,  0.862745f,  0.862745f,  1.0f } */
        static const glm::vec4 GhostWhite;           /*!< Constant color { 0.972549f,  0.972549f,  1.0f,       1.0f } */
        static const glm::vec4 GearsBlue;            /*!< Constant color { 0.2f,       0.2f,       1.0f,       1.0f } */
        static const glm::vec4 GearsGreen;           /*!< Constant color { 0.0f,       0.8f,       0.2f,       1.0f } */
        static const glm::vec4 GearsRed;             /*!< Constant color { 0.8f,       0.1f,       0.0f,       1.0f } */
        static const glm::vec4 Gold;                 /*!< Constant color { 1.0f,       0.843137f,  0.0f,       1.0f } */
        static const glm::vec4 Goldenrod;            /*!< Constant color { 0.854902f,  0.647059f,  0.12549f,   1.0f } */
        static const glm::vec4 Gray;                 /*!< Constant color { 0.501961f,  0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 Green;                /*!< Constant color { 0.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 GreenYellow;          /*!< Constant color { 0.678431f,  1.0f,       0.184314f,  1.0f } */
        static const glm::vec4 HalfGray;             /*!< Constant color { 0.5f,       0.5f,       0.5f,       1.0f } */
        static const glm::vec4 Honeydew;             /*!< Constant color { 0.941177f,  1.0f,       0.941177f,  1.0f } */
        static const glm::vec4 HotPink;              /*!< Constant color { 1.0f,       0.411765f,  0.705882f,  1.0f } */
        static const glm::vec4 IndianRed;            /*!< Constant color { 0.803922f,  0.360784f,  0.360784f,  1.0f } */
        static const glm::vec4 Indigo;               /*!< Constant color { 0.294118f,  0.0f,       0.509804f,  1.0f } */
        static const glm::vec4 Ivory;                /*!< Constant color { 1.0f,       1.0f,       0.941177f,  1.0f } */
        static const glm::vec4 Khaki;                /*!< Constant color { 0.941177f,  0.901961f,  0.54902f,   1.0f } */
        static const glm::vec4 Lavender;             /*!< Constant color { 0.901961f,  0.901961f,  0.980392f,  1.0f } */
        static const glm::vec4 LavenderBlush;        /*!< Constant color { 1.0f,       0.941177f,  0.960784f,  1.0f } */
        static const glm::vec4 LawnGreen;            /*!< Constant color { 0.486275f,  0.988235f,  0.0f,       1.0f } */
        static const glm::vec4 LemonChiffon;         /*!< Constant color { 1.0f,       0.980392f,  0.803922f,  1.0f } */
        static const glm::vec4 LightBlue;            /*!< Constant color { 0.678431f,  0.847059f,  0.901961f,  1.0f } */
        static const glm::vec4 LightCoral;           /*!< Constant color { 0.941177f,  0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 LightCyan;            /*!< Constant color { 0.878431f,  1.0f,       1.0f,       1.0f } */
        static const glm::vec4 LightGoldenrodYellow; /*!< Constant color { 0.980392f,  0.980392f,  0.823529f,  1.0f } */
        static const glm::vec4 LightGray;            /*!< Constant color { 0.827451f,  0.827451f,  0.827451f,  1.0f } */
        static const glm::vec4 LightGreen;           /*!< Constant color { 0.564706f,  0.933333f,  0.564706f,  1.0f } */
        static const glm::vec4 LightPink;            /*!< Constant color { 1.0f,       0.713726f,  0.756863f,  1.0f } */
        static const glm::vec4 LightSalmon;          /*!< Constant color { 1.0f,       0.627451f,  0.478431f,  1.0f } */
        static const glm::vec4 LightSeaGreen;        /*!< Constant color { 0.12549f,   0.698039f,  0.666667f,  1.0f } */
        static const glm::vec4 LightSkyBlue;         /*!< Constant color { 0.529412f,  0.807843f,  0.980392f,  1.0f } */
        static const glm::vec4 LightSlateGray;       /*!< Constant color { 0.466667f,  0.533333f,  0.6f,       1.0f } */
        static const glm::vec4 LightSteelBlue;       /*!< Constant color { 0.690196f,  0.768628f,  0.870588f,  1.0f } */
        static const glm::vec4 LightYellow;          /*!< Constant color { 1.0f,       1.0f,       0.878431f,  1.0f } */
        static const glm::vec4 Lime;                 /*!< Constant color { 0.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 LimeGreen;            /*!< Constant color { 0.196078f,  0.803922f,  0.196078f,  1.0f } */
        static const glm::vec4 Linen;                /*!< Constant color { 0.980392f,  0.941177f,  0.901961f,  1.0f } */
        static const glm::vec4 Magenta;              /*!< Constant color { 1.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 Maroon;               /*!< Constant color { 0.501961f,  0.0f,       0.0f,       1.0f } */
        static const glm::vec4 MediumAquamarine;     /*!< Constant color { 0.4f,       0.803922f,  0.666667f,  1.0f } */
        static const glm::vec4 MediumBlue;           /*!< Constant color { 0.0f,       0.0f,       0.803922f,  1.0f } */
        static const glm::vec4 MediumOrchid;         /*!< Constant color { 0.729412f,  0.333333f,  0.827451f,  1.0f } */
        static const glm::vec4 MediumPurple;         /*!< Constant color { 0.576471f,  0.439216f,  0.858824f,  1.0f } */
        static const glm::vec4 MediumSeaGreen;       /*!< Constant color { 0.235294f,  0.701961f,  0.443137f,  1.0f } */
        static const glm::vec4 MediumSlateBlue;      /*!< Constant color { 0.482353f,  0.407843f,  0.933333f,  1.0f } */
        static const glm::vec4 MediumSpringGreen;    /*!< Constant color { 0.0f,       0.980392f,  0.603922f,  1.0f } */
        static const glm::vec4 MediumTurquoise;      /*!< Constant color { 0.282353f,  0.819608f,  0.8f,       1.0f } */
        static const glm::vec4 MediumVioletRed;      /*!< Constant color { 0.780392f,  0.0823529f, 0.521569f,  1.0f } */
        static const glm::vec4 MidnightBlue;         /*!< Constant color { 0.0980392f, 0.0980392f, 0.439216f,  1.0f } */
        static const glm::vec4 MintCream;            /*!< Constant color { 0.960784f,  1.0f,       0.980392f,  1.0f } */
        static const glm::vec4 MistyRose;            /*!< Constant color { 1.0f,       0.894118f,  0.882353f,  1.0f } */
        static const glm::vec4 Moccasin;             /*!< Constant color { 1.0f,       0.894118f,  0.709804f,  1.0f } */
        static const glm::vec4 NavajoWhite;          /*!< Constant color { 1.0f,       0.870588f,  0.678431f,  1.0f } */
        static const glm::vec4 Navy;                 /*!< Constant color { 0.0f,       0.0f,       0.501961f,  1.0f } */
        static const glm::vec4 OldLace;              /*!< Constant color { 0.992157f,  0.960784f,  0.901961f,  1.0f } */
        static const glm::vec4 Olive;                /*!< Constant color { 0.501961f,  0.501961f,  0.0f,       1.0f } */
        static const glm::vec4 OliveDrab;            /*!< Constant color { 0.419608f,  0.556863f,  0.137255f,  1.0f } */
        static const glm::vec4 Orange;               /*!< Constant color { 1.0f,       0.647059f,  0.0f,       1.0f } */
        static const glm::vec4 OrangeRed;            /*!< Constant color { 1.0f,       0.270588f,  0.0f,       1.0f } */
        static const glm::vec4 Orchid;               /*!< Constant color { 0.854902f,  0.439216f,  0.839216f,  1.0f } */
        static const glm::vec4 PaleGoldenrod;        /*!< Constant color { 0.933333f,  0.909804f,  0.666667f,  1.0f } */
        static const glm::vec4 PaleGreen;            /*!< Constant color { 0.596078f,  0.984314f,  0.596078f,  1.0f } */
        static const glm::vec4 PaleTurquoise;        /*!< Constant color { 0.686275f,  0.933333f,  0.933333f,  1.0f } */
        static const glm::vec4 PaleVioletRed;        /*!< Constant color { 0.858824f,  0.439216f,  0.576471f,  1.0f } */
        static const glm::vec4 PapayaWhip;           /*!< Constant color { 1.0f,       0.937255f,  0.835294f,  1.0f } */
        static const glm::vec4 PeachPuff;            /*!< Constant color { 1.0f,       0.854902f,  0.72549f,   1.0f } */
        static const glm::vec4 Peru;                 /*!< Constant color { 0.803922f,  0.521569f,  0.247059f,  1.0f } */
        static const glm::vec4 Pink;                 /*!< Constant color { 1.0f,       0.752941f,  0.796079f,  1.0f } */
        static const glm::vec4 Plum;                 /*!< Constant color { 0.866667f,  0.627451f,  0.866667f,  1.0f } */
        static const glm::vec4 PowderBlue;           /*!< Constant color { 0.690196f,  0.878431f,  0.901961f,  1.0f } */
        static const glm::vec4 Purple;               /*!< Constant color { 0.501961f,  0.0f,       0.501961f,  1.0f } */
        static const glm::vec4 QuarterGray;          /*!< Constant color { 0.25f,      0.25f,      0.25f,      1.0f } */
        static const glm::vec4 Red;                  /*!< Constant color { 1.0f,       0.0f,       0.0f,       1.0f } */
        static const glm::vec4 RosyBrown;            /*!< Constant color { 0.737255f,  0.560784f,  0.560784f,  1.0f } */
        static const glm::vec4 RoyalBlue;            /*!< Constant color { 0.254902f,  0.411765f,  0.882353f,  1.0f } */
        static const glm::vec4 SaddleBrown;          /*!< Constant color { 0.545098f,  0.270588f,  0.0745098f, 1.0f } */
        static const glm::vec4 Salmon;               /*!< Constant color { 0.980392f,  0.501961f,  0.447059f,  1.0f } */
        static const glm::vec4 SandyBrown;           /*!< Constant color { 0.956863f,  0.643137f,  0.376471f,  1.0f } */
        static const glm::vec4 SeaGreen;             /*!< Constant color { 0.180392f,  0.545098f,  0.341176f,  1.0f } */
        static const glm::vec4 SeaShell;             /*!< Constant color { 1.0f,       0.960784f,  0.933333f,  1.0f } */
        static const glm::vec4 Sienna;               /*!< Constant color { 0.627451f,  0.321569f,  0.176471f,  1.0f } */
        static const glm::vec4 Silver;               /*!< Constant color { 0.752941f,  0.752941f,  0.752941f,  1.0f } */
        static const glm::vec4 SkyBlue;              /*!< Constant color { 0.529412f,  0.807843f,  0.921569f,  1.0f } */
        static const glm::vec4 SlateBlue;            /*!< Constant color { 0.415686f,  0.352941f,  0.803922f,  1.0f } */
        static const glm::vec4 SlateGray;            /*!< Constant color { 0.439216f,  0.501961f,  0.564706f,  1.0f } */
        static const glm::vec4 Snow;                 /*!< Constant color { 1.0f,       0.980392f,  0.980392f,  1.0f } */
        static const glm::vec4 SpringGreen;          /*!< Constant color { 0.0f,       1.0f,       0.498039f,  1.0f } */
        static const glm::vec4 SteelBlue;            /*!< Constant color { 0.27451f,   0.509804f,  0.705882f,  1.0f } */
        static const glm::vec4 Tan;                  /*!< Constant color { 0.823529f,  0.705882f,  0.54902f,   1.0f } */
        static const glm::vec4 Teal;                 /*!< Constant color { 0.0f,       0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 ThirdGray;            /*!< Constant color { 0.3f,       0.3f,       0.3f,       1.0f } */
        static const glm::vec4 Thistle;              /*!< Constant color { 0.847059f,  0.74902f,   0.847059f,  1.0f } */
        static const glm::vec4 Tomato;               /*!< Constant color { 1.0f,       0.388235f,  0.278431f,  1.0f } */
        static const glm::vec4 Turquoise;            /*!< Constant color { 0.25098f,   0.878431f,  0.815686f,  1.0f } */
        static const glm::vec4 Violet;               /*!< Constant color { 0.933333f,  0.509804f,  0.933333f,  1.0f } */
        static const glm::vec4 Wheat;                /*!< Constant color { 0.960784f,  0.870588f,  0.701961f,  1.0f } */
        static const glm::vec4 WhiteSmoke;           /*!< Constant color { 0.960784f,  0.960784f,  0.960784f,  1.0f } */
        static const glm::vec4 Yellow;               /*!< Constant color { 1.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 YellowGreen;          /*!< Constant color { 0.603922f,  0.803922f,  0.196078f,  1.0f } */
    };

    const glm::vec4 ColorConstants<void>::White                { 1.0f,       1.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Black                { 0.0f,       0.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Transparent          { 0.0f,       0.0f,       0.0f,       0.0f };
    const glm::vec4 ColorConstants<void>::AliceBlue            { 0.941177f,  0.972549f,  1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::AntiqueWhite         { 0.980392f,  0.921569f,  0.843137f,  1.0f };
    const glm::vec4 ColorConstants<void>::Aqua                 { 0.0f,       1.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Aquamarine           { 0.498039f,  1.0f,       0.831373f,  1.0f };
    const glm::vec4 ColorConstants<void>::Azure                { 0.941177f,  1.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Beige                { 0.960784f,  0.960784f,  0.862745f,  1.0f };
    const glm::vec4 ColorConstants<void>::Bisque               { 1.0f,       0.894118f,  0.768628f,  1.0f };
    const glm::vec4 ColorConstants<void>::BlanchedAlmond       { 1.0f,       0.921569f,  0.803922f,  1.0f };
    const glm::vec4 ColorConstants<void>::Blue                 { 0.0f,       0.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::BlueViolet           { 0.541176f,  0.168627f,  0.886275f,  1.0f };
    const glm::vec4 ColorConstants<void>::Brown                { 0.647059f,  0.164706f,  0.164706f,  1.0f };
    const glm::vec4 ColorConstants<void>::BurlyWood            { 0.870588f,  0.721569f,  0.529412f,  1.0f };
    const glm::vec4 ColorConstants<void>::CadetBlue            { 0.372549f,  0.619608f,  0.627451f,  1.0f };
    const glm::vec4 ColorConstants<void>::Chartreuse           { 0.498039f,  1.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Chocolate            { 0.823529f,  0.411765f,  0.117647f,  1.0f };
    const glm::vec4 ColorConstants<void>::Coral                { 1.0f,       0.498039f,  0.313726f,  1.0f };
    const glm::vec4 ColorConstants<void>::CornflowerBlue       { 0.392157f,  0.584314f,  0.929412f,  1.0f };
    const glm::vec4 ColorConstants<void>::Cornsilk             { 1.0f,       0.972549f,  0.862745f,  1.0f };
    const glm::vec4 ColorConstants<void>::Crimson              { 0.862745f,  0.0784314f, 0.235294f,  1.0f };
    const glm::vec4 ColorConstants<void>::Cyan                 { 0.0f,       1.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::DarkBlue             { 0.0f,       0.0f,       0.545098f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkCyan             { 0.0f,       0.545098f,  0.545098f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkGoldenrod        { 0.721569f,  0.52549f,   0.0431373f, 1.0f };
    const glm::vec4 ColorConstants<void>::DarkGray             { 0.662745f,  0.662745f,  0.662745f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkGreen            { 0.0f,       0.392157f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::DarkKhaki            { 0.741176f,  0.717647f,  0.419608f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkMagenta          { 0.545098f,  0.0f,       0.545098f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkOliveGreen       { 0.333333f,  0.419608f,  0.184314f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkOrange           { 1.0f,       0.54902f,   0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::DarkOrchid           { 0.6f,       0.196078f,  0.8f,       1.0f };
    const glm::vec4 ColorConstants<void>::DarkRed              { 0.545098f,  0.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::DarkSalmon           { 0.913726f,  0.588235f,  0.478431f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkSeaGreen         { 0.560784f,  0.737255f,  0.545098f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkSlateBlue        { 0.282353f,  0.239216f,  0.545098f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkSlateGray        { 0.184314f,  0.309804f,  0.309804f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkTurquoise        { 0.0f,       0.807843f,  0.819608f,  1.0f };
    const glm::vec4 ColorConstants<void>::DarkViolet           { 0.580392f,  0.0f,       0.827451f,  1.0f };
    const glm::vec4 ColorConstants<void>::DeepPink             { 1.0f,       0.0784314f, 0.576471f,  1.0f };
    const glm::vec4 ColorConstants<void>::DeepSkyBlue          { 0.0f,       0.74902f,   1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::DimGray              { 0.411765f,  0.411765f,  0.411765f,  1.0f };
    const glm::vec4 ColorConstants<void>::DodgerBlue           { 0.117647f,  0.564706f,  1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Firebrick            { 0.698039f,  0.133333f,  0.133333f,  1.0f };
    const glm::vec4 ColorConstants<void>::FloralWhite          { 1.0f,       0.980392f,  0.941177f,  1.0f };
    const glm::vec4 ColorConstants<void>::ForestGreen          { 0.133333f,  0.545098f,  0.133333f,  1.0f };
    const glm::vec4 ColorConstants<void>::Fuchsia              { 1.0f,       0.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Gainsboro            { 0.862745f,  0.862745f,  0.862745f,  1.0f };
    const glm::vec4 ColorConstants<void>::GhostWhite           { 0.972549f,  0.972549f,  1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::GearsBlue            { 0.2f,       0.2f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::GearsGreen           { 0.0f,       0.8f,       0.2f,       1.0f };
    const glm::vec4 ColorConstants<void>::GearsRed             { 0.8f,       0.1f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Gold                 { 1.0f,       0.843137f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Goldenrod            { 0.854902f,  0.647059f,  0.12549f,   1.0f };
    const glm::vec4 ColorConstants<void>::Gray                 { 0.501961f,  0.501961f,  0.501961f,  1.0f };
    const glm::vec4 ColorConstants<void>::Green                { 0.0f,       1.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::GreenYellow          { 0.678431f,  1.0f,       0.184314f,  1.0f };
    const glm::vec4 ColorConstants<void>::HalfGray             { 0.5f,       0.5f,       0.5f,       1.0f };
    const glm::vec4 ColorConstants<void>::Honeydew             { 0.941177f,  1.0f,       0.941177f,  1.0f };
    const glm::vec4 ColorConstants<void>::HotPink              { 1.0f,       0.411765f,  0.705882f,  1.0f };
    const glm::vec4 ColorConstants<void>::IndianRed            { 0.803922f,  0.360784f,  0.360784f,  1.0f };
    const glm::vec4 ColorConstants<void>::Indigo               { 0.294118f,  0.0f,       0.509804f,  1.0f };
    const glm::vec4 ColorConstants<void>::Ivory                { 1.0f,       1.0f,       0.941177f,  1.0f };
    const glm::vec4 ColorConstants<void>::Khaki                { 0.941177f,  0.901961f,  0.54902f,   1.0f };
    const glm::vec4 ColorConstants<void>::Lavender             { 0.901961f,  0.901961f,  0.980392f,  1.0f };
    const glm::vec4 ColorConstants<void>::LavenderBlush        { 1.0f,       0.941177f,  0.960784f,  1.0f };
    const glm::vec4 ColorConstants<void>::LawnGreen            { 0.486275f,  0.988235f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::LemonChiffon         { 1.0f,       0.980392f,  0.803922f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightBlue            { 0.678431f,  0.847059f,  0.901961f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightCoral           { 0.941177f,  0.501961f,  0.501961f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightCyan            { 0.878431f,  1.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::LightGoldenrodYellow { 0.980392f,  0.980392f,  0.823529f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightGray            { 0.827451f,  0.827451f,  0.827451f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightGreen           { 0.564706f,  0.933333f,  0.564706f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightPink            { 1.0f,       0.713726f,  0.756863f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightSalmon          { 1.0f,       0.627451f,  0.478431f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightSeaGreen        { 0.12549f,   0.698039f,  0.666667f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightSkyBlue         { 0.529412f,  0.807843f,  0.980392f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightSlateGray       { 0.466667f,  0.533333f,  0.6f,       1.0f };
    const glm::vec4 ColorConstants<void>::LightSteelBlue       { 0.690196f,  0.768628f,  0.870588f,  1.0f };
    const glm::vec4 ColorConstants<void>::LightYellow          { 1.0f,       1.0f,       0.878431f,  1.0f };
    const glm::vec4 ColorConstants<void>::Lime                 { 0.0f,       1.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::LimeGreen            { 0.196078f,  0.803922f,  0.196078f,  1.0f };
    const glm::vec4 ColorConstants<void>::Linen                { 0.980392f,  0.941177f,  0.901961f,  1.0f };
    const glm::vec4 ColorConstants<void>::Magenta              { 1.0f,       0.0f,       1.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Maroon               { 0.501961f,  0.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::MediumAquamarine     { 0.4f,       0.803922f,  0.666667f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumBlue           { 0.0f,       0.0f,       0.803922f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumOrchid         { 0.729412f,  0.333333f,  0.827451f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumPurple         { 0.576471f,  0.439216f,  0.858824f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumSeaGreen       { 0.235294f,  0.701961f,  0.443137f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumSlateBlue      { 0.482353f,  0.407843f,  0.933333f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumSpringGreen    { 0.0f,       0.980392f,  0.603922f,  1.0f };
    const glm::vec4 ColorConstants<void>::MediumTurquoise      { 0.282353f,  0.819608f,  0.8f,       1.0f };
    const glm::vec4 ColorConstants<void>::MediumVioletRed      { 0.780392f,  0.0823529f, 0.521569f,  1.0f };
    const glm::vec4 ColorConstants<void>::MidnightBlue         { 0.0980392f, 0.0980392f, 0.439216f,  1.0f };
    const glm::vec4 ColorConstants<void>::MintCream            { 0.960784f,  1.0f,       0.980392f,  1.0f };
    const glm::vec4 ColorConstants<void>::MistyRose            { 1.0f,       0.894118f,  0.882353f,  1.0f };
    const glm::vec4 ColorConstants<void>::Moccasin             { 1.0f,       0.894118f,  0.709804f,  1.0f };
    const glm::vec4 ColorConstants<void>::NavajoWhite          { 1.0f,       0.870588f,  0.678431f,  1.0f };
    const glm::vec4 ColorConstants<void>::Navy                 { 0.0f,       0.0f,       0.501961f,  1.0f };
    const glm::vec4 ColorConstants<void>::OldLace              { 0.992157f,  0.960784f,  0.901961f,  1.0f };
    const glm::vec4 ColorConstants<void>::Olive                { 0.501961f,  0.501961f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::OliveDrab            { 0.419608f,  0.556863f,  0.137255f,  1.0f };
    const glm::vec4 ColorConstants<void>::Orange               { 1.0f,       0.647059f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::OrangeRed            { 1.0f,       0.270588f,  0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::Orchid               { 0.854902f,  0.439216f,  0.839216f,  1.0f };
    const glm::vec4 ColorConstants<void>::PaleGoldenrod        { 0.933333f,  0.909804f,  0.666667f,  1.0f };
    const glm::vec4 ColorConstants<void>::PaleGreen            { 0.596078f,  0.984314f,  0.596078f,  1.0f };
    const glm::vec4 ColorConstants<void>::PaleTurquoise        { 0.686275f,  0.933333f,  0.933333f,  1.0f };
    const glm::vec4 ColorConstants<void>::PaleVioletRed        { 0.858824f,  0.439216f,  0.576471f,  1.0f };
    const glm::vec4 ColorConstants<void>::PapayaWhip           { 1.0f,       0.937255f,  0.835294f,  1.0f };
    const glm::vec4 ColorConstants<void>::PeachPuff            { 1.0f,       0.854902f,  0.72549f,   1.0f };
    const glm::vec4 ColorConstants<void>::Peru                 { 0.803922f,  0.521569f,  0.247059f,  1.0f };
    const glm::vec4 ColorConstants<void>::Pink                 { 1.0f,       0.752941f,  0.796079f,  1.0f };
    const glm::vec4 ColorConstants<void>::Plum                 { 0.866667f,  0.627451f,  0.866667f,  1.0f };
    const glm::vec4 ColorConstants<void>::PowderBlue           { 0.690196f,  0.878431f,  0.901961f,  1.0f };
    const glm::vec4 ColorConstants<void>::Purple               { 0.501961f,  0.0f,       0.501961f,  1.0f };
    const glm::vec4 ColorConstants<void>::QuarterGray          { 0.25f,      0.25f,      0.25f,      1.0f };
    const glm::vec4 ColorConstants<void>::Red                  { 1.0f,       0.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::RosyBrown            { 0.737255f,  0.560784f,  0.560784f,  1.0f };
    const glm::vec4 ColorConstants<void>::RoyalBlue            { 0.254902f,  0.411765f,  0.882353f,  1.0f };
    const glm::vec4 ColorConstants<void>::SaddleBrown          { 0.545098f,  0.270588f,  0.0745098f, 1.0f };
    const glm::vec4 ColorConstants<void>::Salmon               { 0.980392f,  0.501961f,  0.447059f,  1.0f };
    const glm::vec4 ColorConstants<void>::SandyBrown           { 0.956863f,  0.643137f,  0.376471f,  1.0f };
    const glm::vec4 ColorConstants<void>::SeaGreen             { 0.180392f,  0.545098f,  0.341176f,  1.0f };
    const glm::vec4 ColorConstants<void>::SeaShell             { 1.0f,       0.960784f,  0.933333f,  1.0f };
    const glm::vec4 ColorConstants<void>::Sienna               { 0.627451f,  0.321569f,  0.176471f,  1.0f };
    const glm::vec4 ColorConstants<void>::Silver               { 0.752941f,  0.752941f,  0.752941f,  1.0f };
    const glm::vec4 ColorConstants<void>::SkyBlue              { 0.529412f,  0.807843f,  0.921569f,  1.0f };
    const glm::vec4 ColorConstants<void>::SlateBlue            { 0.415686f,  0.352941f,  0.803922f,  1.0f };
    const glm::vec4 ColorConstants<void>::SlateGray            { 0.439216f,  0.501961f,  0.564706f,  1.0f };
    const glm::vec4 ColorConstants<void>::Snow                 { 1.0f,       0.980392f,  0.980392f,  1.0f };
    const glm::vec4 ColorConstants<void>::SpringGreen          { 0.0f,       1.0f,       0.498039f,  1.0f };
    const glm::vec4 ColorConstants<void>::SteelBlue            { 0.27451f,   0.509804f,  0.705882f,  1.0f };
    const glm::vec4 ColorConstants<void>::Tan                  { 0.823529f,  0.705882f,  0.54902f,   1.0f };
    const glm::vec4 ColorConstants<void>::Teal                 { 0.0f,       0.501961f,  0.501961f,  1.0f };
    const glm::vec4 ColorConstants<void>::ThirdGray            { 0.3f,       0.3f,       0.3f,       1.0f };
    const glm::vec4 ColorConstants<void>::Thistle              { 0.847059f,  0.74902f,   0.847059f,  1.0f };
    const glm::vec4 ColorConstants<void>::Tomato               { 1.0f,       0.388235f,  0.278431f,  1.0f };
    const glm::vec4 ColorConstants<void>::Turquoise            { 0.25098f,   0.878431f,  0.815686f,  1.0f };
    const glm::vec4 ColorConstants<void>::Violet               { 0.933333f,  0.509804f,  0.933333f,  1.0f };
    const glm::vec4 ColorConstants<void>::Wheat                { 0.960784f,  0.870588f,  0.701961f,  1.0f };
    const glm::vec4 ColorConstants<void>::WhiteSmoke           { 0.960784f,  0.960784f,  0.960784f,  1.0f };
    const glm::vec4 ColorConstants<void>::Yellow               { 1.0f,       1.0f,       0.0f,       1.0f };
    const glm::vec4 ColorConstants<void>::YellowGreen          { 0.603922f,  0.803922f,  0.196078f,  1.0f };

} // namespace detail

    /*
    * Represents a 4 channel color.
    */
    struct Color
        : public glm::vec4
        , public detail::ColorConstants<void>
    {
    };

} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

namespace Dynamic_Static {

    typedef struct Radians { } radians; /*!< Radians tag for functions operating on angles */
    typedef struct Degrees { } degrees; /*!< Degrees tag for functions operating on angles */

    /*
    * Wraps an angle to the range [0, 2Pi].
    * @param [in] angle The angle to wrap
    * @param [tag dispatch dst::radians]
    * @return The wrapped angle
    */
    template <typename T>
    inline T wrap_angle(const T& angle, const Radians&)
    {
        T twoPi = static_cast<T>(M_PI * 2);
        T wrappedAngle = std::fmod(angle, twoPi);
        return wrappedAngle < 0 ? wrappedAngle : wrappedAngle + twoPi;
    }

    /*
    * Gets the world left vector; (-1, 0), (-1, 0, 0), or (-1, 0, 0, 0).
    * @return The world left vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_left()
    {
        VectorType v { };
        v.x = -1;
        return v;
    }

    /*
    * Gets the world right vector; (1, 0), (1, 0, 0), or (1, 0, 0, 0).
    * @return The world right vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_right()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /*
    * Gets the world up vector; (0, 1), (0, 1, 0), or (0, 1, 0, 0).
    * @return The world up vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_up()
    {
        VectorType v { };
        v.y = 1;
        return v;
    }

    /*
    * Gets the world down vector; (0, -1), (0, -1, 0), or (0, -1, 0, 0).
    * @return The world down vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_down()
    {
        VectorType v { };
        v.y = -1;
        return v;
    }

    /*
    * Gets the world forward vector; (0, 0, -1) or (0, 0, -1, 0).
    * @return The world forward vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_forward()
    {
        VectorType v { };
        v.z = -1;
        return v;
    }

    /*
    * Gets the world backward vector; (0, 0, 1) or (0, 0, 1, 0).
    * @return The world backward vector
    */
    template <typename VectorType>
    inline constexpr VectorType world_backward()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /*
    * Gets a 2, 3, or 4 component vector with its x component set to 1; (1, 0), (1, 0, 0), or (1, 0, 0, 0).
    * @return The 2, 3, or 4 component vector with its x component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_x()
    {
        VectorType v { };
        v.x = 1;
        return v;
    }

    /*
    * Gets a 2, 3, or 4 component vector with its y component set to 1; (0, 1), (0, 1, 0), or (0, 1, 0, 0).
    * @return The 2, 3, or 4 component vector with its y component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_y()
    {
        VectorType v { };
        v.y = 1;
        return v;
    }

    /*
    * Gets a 3 or 4 component vector with its z component set to 1; (0, 0, 1) or (0, 0, 1, 0).
    * @return The 3 or 4 component vector with its z component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_z()
    {
        VectorType v { };
        v.z = 1;
        return v;
    }

    /*
    * Gets a 4 component vector with its w component set to 1; (0, 0, 0, 1).
    * @return The 4 component vector with its w component set to 1
    */
    template <typename VectorType>
    inline constexpr VectorType unit_w()
    {
        VectorType v { };
        v.w = 1;
        return v;
    }

} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

namespace Dynamic_Static {

    /*
    * Represents a position, rotation, and scale.
    */
    struct Transform final
    {
        glm::vec3 translation { };
        glm::quat rotation { 1, 0, 0, 0 };
        glm::vec3 scale { 1 };

        /*
        * Gets a glm::mat4 representing this Transform's world from local matrix.
        * @return A glm::mat4 representing this Transform's world from local matrix
        */
        inline glm::mat4 world_from_local() const
        {
            return
                glm::translate(translation) *
                glm::toMat4(rotation) *
                glm::scale(scale);
        }

        /*
        * Gets a glm::mat4 representing this Transform's local from world matrix.
        * @return A glm::mat4 representing this Transform's local from world matrix
        */
        inline glm::mat4 local_from_world() const
        {
            return glm::transpose(world_from_local());
        }

        /*
        * Gets a glm::vec3 representing this Transform's up vector in world space.
        * @return A glm::vec3 representing this Transform's up vector in world space
        */
        inline glm::vec3 up() const
        {
            return glm::normalize(rotation * dst::world_up<glm::vec3>());
        }

        /*
        * Gets a glm::vec3 representing this Transform's down vector in world space.
        * @return A glm::vec3 representing this Transform's down vector in world space
        */
        inline glm::vec3 down() const
        {
            return glm::normalize(rotation * dst::world_down<glm::vec3>());
        }

        /*
        * Gets a glm::vec3 representing this Transform's left vector in world space.
        * @return A glm::vec3 representing this Transform's left vector in world space
        */
        inline glm::vec3 left() const
        {
            return glm::normalize(rotation * dst::world_left<glm::vec3>());
        }

        /*
        * Gets a glm::vec3 representing this Transform's right vector in world space.
        * @return A glm::vec3 representing this Transform's right vector in world space
        */
        inline glm::vec3 right() const
        {
            return glm::normalize(rotation * dst::world_right<glm::vec3>());
        }

        /*
        * Gets a glm::vec3 representing this Transform's forward vector in world space.
        * @return A glm::vec3 representing this Transform's forward vector in world space
        */
        inline glm::vec3 forward() const
        {
            return glm::normalize(rotation * dst::world_forward<glm::vec3>());
        }

        /*
        * Gets a glm::vec3 representing this Transform's backward vector in world space.
        * @return A glm::vec3 representing this Transform's backward vector in world space
        */
        inline glm::vec3 backward() const
        {
            return glm::normalize(rotation * dst::world_backward<glm::vec3>());
        }
    };

} // namespace Dynamic_Static

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED

namespace Dynamic_Static {

    /*
    * Provides a Callback<> for move notification.
    */
    template <typename T>
    class MoveNotifier
    {
    public:
        /*
        * Callback<> executed when this MoveNotifier is moved.
        * @param [in] (MoveNotifier*) The address moved to
        * @param [in] (MoveNotifier*) The address moved from
        */
        Callback<MoveNotifier<T>, MoveNotifier<T>*, MoveNotifier<T>*> on_move;

    public:
        /*
        * Constructs an instance of MoveNotifier<T>.
        */
        MoveNotifier() = default;

        /*
        * Moves this instance of MoveNotifier.
        * @param [in] other The MoveNotifier to move from
        */
        MoveNotifier(MoveNotifier<T>&& other)
        {
            *this = std::move(other);
        }

        /*
        * Moves this instance of MoveNotifier.
        * @param [in] other The MoveNotifier to move from
        * @return This MoveNotifier
        */
        MoveNotifier<T>& operator=(MoveNotifier<T>&& other)
        {
            if (this != &other) {
                on_move = std::move(other);
                other.on_move = nullptr;
                on_move(this, &other);
            }
            return *this;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides an inheritable interface for std::enable_shared_from_this.
    */
    template <typename CRTP>
    class SharedObject
        : public std::enable_shared_from_this<CRTP>
    {
    public:
        /*
        * Gets a std::shared_ptr<> to this SharedObject.
        * @return An std::shared_ptr<> to this SharedObject
        */
        inline std::shared_ptr<CRTP> get_shared_ptr()
        {
            return shared_from_this();
        }

        /*
        * Gets a std::shared_ptr<const> to this SharedObject.
        * @return An std::shared_ptr<const> to this SharedObject
        */
        inline std::shared_ptr<const CRTP> get_shared_ptr() const
        {
            return shared_from_this();
        }

        /*
        * Gets a std::weak_ptr<> to this SharedObject.
        * @return An std::weak_ptr<> to this SharedObject
        */
        inline std::weak_ptr<CRTP> get_weak_ptr()
        {
            return weak_from_this();
        }

        /*
        * Gets a std::weak_ptr<const> to this SharedObject.
        * @return An std::weak_ptr<const> to this SharedObject
        */
        inline std::weak_ptr<const CRTP> get_weak_ptr() const
        {
            return weak_from_this();
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides high level control over random number generation.
    */
    class RandomNumberGenerator final
    {
    private:
        uint32_t mSeed { 0 };
        std::mt19937_64 mEngine;
        std::uniform_real_distribution<double> mRealDistribution { 0., 1. };
        std::uniform_int_distribution<uint64_t> mIntDistribution { 0, std::numeric_limits<uint64_t>::max() };

    public:
        /*
        * Constructs a new instance of RandomNumberGenerator.
        */
        inline RandomNumberGenerator()
            : RandomNumberGenerator(std::random_device()())
        {
        }

        /*
        * Constructs a new instance of RandomNumberGenerator with a given seed.
        * @param [in] seed This RandomNumberGenerator's seed
        */
        inline RandomNumberGenerator(uint32_t seed)
        {
            set_seed(seed);
        }

    public:
        /*
        * Gets this RandomNumberGenerator's seed.
        * @return This RandomNumberGenerator's seed
        */
        inline uint32_t get_seed() const
        {
            return mSeed;
        }

        /*
        * Sets this RandomNumberGenerator's seed.
        * \n NOTE : Calling this method will reset this RandomNumberGenerator
        * @param [in] This RandomNumberGenerator's seed
        */
        inline void set_seed(uint32_t seed)
        {
            mSeed = seed;
            reset();
        }

        /*
        * Resets this RandomNumberGenerator.
        */
        inline void reset()
        {
            mEngine.seed(mSeed);
            mRealDistribution.reset();
            mIntDistribution.reset();
        }

        /*
        * Generates a random in the range of two given values.
        * @param <IntegerType> The type of the value
        * @param [in] min The lower bound of the range [inclusive]
        * @param [in] max The upper bound of the range (exclusive)
        * @return The generated value
        */
        template <typename IntegerType>
        inline typename std::enable_if<std::is_integral<IntegerType>::value, IntegerType>::type
            range(IntegerType min, IntegerType max)
        {
            return static_cast<IntegerType>(mIntDistribution(mEngine) % (max - min) + min);
        }

        /*
        * Generates a random value in the range of two given values.
        * @param <IntegerType> The type of the value
        * @param [in] min The lower bound of the range [inclusive]
        * @param [in] max The upper bound of the range (exclusive)
        * @return The generated value
        */
        template <typename FloatingPointType>
        inline typename std::enable_if<std::is_floating_point<FloatingPointType>::value, FloatingPointType>::type
            range(FloatingPointType min, FloatingPointType max)
        {
            return static_cast<FloatingPointType>(mRealDistribution(mEngine) * (max - min) + min);
        }

        /*
        * Generates a random value in a given type's range.
        * @param <T> The type of the value
        * @return The generated value
        */
        template <typename T>
        inline T value()
        {
            return range<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        }

        /*
        * Has a chance of returning true based on a given value.
        * @param [in] value The value (0 - 100] to test
        * @return Whether or not the value passed
        */
        template <typename IntegerType>
        inline bool probability(
            IntegerType value,
            typename std::enable_if<std::is_integral<IntegerType>::value, IntegerType>::type* = nullptr
        )
        {
            return value >= range<IntegerType>(1, 101);
        }

        /*
        * Has a chance of returning true based on a given value.
        * @param [in] value The floating point value (0 - 1] to test
        * @return Whether or not the value passed
        */
        template <typename FloatingPointType>
        inline bool probability(
            FloatingPointType value,
            typename std::enable_if<std::is_floating_point<FloatingPointType>::value, FloatingPointType>::type* = nullptr
        )
        {
            return value >= range<FloatingPointType>(std::numeric_limits<FloatingPointType>::epsilon(), 1.);
        }

        /*
        * Generates a random index for a collection with a given count.
        * @param [in] count The number of elements in the collection
        * @return The generated index
        */
        template <typename IntegerType>
        inline IntegerType index(IntegerType count)
        {
            static_assert(
                std::is_integral<IntegerType>::value,
                "dst::RandomNumberGenerator::index() can only be used with integer types"
            );
            return count ? range<IntegerType>(0, count) : 0;
        }

        /*
        * Generates a roll from a die with a given number of sides.
        * @param [in] D The number of sides on the die
        * @return The result of the die roll
        */
        template <typename IntegerType>
        inline IntegerType die_roll(IntegerType D)
        {
            static_assert(
                std::is_integral<IntegerType>::value,
                "dst::RandomNumberGenerator::die_roll() can only be used with integer types"
            );
            return D >= 1 ? range<IntegerType>(1, D + 1) : 0;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Provides a non-owning reference to a contiguous sequence of char-like objects.
    */
    class StringView
        : public std::string_view
    {
    public:
        /*
        * Constructs an instance of dst::string_view.
        * @param [in] strView The std::string_view to reference
        */
        StringView(const std::string_view& strView)
            : std::string_view(strView)
        {
        }

        /*
        * Constructs an instance of dst::string_view.
        * @param [in] strView The std::string to reference
        */
        StringView(const std::string& str)
            : std::string_view(str)
        {
        }

        /*
        * Constructs an instance of dst::string_view.
        * @param [in] strView The const char* to reference
        */
        StringView(const char* cStr)
            : std::string_view(cStr, cStr ? strlen(cStr) : 0)
        {
        }

        /*
        * Constructs an instance of dst::string_view.
        * @param [in] strView The char to reference
        */
        StringView(const char& c)
            : std::string_view(&c, 1)
        {
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Gets a value indicating whether or not a given string contains another given string.
    * @param [in] str The string to search
    * @param [in] find The string to find
    * @param [in] offset The offset to start searching from (optional = 0)
    */
    inline bool contains(
        const dst::StringView& str,
        const dst::StringView& find,
        size_t offset = 0
    )
    {
        return str.find(find, offset) != std::string::npos;
    }

    /*
    * Gets a copy of an std::string with all occurences of a given substring replaced with another.
    * @param [in] str The source string
    * @param [in] find The string to find and replace in the source string
    * @param [in] replacement The string to replace found occurences with
    * @param [in] recursive (default = false) Whether or not to recursively replace occurences of the find string
    * @return The resulting string
    */
    inline std::string replace(
        const dst::StringView& str,
        const dst::StringView& find,
        const dst::StringView& replacement,
        bool recursive = false
    )
    {
        std::string result(str.begin(), str.end());
        if (!find.empty() && find != replacement) {
            auto index = result.find(find);
            while (index != std::string::npos) {
                result.replace(index, find.size(), replacement);
                index += recursive ? 0 : replacement.size();
                index = result.find(find, index);
            }
        }
        return result;
    }

    /*
    * Gets a copy of an std::string with all occurences of a given substring removed.
    * @param [in] str The source string
    * @param [in] find The string to find and remove from the source string
    * @param [in] recursive (default = false) Whether or not to recursively remove occurences of the find string
    * @return The resulting string
    */
    inline std::string remove(
        const dst::StringView& str,
        const dst::StringView& find,
        bool recursive = false
    )
    {
        return dst::replace(str, find, nullptr, recursive);
    }

    /*
    * Gets a copy of an std::string with all repetitive occurences of a given substring reduced to single occurences.
    * @param [in] str The source string
    * @param [in] find The string to find and reduce
    * @return The resulting string
    */
    inline std::string reduce_sequence(
        const dst::StringView& str,
        const dst::StringView& find
    )
    {
        std::string sequence(find.begin(), find.end());
        return dst::replace(str, sequence + sequence, find, true);
    }

    /*
    * Gets a copy of an std::string containing a path with back slashes replaced with forward slashes and slash sequences reduced.
    * @param [in] path The path to scrub
    * @reutrn The scrubbed path
    */
    inline std::string scrub_path(dst::StringView path)
    {
        return dst::reduce_sequence(dst::replace(path, '\\', '/'), '/');
    }

    /*
    * Gets an std::vector<std::string> populated with substrings of a given string using a given delimiter.
    * @param [in] str The string to search for delimiters
    * @param [in] delimiter The delimiter to search for
    * @return An std::vector<std::string> populated with split tokens
    */
    inline std::vector<std::string> split(
        const dst::StringView& str,
        const dst::StringView& delimiter
    )
    {
        std::vector<std::string> tokens;
        if (!str.empty() && !delimiter.empty()) {
            size_t index = 0;
            size_t offset = 0;
            while ((index = str.find(delimiter, offset)) != std::string::npos) {
                if (index - offset > 0) {
                    tokens.push_back(std::string(str.substr(offset, index - offset)));
                }
                offset = index + delimiter.size();
            }
            if (offset < str.length()) {
                tokens.push_back(std::string(str.substr(offset, str.length() - offset)));
            }
        }
        return tokens;
    }

    /*
    * Gets the upper case version of a given char.
    * @param [in] c The char to convert to upper case
    * @return The resulting char
    */
    inline char to_upper(char c)
    {
        return static_cast<char>(std::toupper(static_cast<int>(c)));
    }

    /*
    * Gets a copy of an std::string with all characters converted to upper case.
    * @param [in] str The string to convert to upper case
    * @return The resulting string
    */
    inline std::string to_upper(const dst::StringView& str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_upper(c);
        }
        return result;
    }

    /*
    * Gets the lower case version of a given char.
    * @param [in] c The char to convert to lower case
    * @return The resulting char
    */
    inline char to_lower(char c)
    {
        return static_cast<char>(std::tolower(static_cast<int>(c)));
    }

    /*
    * Gets a copy of an std::string with all characters converted to lower case.
    * @param [in] str The string to convert to lower case
    * @return The resulting string
    */
    inline std::string to_lower(dst::StringView str)
    {
        std::string result(str.begin(), str.end());
        for (auto& c : result) {
            c = dst::to_lower(c);
        }
        return result;
    }

    /*
    * Gets the std::string representation of the hex value of a given integral value.
    * @param <T> The type of the given value
    * @return The string representation of the hex value of the given integral value
    */
    template <typename T>
    inline std::string to_hex_string(const T& value)
    {
        static_assert(
            std::is_integral<T>::value,
            "dst::to_hex_string() can only be used with integer types"
        );
        std::stringstream strStr;
        strStr << "0x" << std::hex << value;
        return strStr.str();
    }

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Represents a Version with major, minor, and patch values.
    */
    struct Version final
    {
        /*
        * This Version's major value
        */
        int major { 0 };

        /*
        * This Version's minor value
        */
        int minor { 0 };

        /*
        * This Version's patch value
        */
        int patch { 0 };

        /*
        * Gets the std::string representation of this Version.
        * @return The std::string representation of this Version
        */
        inline std::string to_string() const
        {
            return
                std::to_string(major) + "." +
                std::to_string(minor) + "." +
                std::to_string(patch);
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /*
    * Populates a given std::vector<> with objects converted from another std::vector<> using a given conversion function.
    * @param <SourceType> The type of the source std::vector<>
    * @param <DestinationType> The type of the destination std::vector<>
    * @param <ConversionFunctionType> The type of the conversion function
    * @param [in] source The source std::vector<>
    * @param [out] destination The destination std::vector<>
    * @param [in] conversion The conversion function
    */
    template <
        typename SourceType,
        typename DestinationType,
        typename ConversionFunctionType
    >
    inline void convert(
        const std::vector<SourceType>& source,
        std::vector<DestinationType>& destination,
        ConversionFunctionType conversion
    )
    {
        destination.clear();
        destination.reserve(source.size());
        for (const auto& object : source) {
            destination.push_back(conversion(object));
        }
    }

    /*
    * Gets a std::vector<> populated with objects converted from another std::vector<> using a given conversion function.
    * @param <SourceType> The type of the source std::vector
    * @param <DestinationType> The type of the destination std::vector
    * @param <ConversionFunctionType> The type of the conversion function
    * @param [in] source The source std::vector<>
    * @param [in] conversion The conversion function
    * @return A std::vector<> containing the converted objects
    */
    template <
        typename SourceType,
        typename DestinationType,
        typename ConversionFunctionType
    >
    inline std::vector<DestinationType> convert(
        const std::vector<SourceType>& source,
        ConversionFunctionType conversion
    )
    {
        std::vector<DestinationType> destination;
        convert(source, destination, conversion);
        return destination;
    }

    /*
    * Removes duplicate elements from a given std::vector<>
    * \n NOTE : This function will sort the given std::vector
    * \n NOTE : The type of the given std::vector<> must provide operator< and operator==
    * \n        The type of the given std::vector<> must fulfill the Compare concept
    * \n        (http://en.cppreference.com/w/cpp/concept/Compare)
    * @param <T> T The type of the std::vector to remove duplicates from
    * @param [in, out] vctr The std::vector to remove duplicates from
    */
    template <typename T>
    inline void remove_duplicates(std::vector<T>& vctr)
    {
        std::sort(vctr.begin(), vctr.end());
        vctr.erase(std::unique(vctr.begin(), vctr.end()), vctr.end());
    }

} // namespace Dynamic_Static
