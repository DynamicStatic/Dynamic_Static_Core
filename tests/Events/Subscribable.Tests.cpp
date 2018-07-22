
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Events/Subscribable.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    static constexpr int TestCount { 16 };

    class Subscription final
    {
    private:
        Subscribable* subscribable0 { nullptr };
        Subscribable* subscribable1 { nullptr };

    public:
        Subscription(
            Subscribable* subscribable0,
            Subscribable* subscribable1
        )
            : subscribable0 { subscribable0 }
            , subscribable1 { subscribable1 }
        {
            subscribe();
        }

    public:
        void subscribe()
        {
            (*subscribable0) += (*subscribable1);
        }

        void unsusbscribe()
        {
            (*subscribable0) -= (*subscribable1);
        }

        bool is_subscribed() const
        {
            return
                subscribable0->is_subscribed_to(*subscribable1) ||
                subscribable1->is_subscribed_to(*subscribable0);
        }

        bool is_unsusbscribed() const
        {
            return
                !subscribable0->is_subscribed_to(*subscribable1) &&
                !subscribable1->is_subscribed_to(*subscribable0);
        }
    };

    static std::vector<Subscription> create_randomized_subscriptions(
        std::vector<Subscribable>& subscribables
    )
    {
        dst::RandomNumberGenerator rng;
        std::vector<Subscription> subscriptions;
        for (int i = 0; i < subscribables.size(); ++i) {
            for (int j = i + 1; j < subscribables.size(); ++j) {
                if (rng.probability(0.5f)) {
                    subscriptions.push_back(Subscription(&subscribables[i], &subscribables[j]));
                }
            }
        }
        return subscriptions;
    }

    static bool validate_subscriptions(
        const std::vector<Subscription>& subscriptions
    )
    {
        bool valid = true;
        for (const auto& subscription : subscriptions) {
            if (!subscription.is_subscribed()) {
                valid = false;
                break;
            }
        }
        return valid;
    }

    static bool validate_unsusbscriptions(
        const std::vector<Subscription>& subscriptions
    )
    {
        bool valid = true;
        for (const auto& subscription : subscriptions) {
            if (!subscription.is_unsusbscribed()) {
                valid = false;
                break;
            }
        }
        return valid;
    }

    TEST_CASE("Subscribable objects can create and remove subscriptions", "[Subscribable]")
    {
        std::vector<Subscribable> subscribables(TestCount);
        auto subscriptions = create_randomized_subscriptions(subscribables);
        REQUIRE(validate_subscriptions(subscriptions));

        SECTION("operator-=()")
        {
            for (auto& subscription : subscriptions) {
                subscription.unsusbscribe();
            }
            REQUIRE(validate_unsusbscriptions(subscriptions));
        }

        SECTION("clear()")
        {
            for (auto& subscribable : subscribables) {
                subscribable.clear();
            }
            REQUIRE(validate_unsusbscriptions(subscriptions));
        }
    }

    TEST_CASE("Subscribable dtor() removes subscriptions", "[Subscribable]")
    {
        Subscribable subscribable;
        std::vector<Subscribable> tempSubscribables(TestCount);
        for (auto& tempSubscribable : tempSubscribables) {
            subscribable += tempSubscribable;
        }

        REQUIRE(subscribable.get_subscriptions().size() == tempSubscribables.size());
        tempSubscribables.clear();
        REQUIRE(subscribable.get_subscriptions().empty());
    }

    TEST_CASE("Subscribable objects are moveable", "[Subscribable]")
    {
        Subscribable obj0;
        Subscribable obj1;
        obj0 += obj1;
        REQUIRE(obj0.is_subscribed_to(obj1));
        Subscribable obj2 = std::move(obj0);
        Subscribable obj3 = std::move(obj1);
        REQUIRE(!obj0.is_subscribed_to(obj1));
        REQUIRE(obj2.is_subscribed_to(obj3));
    }

} // namespace Tests
} // namespace Dynamic_Static
