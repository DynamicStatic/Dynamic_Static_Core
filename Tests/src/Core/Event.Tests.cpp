
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

#include "catch.hpp"

#include "Event.Tests.inl"

namespace Dynamic_Static {
    namespace Tests {
        static const size_t g_test_count { 16 };

        TEST_CASE("Subscribable objects can subscribe / unsubscribe", "[Events]")
        {
            std::vector<SubscribableObj> subscribables(g_test_count);
            auto subscriptions = create_randomized_subscriptions(subscribables);
            REQUIRE(validate_mutual_subscription(subscriptions));

            SECTION("unsubscribe()")
            {
                for (auto& subscription : subscriptions) {
                    subscription.unsubscribe();
                }
            
                REQUIRE(validate_mutual_unsubscription(subscriptions));
            }

            SECTION("clear()")
            {
                for (auto& subscribable : subscribables) {
                    subscribable.clear();
                }

                REQUIRE(validate_mutual_unsubscription(subscriptions));
            }
        }

        TEST_CASE("Subscribable's destructor removes subscriptions", "[Event]")
        {
            SubscribableObj subscribable;
            std::vector<SubscribableObj> subscribables(g_test_count);
            for (auto& subscription : subscribables) {
                subscribable.subscribe(subscription);
            }

            REQUIRE(subscribable.subscriptions().size() == subscribables.size());
            subscribables.clear();
            REQUIRE(subscribable.subscriptions().size() == 0);
        }

        TEST_CASE("Subscribable objects are moveable", "[Events]")
        {
            std::vector<SubscribableObj> move_from(g_test_count);
            auto subscriptions = create_randomized_subscriptions(move_from);
            auto move_to = move_vector_elements(move_from, false);

            auto retarget =
            [](SubscribableObj& from, SubscribableObj& to, SubscribableObj*& delegate) {
                if (delegate == &from) {
                    delegate = &to;
                }
            };

            for (size_t i = 0; i < move_from.size(); ++i) {
                for (auto& subscription : subscriptions) {
                    retarget(move_from[i], move_to[i], subscription.subscribable_0);
                    retarget(move_from[i], move_to[i], subscription.subscribable_1);
                }
            }

            bool move_from_unsubscribed = true;
            for (const auto& subscribable : move_from) {
                if (subscribable.subscriptions().size() != 0) {
                    move_from_unsubscribed = false;
                    break;
                }
            }

            move_from.clear();
            REQUIRE(move_from_unsubscribed);
            REQUIRE(validate_mutual_subscription(subscriptions));
        }

        TEST_CASE("Actions can be assigned to and called through Delegates", "[Events]")
        {
            auto delegates = create_delegates();
            for (auto& delegate : delegates) {
                REQUIRE(validate_delegate_call(delegate));
            }
        }

        TEST_CASE("Delegates are moveable", "[Events]")
        {
            auto move_from = create_delegates();
            auto move_to = move_vector_elements(move_from);
            for (auto& delegate : move_to) {
                REQUIRE(validate_delegate_call(delegate));
            }
        }

        TEST_CASE("Delegates can be assigned to and called through Events", "[Events]")
        {
            std::vector<Publisher> publishers(g_test_count);
            std::vector<Subscriber> subscribers(g_test_count);
            create_randomized_subscriptions(publishers, subscribers);
            activate_publishers(publishers);
            REQUIRE(validate_invocation(subscribers));
        }

        TEST_CASE("Events and Delegates are moveable after subscription", "[Events]")
        {
            std::vector<Publisher> publishers_move_from(g_test_count);
            std::vector<Subscriber> subscribers_move_from(g_test_count);
            create_randomized_subscriptions(publishers_move_from, subscribers_move_from);
            auto publishers_move_to = move_vector_elements(publishers_move_from);
            auto subscribers_move_to = move_vector_elements(subscribers_move_from);
            activate_publishers(publishers_move_to);
            REQUIRE(validate_invocation(subscribers_move_to));
        }

        TEST_CASE("Delegates can unsubscribe during invocation", "[Events]")
        {
            std::vector<Publisher> publishers(g_test_count);
            std::vector<Subscriber> subscribers(g_test_count);
            create_randomized_subscriptions(publishers, subscribers);
            for (auto& subscriber : subscribers) {
                subscriber.unsubscribe_on_event(true);
            }

            activate_publishers(publishers);
            std::vector<size_t> invocation_counts;
            invocation_counts.reserve(subscribers.size());
            for (const auto& subscriber : subscribers) {
                invocation_counts.push_back(subscriber.invocation_count());
            }

            activate_publishers(publishers);
            bool listeners_unsubscribed = true;
            for (size_t i = 0; i < subscribers.size(); ++i) {
                if (subscribers[i].invocation_count() != invocation_counts[i]) {
                    listeners_unsubscribed = false;
                    break;
                }
            }

            REQUIRE(listeners_unsubscribed);
        }
    }
}
