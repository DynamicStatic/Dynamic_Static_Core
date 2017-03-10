
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

#include "Events.Tests.inl"

namespace Dynamic_Static {
    namespace Tests {
        static const size_t gTestCount { 16 };

        TEST_CASE("Subscribable objects can subscribe / unsubscribe", "[Events]")
        {
            std::vector<SubscribableObj> subscribables(gTestCount);
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
            std::vector<SubscribableObj> subscribables(gTestCount);
            for (auto& subscription : subscribables) {
                subscribable.subscribe(subscription);
            }

            REQUIRE(subscribable.subscriptions().size() == subscribables.size());
            subscribables.clear();
            REQUIRE(subscribable.subscriptions().size() == 0);
        }

        TEST_CASE("Subscribable objects are moveable", "[Events]")
        {
            std::vector<SubscribableObj> moveFrom(gTestCount);
            auto subscriptions = create_randomized_subscriptions(moveFrom);
            auto moveTo = move_vector_elements(moveFrom, false);

            auto retarget =
            [](SubscribableObj& from, SubscribableObj& to, SubscribableObj*& delegate) {
                if (delegate == &from) {
                    delegate = &to;
                }
            };

            for (size_t i = 0; i < moveFrom.size(); ++i) {
                for (auto& subscription : subscriptions) {
                    retarget(moveFrom[i], moveTo[i], subscription.subscribable0);
                    retarget(moveFrom[i], moveTo[i], subscription.subscribable1);
                }
            }

            bool moveFromUnsubscribed = true;
            for (const auto& subscribable : moveFrom) {
                if (subscribable.subscriptions().size() != 0) {
                    moveFromUnsubscribed = false;
                    break;
                }
            }

            moveFrom.clear();
            REQUIRE(moveFromUnsubscribed);
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
            auto moveFrom = create_delegates();
            auto moveTo = move_vector_elements(moveFrom);
            for (auto& delegate : moveTo) {
                REQUIRE(validate_delegate_call(delegate));
            }
        }

        TEST_CASE("Delegates can be assigned to and called through Events", "[Events]")
        {
            std::vector<Publisher> publishers(gTestCount);
            std::vector<Subscriber> subscribers(gTestCount);
            create_randomized_subscriptions(publishers, subscribers);
            activate_publishers(publishers);
            REQUIRE(validate_invocation(subscribers));
        }

        TEST_CASE("Events and Delegates are moveable after subscription", "[Events]")
        {
            std::vector<Publisher> publishersMoveFrom(gTestCount);
            std::vector<Subscriber> subscribersMoveFrom(gTestCount);
            create_randomized_subscriptions(publishersMoveFrom, subscribersMoveFrom);
            auto publishersMoveTo = move_vector_elements(publishersMoveFrom);
            auto subscribersMoveTo = move_vector_elements(subscribersMoveFrom);
            activate_publishers(publishersMoveTo);
            REQUIRE(validate_invocation(subscribersMoveTo));
        }

        TEST_CASE("Delegates can unsubscribe during invocation", "[Events]")
        {
            std::vector<Publisher> publishers(gTestCount);
            std::vector<Subscriber> subscribers(gTestCount);
            create_randomized_subscriptions(publishers, subscribers);
            for (auto& subscriber : subscribers) {
                subscriber.unsubscribe_on_event(true);
            }

            activate_publishers(publishers);
            std::vector<size_t> invocationCounts;
            invocationCounts.reserve(subscribers.size());
            for (const auto& subscriber : subscribers) {
                invocationCounts.push_back(subscriber.invocation_count());
            }

            activate_publishers(publishers);
            bool listenersUnsubscribed = true;
            for (size_t i = 0; i < subscribers.size(); ++i) {
                if (subscribers[i].invocation_count() != invocationCounts[i]) {
                    listenersUnsubscribed = false;
                    break;
                }
            }

            REQUIRE(listenersUnsubscribed);
        }
    }
}
