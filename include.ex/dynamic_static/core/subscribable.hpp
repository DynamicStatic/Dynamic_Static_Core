
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <unordered_set>
#include <utility>

namespace dst {

/**
Encapsulates a collection of mutual references between extended objects
*/
class Subscribable
{
public:
    /**
    Constructs an instance of Subscribable
    */
    inline Subscribable() = default;

    /**
    Moves an instance of Subscribable
    @param [in] other The Subscribable to move from
    */
    inline Subscribable(Subscribable&& other) noexcept
    {
        *this = std::move(other);
    }

    /**
    Destroys this instance of Subscribable
    */
    virtual ~Subscribable() = 0;

    /**
    Moves an instance of Subscribable
    @param [in] other The Subscribable to move from
    @return A reference to this Subscribable
    */
    inline Subscribable& operator=(Subscribable&& other) noexcept
    {
        mSubscribers = std::move(other.mSubscribers);
        for (auto pSubscriber : mSubscribers) {
            pSubscriber->mSubscriptions.erase(&other);
            pSubscriber->mSubscriptions.insert(this);
        }
        mSubscriptions = std::move(other.mSubscriptions);
        for (auto pSubscription : mSubscriptions) {
            pSubscription->mSubscribers.erase(&other);
            pSubscription->mSubscribers.insert(this);
        }
        return *this;
    }

    /**
    Adds a subscriber to this Subscribable
    @param [in] subscriber The Subscribable subscribing to this Subscribable
    @return A reference to this Subscribable
    */
    inline Subscribable& operator+=(Subscribable& subscriber)
    {
        if (this != &subscriber) {
            mSubscribers.insert(&subscriber);
            subscriber.mSubscriptions.insert(this);
        }
        return *this;
    }

    /**
    Removes a subscriber from this Subscribable
    @param [in] subscriber The Subscribable unsubscribing from this Subscribable
    @return A reference to this Subscribable
    */
    inline Subscribable& operator-=(Subscribable& subscriber)
    {
        mSubscribers.erase(&subscriber);
        subscriber.mSubscriptions.erase(this);
        return *this;
    }

    /**
    Gets this Subscribable subscribers
    @return This Subscribable object's subscribers
    */
    inline const std::unordered_set<Subscribable*>& get_subscribers() const
    {
        return mSubscribers;
    }

    /**
    Gets this Subscribable subscriptions
    @return This Subscribable object's subscriptions
    */
    inline const std::unordered_set<Subscribable*>& get_subscriptions() const
    {
        return mSubscriptions;
    }

    /**
    Removes all subscribers from this Subscribable
    */
    inline void clear_subscribers()
    {
        for (auto pSubscriber : mSubscribers) {
            pSubscriber->mSubscriptions.erase(this);
        }
        mSubscribers.clear();
    }

    /**
    Removes all subscriptions to this Subscribable
    */
    inline void clear_subscriptions()
    {
        for (auto pSubscription : mSubscriptions) {
            pSubscription->mSubscribers.erase(this);
        }
        mSubscriptions.clear();
    }

    /**
    Removes all subscribers from and subscriptions to this Subscribable
    */
    inline void clear()
    {
        clear_subscribers();
        clear_subscriptions();
    }

private:
    std::unordered_set<Subscribable*> mSubscribers;
    std::unordered_set<Subscribable*> mSubscriptions;
    Subscribable(const Subscribable&) = delete;
    Subscribable& operator=(const Subscribable&) = delete;
};

inline Subscribable::~Subscribable()
{
    clear();
}

} // namespace dst
