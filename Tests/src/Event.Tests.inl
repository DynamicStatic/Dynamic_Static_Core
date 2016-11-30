
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

#include "Dynamic_Static/Core/Events.hpp"

#include "Dynamic_Static/Core/Random.hpp"

#pragma once

namespace Dynamic_Static {
    namespace Tests {
        class SubscribableObj final
            : public detail::Subscribable<> {
        public:
            void operator()() { }
            void subscribe(SubscribableObj& subscription) { operator+=(subscription); }
            void unsubscribe(SubscribableObj& subscription) { operator-=(subscription); }
            bool subscribed(SubscribableObj& subscription) { return Subscribable::subscribed(subscription); }
            void clear() { Subscribable::clear(); }
        };
    }
}

namespace Dynamic_Static {
    namespace Tests {
        struct Subscription {
            SubscribableObj* subscribable_0;
            SubscribableObj* subscribable_1;

            Subscription(SubscribableObj& subscribable_0, SubscribableObj& subscribable_1)
                : subscribable_0 { &subscribable_0 }
                , subscribable_1 { &subscribable_1 }
            {
                subscribe();
            }

            void subscribe()
            {
                subscribable_0->subscribe(*subscribable_1);
            }

            void unsubscribe()
            {
                subscribable_0->unsubscribe(*subscribable_1);
            }

            bool subscribed() const
            {
                return
                    subscribable_0->subscribed(*subscribable_1) &&
                    subscribable_1->subscribed(*subscribable_0);
            }

            bool unsubscribed() const
            {
                return
                    !subscribable_0->subscribed(*subscribable_1) &&
                    !subscribable_1->subscribed(*subscribable_0);
            }
        };
    }
}

namespace Dynamic_Static {
    namespace Tests {
        static void set_target_value(uint32_t value, uint32_t& target)
        {
            target = value;
        }

        class Obj {
        public:
            void set_target_value(uint32_t value, uint32_t& target)
            {
                Tests::set_target_value(value, target);
            }
        };

        static Obj g_test_obj;
    }
}

namespace Dynamic_Static {
    namespace Tests {
        class Publisher final {
        public:
            Event<Publisher, Publisher&> on_event;

            void fire_event()
            {
                on_event(*this);
            }
        };
    }
}

namespace Dynamic_Static {
    namespace Tests {
        class Subscriber final {
        private:
            size_t m_invocation_count { 0 };
            bool m_unsubscribe_on_event { false };
            Delegate<Publisher&> m_on_publisher_event;

        public:
            Subscriber() = default;

            Subscriber(Subscriber&& other)
            {
                *this = std::move(other);
            }

            Subscriber& operator=(Subscriber&& other)
            {
                if (this != &other) {
                    m_invocation_count = std::move(other.m_invocation_count);
                    m_unsubscribe_on_event = std::move(other.m_unsubscribe_on_event);
                    m_on_publisher_event = std::move(other.m_on_publisher_event);
                    bind_delegate();
                }

                return *this;
            }

        public:
            bool unsubscribe_on_event() const { return m_unsubscribe_on_event; }
            void unsubscribe_on_event(bool unsubscribe) { m_unsubscribe_on_event = unsubscribe; }
            size_t subscription_count() const { return m_on_publisher_event.subscriptions().size(); }
            size_t invocation_count() const { return m_invocation_count; }

            void subscribe(Publisher& publisher)
            {
                publisher.on_event += m_on_publisher_event;
                bind_delegate();
            }

        private:
            void bind_delegate()
            {
                using namespace std::placeholders;
                m_on_publisher_event = std::bind(&Subscriber::on_publisher_event, this, _1);
            }

            void on_publisher_event(Publisher& publisher)
            {
                if (m_unsubscribe_on_event) {
                    publisher.on_event -= m_on_publisher_event;
                }

                ++m_invocation_count;
            }
        };
    }
}

namespace Dynamic_Static {
    namespace Tests {
        static std::vector<Subscription> create_randomized_subscriptions(std::vector<SubscribableObj>& subscribables)
        {
            std::vector<Subscription> subscriptions;
            for (size_t i = 0; i < subscribables.size(); ++i) {
                for (size_t j = i + 1; j < subscribables.size(); ++j) {
                    if (Random.probability(0.5f)) {
                        subscriptions.push_back(Subscription(subscribables[i], subscribables[j]));
                    }
                }
            }

            return subscriptions;
        }

        static void create_randomized_subscriptions(std::vector<Publisher>& publishers, std::vector<Subscriber>& subscribers)
        {
            for (auto& publisher : publishers) {
                for (auto& subscriber : subscribers) {
                    if (Random.probability(0.5f)) {
                        subscriber.subscribe(publisher);
                    }
                }
            }
        }

        static bool validate_mutual_subscription(const std::vector<Subscription>& subscriptions)
        {
            bool mutually_subscribed = true;
            for (const auto& subscription : subscriptions) {
                if (!subscription.subscribed()) {
                    mutually_subscribed = false;
                    break;
                }
            }

            return mutually_subscribed;
        }

        static bool validate_mutual_unsubscription(const std::vector<Subscription>& subscriptions)
        {
            bool mutually_unsubscribed = true;
            for (const auto& subscription : subscriptions) {
                if (!subscription.unsubscribed()) {
                    mutually_unsubscribed = false;
                    break;
                }
            }

            return mutually_unsubscribed;
        }

        template <typename T>
        static std::vector<T> move_vector_elements(std::vector<T>& move_from, bool clear = true)
        {
            std::vector<T> move_to;
            for (auto& element : move_from) {
                move_to.push_back(std::move(element));
            }

            if (clear) {
                move_from.clear();
            }

            return move_to;
        }

        static std::vector<Delegate<uint32_t, uint32_t&>> create_delegates()
        {
            using namespace std::placeholders;
            std::vector<Delegate<uint32_t, uint32_t&>> delegates;
            delegates.push_back(Action<uint32_t, uint32_t&>(std::bind(&Obj::set_target_value, &g_test_obj, _1, _2)));
            delegates.push_back(Action<uint32_t, uint32_t&>(set_target_value));
            delegates.push_back(Action<uint32_t, uint32_t&>(
                [](uint32_t value, uint32_t& target)
                {
                    target = value;
                }
            ));

            return delegates;
        }

        static bool validate_delegate_call(Delegate<uint32_t, uint32_t&>& delegate)
        {
            uint32_t value = 64;
            uint32_t target = 0;
            delegate(value, target);
            return value == target;
        }

        void activate_publishers(std::vector<Publisher>& publishers)
        {
            for (auto& publisher : publishers) {
                publisher.fire_event();
            }
        }

        bool validate_invocation(const std::vector<Subscriber>& subscribers)
        {
            bool all_subscribers_invoked = true;
            for (const auto& subscriber : subscribers) {
                if (subscriber.invocation_count() != subscriber.subscription_count()) {
                    all_subscribers_invoked = false;
                    break;
                }
            }

            return all_subscribers_invoked;
        }
    }
}
