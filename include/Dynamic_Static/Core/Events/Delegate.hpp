
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
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
