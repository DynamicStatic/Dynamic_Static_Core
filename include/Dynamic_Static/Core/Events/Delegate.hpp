
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Events/Subscribable.hpp"
#include "Dynamic_Static/Core/Action.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <utility>

namespace Dynamic_Static {

    /*
    * Encapsulates a Subscribable multicast Action<>.
    */
    template <typename ...Args>
    class Delegate final
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
        * Removes this Delegate's Action<> and all subscriptions.
        * @return This Delegate
        */
        inline Delegate& operator=(nullptr_t)
        {
            Subscribable::clear();
            mAction = nullptr;
            return *this;
        }

        /*
        * Subscribes a given Delegate to this Delegate.
        * @param [in] other The Delegate to subscribe to this Delegate
        * @return This Delegate
        */
        Delegate& operator+=(Delegate<Args...>& other)
        {
            Subscribable::operator+=(other);
            return *this;
        }

        /*
        * Unsubscribes a given Delegate from this Delegate.
        * @param [in] other The Delegate to unsubscribe from this Delegate
        * @return This Delegate
        */
        Delegate& operator-=(Delegate<Args...>& other)
        {
            Subscribable::operator-=(other);
            return *this;
        }

        #if 1
        /*
        * Executes this Delegate.
        * @param [in] args The arguments to execute this Delegate with
        */
        inline void operator()(Args... args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
            for (auto subscription : Subscribable::get_subscriptions()) {
                const Delegate<Args...>& delegate = *reinterpret_cast<Delegate<Args...>*>(subscription);
                delegate(std::forward<Args>(args)...);
            }
        }
        #else
        /*
        * Executes this Delegate.
        * @param [in] args The arguments to execute this Delegate with
        */
        inline void operator()(Args&&... args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
            for (auto subscription : Subscribable::get_subscriptions()) {
                const Delegate<Args...>& delegate = *reinterpret_cast<Delegate<Args...>*>(subscription);
                delegate(std::forward<Args>(args)...);
            }
        }
        #endif

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
        * Removes all of this Delegate's subscriptions.
        */
        void clear()
        {
            Subscribable::clear();
        }
    };

} // namespace Dynamic_Static
