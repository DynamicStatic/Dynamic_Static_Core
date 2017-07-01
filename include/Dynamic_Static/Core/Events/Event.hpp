
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

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Events/Delegate.hpp"
#include "Dynamic_Static/Core/Events/Subscribable.hpp"

#include <utility>

namespace Dynamic_Static
{
    namespace detail
    {
        template <typename ...Args>
        class Event
            : public Subscribable<Args...>
        {
            // TODO : This can be refactored out by making Delegate multicast
            //        then using it as the base for Event...ie Event would only
            //        provide the CallerType / Callback functionality.  This
            //        would also remove the need to have an abstract operator()
            //        and friend Event<Args...> in Subscribable which would be
            //        a good separation of concerns and allow Subscribable to
            //        come out of the detail namespace.
        protected:
            void operator()(Args... args) override
            {
                Subscribable<Args...>::lock();

                for (const auto& subscription : Subscribable<Args...>::mSubscriptions) {
                    subscription->operator()(std::forward<Args>(args)...);
                }

                Subscribable<Args...>::unlock();
            }
        };
    } // namespace detail
} // namespace Dynamic_Static

namespace Dynamic_Static
{
    /**
     * Enables an object of a given type to execute subscribed Delegates.
     * @param <CallerType> The type that is capable of raising this Event
     * @param <Args>       The parameter types for subscribable Delegates
     */
    template <typename CallerType, typename ...Args>
    class Event final
        : public detail::Event<Args...>
    {
        friend CallerType;
    public:
        /**
         * Subscribes a given Delegate to this Event.
         * \n NOTE : If the given Delegate is already subscribed to this Event, this method is a noop
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         * @param [in] delegate The Delegate to subscribe to this Event
         */
        Event<CallerType, Args...>& operator+=(Delegate<Args...>& delegate)
        {
            detail::Subscribable<Args...>::operator+=(delegate);
            return *this;
        }

        /**
         * Unsubscribes a given Delegate from this Event.
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         * @param [in] delegate The Delegate to unsubscribe from this Event
         */
        Event<CallerType, Args...>& operator-=(Delegate<Args...>& delegate)
        {
            detail::Subscribable<Args...>::operator-=(delegate);
            return *this;
        }

    private:
        /**
         * Raises this Event.
         * \n NOTE : This method can only be called by an object of type CallerType
         * @param [in] args The arguments to forward to each subscribed Delegate
         */
        void operator()(Args... args) override
        {
            detail::Event<Args...>::operator()(std::forward<Args>(args)...);
        }

    public:
        /**
         * Checks whether or not a given Delegate is subscribed to this Event.
         * @return Whether or not the given Delegate is subscribed to this Event
         */
        bool subscribed(const Delegate<Args...>& delegate)
        {
            return detail::Subscribable<Args...>::subscribed(delegate);
        }

    private:
        /**
         * Removes all subscriptions from this Event.
         * \n NOTE : This method can only be called by an object of type CallerType
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         */
        void clear()
        {
            detail::Subscribable<Args...>::clear();
        }
    };
} // namespace Dynamic_Static
