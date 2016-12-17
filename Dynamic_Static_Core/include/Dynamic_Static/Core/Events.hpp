
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
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

namespace Dynamic_Static {
    namespace detail {
        template <typename ...Args>
        class Event;
    }
}

namespace Dynamic_Static {
    namespace detail {
        template <typename ...Args>
        class Subscribable
            : NonCopyable {
            friend Event<Args...>;
        private:
            struct DefferedCommand {
                enum class Type {
                    Clear,
                    Subscribe,
                    Unsubscribe,
                };

                Type type;
                Subscribable<Args...>* subscription;
            };

            typedef typename std::vector<Subscribable<Args...>*>::iterator Iterator;
            std::vector<Subscribable<Args...>*> m_subscriptions;
            std::vector<DefferedCommand> m_deffered_commands;
            bool m_locked { false };

        protected:
            Subscribable() = default;

            Subscribable(Subscribable<Args...>&& other)
            {
                *this = std::move(other);
            }

            virtual ~Subscribable() = 0
            {
                remove_all_mutual_subscriptions();
            }

            Subscribable<Args...>& operator=(Subscribable<Args...>&& other)
            {
                if (this != &other) {
                    other.remove_all_mutual_subscriptions();
                    m_subscriptions = std::move(other.m_subscriptions);
                    for (auto& subscription : m_subscriptions) {
                        create_mutual_subscription(*subscription);
                    }
                }

                return *this;
            }

            Subscribable<Args...>& operator+=(Subscribable<Args...>& subscription)
            {
                if (m_locked) {
                    create_deffered_command(DefferedCommand::Type::Subscribe, &subscription);
                } else {
                    if (!subscribed(subscription)) {
                        m_subscriptions.push_back(&subscription);
                        create_mutual_subscription(subscription);
                    }
                }

                return *this;
            }

            Subscribable<Args...>& operator-=(Subscribable<Args...>& subscription)
            {
                if (m_locked) {
                    create_deffered_command(DefferedCommand::Type::Unsubscribe, &subscription);
                } else {
                    auto itr = find(subscription);
                    if (subscribed(itr)) {
                        remove_mutual_subscription(subscription);
                        m_subscriptions.erase(itr);
                    }
                }

                return *this;
            }

            virtual void operator()(Args... args) = 0;

        public:
            /**
             * Gets this Subscribable's subscriptions.
             * @return This Subscribable's subscriptions
             */
            const std::vector<Subscribable<Args...>*>& subscriptions() const
            {
                return m_subscriptions;
            }

        protected:
            bool subscribed(const Subscribable<Args...>& subscription)
            {
                return subscribed(find(subscription));
            }

            void clear()
            {
                if (m_locked) {
                    create_deffered_command(DefferedCommand::Type::Clear);
                } else {
                    remove_all_mutual_subscriptions();
                    m_subscriptions.clear();
                }
            }

        private:
            bool subscribed(const Iterator& subscription) const
            {
                return subscription != m_subscriptions.end();
            }

            Iterator find(const Subscribable<Args...>& subscription)
            {
                return std::find(m_subscriptions.begin(), m_subscriptions.end(), &subscription);
            }

            void create_deffered_command(typename DefferedCommand::Type type, Subscribable<Args...>* subscribable = nullptr)
            {
                m_deffered_commands.push_back(DefferedCommand { type, subscribable });
            }

            void create_mutual_subscription(Subscribable<Args...>& subscription)
            {
                subscription.m_subscriptions.push_back(this);
            }

            void remove_mutual_subscription(Subscribable<Args...>& subscription)
            {
                subscription.m_subscriptions.erase(subscription.find(*this));
            }

            void remove_all_mutual_subscriptions()
            {
                for (auto& subscription : m_subscriptions) {
                    remove_mutual_subscription(*subscription);
                }
            }

            void lock()
            {
                m_locked = true;
            }

            void unlock()
            {
                m_locked = false;
                for (const auto& command : m_deffered_commands) {
                    switch (command.type) {
                        case DefferedCommand::Type::Clear:
                            clear();
                            break;

                        case DefferedCommand::Type::Subscribe:
                            operator+=(*command.subscription);
                            break;

                        case DefferedCommand::Type::Unsubscribe:
                            operator-=(*command.subscription);
                            break;
                    }
                }
            
                m_deffered_commands.clear();
            }
        };

        /**
         * Compares two Subscribables for equality.
         * @param [in] obj_0 The first object to compare
         * @param [in] obj_1 The second object to compare
         * @return Whether or not the two Subscribables are the same object
         */
        template <typename ...Args>
        bool operator==(const Subscribable<Args...>& obj_0, const Subscribable<Args...>& obj_1)
        {
            return &obj_0 == &obj_1;
        }

        /**
         * Compares two Subscribables for inequality.
         * @param [in] obj_0 The first object to compare
         * @param [in] obj_1 The second object to compare
         * @return Whether or not the two Subscribables are not the same object
         */
        template <typename ...Args>
        bool operator!=(const Subscribable<Args...>& obj_0, const Subscribable<Args...>& obj_1)
        {
            return !(obj_0 == obj_1);
        }
    }
}

namespace Dynamic_Static {
    namespace detail {
        template <typename ...Args>
        class Event
            : public Subscribable<Args...> {
        protected:
            void operator()(Args... args) override
            {
                lock();

                for (const auto& subscription : m_subscriptions) {
                    subscription->operator()(std::forward<Args>(args)...);
                }

                unlock();
            }
        };
    }
}

namespace Dynamic_Static {
    /**
     * Alias for a variadic std::function with no return value.
     */
    template <typename ...Args>
    using Action = std::function<void(Args...)>;
}

namespace Dynamic_Static {
    /**
     * Encapsulates an Action.
     * @param <Args> The parameter types for assignable Actions
     */
    template <typename ...Args>
    class Delegate final
        : public detail::Subscribable<Args...> {
    private:
        Action<Args...> m_action;

    public:
        /**
         * Constructs and instance of Delegate.
         */
        Delegate() = default;

        /**
         * Constructs an instance of Delegate with a specified Action.
         * @param [in] action The Action to construct this Delegate with
         */
        Delegate(const Action<Args...>& action)
            : m_action { action }
        {
        }

        /**
         * Assigns this Delegate a specified Action.
         * @param [in] action The Action to assign to this Delegate
         */
        Delegate& operator=(const Action<Args...>& action)
        {
            m_action = action;
            return *this;
        }

        /**
         * Executes this Delegate's assigned Action.
         * @param [in] args Arguments to forward to this Delegate's Action
         */
        void operator()(Args... args) override
        {
            if (m_action) {
                m_action(std::forward<Args>(args)...);
            }
        }

    public:
        /**
         * Checks whether or not this Delegate is subscribed to a specified Event.
         * @return Whether or not this Delegate is subscribed to the specified Event
         */
        bool subscribed(const detail::Event<Args...>& event)
        {
            return Subscribable::subscribed(event);
        }

        /**
         * Removes all subscriptions from this Delegate.
         */
        void clear()
        {
            Subscribable::clear();
        }
    };
}

namespace Dynamic_Static {
    /**
     * Enables an object to activate subscribed Delegates.
     * @param <OwnerType> The type that is capable of raising this Event
     * @param <Args> The parameter types for subscribable Delegates
     */
    template <typename OwnerType, typename ...Args>
    class Event final
        : public detail::Event<Args...> {
        friend OwnerType;
    public:
        /**
         * Subscribes a specified Delegate to this Event.
         * \n NOTE : If the specified Delegate is already subscribed to this Event, this method is a no-op
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         * @param [in] delegate The Delegate to subscribe to this Event
         */
        Event<OwnerType, Args...>& operator+=(Delegate<Args...>& delegate)
        {
            Subscribable::operator+=(delegate);
            return *this;
        }

        /**
         * Unsubscribes a specified Delegate from this Event.
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         * @param [in] delegate The Delegate to unsubscribe from this Event
         */
        Event<OwnerType, Args...>& operator-=(Delegate<Args...>& delegate)
        {
            Subscribable::operator-=(delegate);
            return *this;
        }

    private:
        /**
         * Raises this Event.
         * \n NOTE : This method can only be called by an object of type OwnerType
         * @param [in] args The arguments to forward to each subscribed Delegate
         */
        void operator()(Args... args) override
        {
            detail::Event<Args...>::operator()(std::forward<Args>(args)...);
        }

    public:
        /**
         * Checks whether or not a specified Delegate is subscribed to this Event.
         * @return Whether or not the specified Delegate is subscribed to this Event
         */
        bool subscribed(const Delegate<Args...>& delegate)
        {
            return Subscribable::subscribed(delegate);
        }

    private:
        /**
         * Removes all subscriptions from this Event.
         * \n NOTE : This method can only be called by an object of type OwnerType
         * \n NOTE : If this method is called while this Event is executing, it will be deffered until execution is complete
         */
        void clear()
        {
            Subscribable::clear();
        }
    };
}
