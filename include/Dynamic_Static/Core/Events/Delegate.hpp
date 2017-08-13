
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Action.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Events/Subscribable.hpp"

#include <utility>

namespace Dynamic_Static {

    /**
     * Function objet used for Event subscription.
     * @param <Args> The parameter types for this Delegate's Action type
     */
    template <typename ...Args>
    class Delegate final
        : public detail::Subscribable<Args...>
    {
    private:
        Action<Args...> mAction;

    public:
        /**
         * Constructs an instance of Delegate.
         */
        Delegate() = default;

        /**
         * Constructs an instance of Delegate with a given Action.
         * @param [in] action This Delegate's Action
         */
        Delegate(const Action<Args...>& action)
            : mAction { action }
        {
        }

        /**
         * Assigns this Delegate a given Action.
         * @param [in] action The Action to assign to this Delegate
         */
        Delegate& operator=(const Action<Args...>& action)
        {
            mAction = action;
            return *this;
        }

        /**
         * Executes this Delegate's assigned Action.
         * @param [in] args Arguments to forward to this Delegate's Action
         */
        void operator()(Args... args) override
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
        }

    public:
        /**
         * Checks whether or not this Delegate is subscribed to a given Event.
         * @return Whether or not this Delegate is subscribed to the given Event
         */
        bool subscribed(const detail::Event<Args...>& event)
        {
            return detail::Subscribable<Args...>::subscribed(event);
        }

        /**
         * Removes all subscriptions from this Delegate.
         */
        void clear()
        {
            detail::Subscribable<Args...>::clear();
        }
    };

} // namespace Dynamic_Static
