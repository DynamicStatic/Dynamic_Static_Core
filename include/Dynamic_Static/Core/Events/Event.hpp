
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Events/Delegate.hpp"
#include "Dynamic_Static/Core/Defines.hpp"

namespace dst {

    /*!
    Encapsulates a collection of Delegates<> that are callable by a given type.
    @param <CallerType> The type of object that can excute this Event
    @param <Args> This Event's argument types
    */
    template <typename CallerType, typename ...Args>
    class Event
        : Delegate<Args...>
    {
    public:
        /*!
        Constructs an instance of Event.
        */
        inline Event() = default;

        /*!
        Constructs an instance of Event.
        @param [in] action This Event's Action<>
        */
        inline Event(const Action<Args...>& action)
            : mAction { action }
        {
        }

        /*!
        Assigns this Event's Action<>.
        @return This Event
        */
        inline Event& operator=(const Action<Args...>& action)
        {
            Delegate<Args...>::operator=(action);
            return *this;
        }

        /*!
        Removes this Event's Action<> and all subscribers.
        \n NOTE : This method doesn't remove subscriptions
        @return This Event
        */
        inline Event& operator=(nullptr_t)
        {
            Delegate<Args...>::operator=(nullptr);
            return *this;
        }

        /*!
        Subscribes a given Delegate<> to this Event.
        @param [in] delegate The Delegate<> to subscribe to this Event
        @return This Event
        */
        inline Event<CallerType, Args...>& operator+=(Delegate<Args...>& delegate)
        {
            Delegate<Args...>::operator+=(delegate);
            return *this;
        }

        /*!
        Unsubscribes a given Delegate<> from this Event.
        @param [in] delegate The Delegate<> to unsubscribe from this Event
        @return This Event
        */
        inline Event<CallerType, Args...>& operator-=(Delegate<Args...>& delegate)
        {
            Delegate<Args...>::operator-=(delegate);
            return *this;
        }

    private:
        /*!
        Executes all of this Event's subscribed Delegates<>.
        \n NOTE : This method can only be called by an object of type CallerType
        @param [in] args The arguments to execute this Event with
        */
        inline void operator()(Args&&... args) const
        {
            Delegate<Args...>::operator()(std::forward<Args>(args)...);
        }

    public:
        /*!
        Gets this Event's subscribers.
        @return This Event's subscribers
        */
        inline const std::vector<dst::Subscribable*>& get_subscribers() const
        {
            return Delegate<Args...>::get_subscribers();
        }

    private:
        /*!
        Removes all of this Events's subscribers.
        \n NOTE : This method can only be called by an object of type CallerType
        */
        inline void clear()
        {
            Delegate<Args...>::clear();
        }

    private:
        friend CallerType;
    };

} // namespace dst
