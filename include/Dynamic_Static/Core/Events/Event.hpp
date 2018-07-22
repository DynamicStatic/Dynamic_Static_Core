
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
#include "Dynamic_Static/Core/NonCopyable.hpp"

namespace Dynamic_Static {

    /*
    * Encapsulates a collection of Delegates<> that are callable by a given type.
    * @param <CallerType> The type of object that can excute this Event
    * @param <Args> This Event's argument types
    */
    template <typename CallerType, typename ...Args>
    class Event final
        : Delegate<Args...>
    {
    public:
        /*
        * Subscribes a given Delegate<> to this Event.
        * @param [in] delegate The Delegate<> to subscribe to this Event
        * @return This Event
        */
        Event<CallerType, Args...>& operator+=(Delegate<Args...>& delegate)
        {
            Delegate<Args...>::operator+=(delegate);
            return *this;
        }

        /*
        * Unsubscribes a given Delegate<> from this Event.
        * @param [in] delegate The Delegate<> to unsubscribe from this Event
        * @return This Event
        */
        Event<CallerType, Args...>& operator-=(Delegate<Args...>& delegate)
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
        void operator()(Args&&... args) const
        {
            for (auto subscription : Subscribable::get_subscriptions()) {
                const Delegate<Args...>& delegate = *reinterpret_cast<Delegate<Args...>*>(subscription);
                delegate(std::forward<Args>(args)...);
            }
        }

    private:
        /*
        * Removes all Delegates<> from this Event.
        * \n NOTE : This method can only be called by an object of type CallerType
        */
        void clear()
        {
            Subscribable::clear();
        }

    private:
        friend CallerType;
    };

} // namespace Dynamic_Static
