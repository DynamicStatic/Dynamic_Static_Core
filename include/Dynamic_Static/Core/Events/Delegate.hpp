
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

#include <utility>

namespace Dynamic_Static {

    /*!
    Encapsulates a Subscribable multicast Action<>.
    */
    template <typename ...Args>
    class Delegate
        : Subscribable
    {
    private:
        Action<Args...> mAction;

    public:
        /*!
        Constructs an instance of Delegate.
        */
        inline Delegate() = default;

        /*!
        Constructs an instance of Delegate.
        @param [in] action This Delegate's Action<>
        */
        inline Delegate(const Action<Args...>& action)
            : mAction { action }
        {
        }

        /*!
        Assigns this Delegate's Action<>.
        @return This Delegate
        */
        inline Delegate& operator=(const Action<Args...>& action)
        {
            mAction = action;
            return *this;
        }

        /*!
        Removes this Delegate's Action<> and all subscribers.
        \n NOTE : This method doesn't remove subscriptions
        @return This Delegate
        */
        inline Delegate& operator=(nullptr_t)
        {
            clear_subscribers();
            mAction = nullptr;
            return *this;
        }

        /*!
        Subscribes a given Delegate to this Delegate.
        @param [in] other The Delegate to subscribe to this Delegate
        @return This Delegate
        */
        inline Delegate& operator+=(Delegate<Args...>& other)
        {
            Subscribable::operator+=(other);
            return *this;
        }

        /*!
        Unsubscribes a given Delegate from this Delegate.
        @param [in] other The Delegate to unsubscribe from this Delegate
        @return This Delegate
        */
        inline Delegate& operator-=(Delegate<Args...>& other)
        {
            Subscribable::operator-=(other);
            return *this;
        }

        /*!
        Executes this Delegate.
        @param [in] args The arguments to execute this Delegate with
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

        /*!
        Gets a value indicating whether or not this Delegate has a valid Action<>.
        @return Whether or not this Delegate has a valid Action<>
        */
        inline operator bool() const
        {
            return mAction != nullptr;
        }

    public:
        /*!
        Gets this Delegate's subscribers.
        @return This Delegate's subscribers
        */
        inline const std::vector<Subscribable*>& get_subscribers() const
        {
            return Subscribable::get_subscribers();
        }

        /*!
        Gets this Delegate's subscriptions.
        @return This Delegate's subscrpitions
        */
        inline const std::vector<Subscribable*>& get_subscriptions() const
        {
            return Subscribable::get_subscriptions();
        }

        /*!
        Removes all of this Delegate's subscribers.
        */
        inline void clear_subscribers()
        {
            Subscribable::clear_subscribers();
        }

        /*!
        Removes all of this Delegate's subscriptions.
        */
        inline void clear_subscriptions()
        {
            Subscribable::clear_subscriptions();
        }

        /*!
        Removes all of this Delegate's subscriptions.
        */
        inline void clear()
        {
            Subscribable::clear();
        }
    };

} // namespace Dynamic_Static
