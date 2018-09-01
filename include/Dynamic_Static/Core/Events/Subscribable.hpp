
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <algorithm>
#include <utility>
#include <vector>

namespace Dynamic_Static {

    /*!
    Provides tracking of mutual subscription between objects.
    */
    class Subscribable
        : NonCopyable
    {
    private:
        std::vector<Subscribable*> mSubscribers;
        std::vector<Subscribable*> mSubscriptions;

    public:
        /*!
        Constructs an instance of Subscribable.
        */
        inline Subscribable() = default;

        /*!
        Moves an instance of Subscribable.
        @param [in] other The Subscribable to move from
        */
        inline Subscribable(Subscribable&& other)
        {
            *this = std::move(other);
        }

        /*!
        Destroys this instance of Subscribable.
        */
        virtual inline ~Subscribable()
        {
            clear();
        }

        /*!
        Moves an instance of Subscribable.
        @param [in] other The Subscribable to move from
        @return This Subscribable
        */
        inline Subscribable& operator=(Subscribable&& other)
        {
            if (this != &other) {
                mSubscribers = std::move(other.mSubscribers);
                for (auto subscriber : mSubscribers) {
                    auto itr = dst::find(subscriber->mSubscriptions, &other);
                    assert(itr != subscriber->mSubscriptions.end());
                    *itr = this;
                }
                mSubscriptions = std::move(other.mSubscriptions);
                for (auto subscription : mSubscriptions) {
                    auto itr = dst::find(subscription->mSubscribers, &other);
                    assert(itr != subscription->mSubscribers.end());
                    *itr = this;
                }
            }
            return *this;
        }

        /*!
        Subscribes a given Subscribable to this Subscribable.
        @param [in] subscriber The Subscribable subscribing to this Subscribable
        @return This Subscribable
        */
        inline Subscribable& operator+=(Subscribable& subscriber)
        {
            if (!subscriber.subscribed_to(*this)) {
                mSubscribers.push_back(&subscriber);
                subscriber.mSubscriptions.push_back(this);
            }
            return *this;
        }

        /*!
        Unsubscribes a given Subscribable from this Subscribable.
        @param [in] subscriber The Subscribable unsubscribing from this Subscribable
        @return This Subscribable
        */
        inline Subscribable& operator-=(Subscribable& subscriber)
        {
            auto itr = dst::find(mSubscribers, &subscriber);
            if (itr != mSubscribers.end()) {
                mSubscribers.erase(itr);
                itr = dst::find(subscriber.mSubscriptions, this);
                assert(itr != subscriber.mSubscriptions.end());
                subscriber.mSubscriptions.erase(itr);
            }
            return *this;
        }

    public:
        /*!
        Gets of this Subscribable's subscribers.
        @return This Subscribable's subscribers
        */
        inline const std::vector<Subscribable*>& get_subscribers() const
        {
            return mSubscribers;
        }

        /*!
        Gets of this Subscribable's subscriptions.
        @return This Subscribable's subscrpitions
        */
        inline const std::vector<Subscribable*>& get_subscriptions() const
        {
            return mSubscriptions;
        }

        /*!
        Gets a value indicating whether or not this Subscribable is subscribed to a given Subscribable.
        @return Whether or not this Subscribable is subscribed to a given Subscribable
        */
        inline bool subscribed_to(const Subscribable& other) const
        {
            return dst::find(mSubscriptions, &other) != mSubscriptions.end();
        }

        /*!
        Removes all of this Subscribable's subscribers.
        */
        inline void clear_subscribers()
        {
            for (auto subscriber : mSubscribers) {
                auto itr = dst::find(subscriber->mSubscriptions, this);
                assert(itr != subscriber->mSubscriptions.end());
                subscriber->mSubscriptions.erase(itr);
            }
            mSubscribers.clear();
        }

        /*!
        Removes all of this Subscribable's subscriptions.
        */
        inline void clear_subscriptions()
        {
            for (auto& subscription : mSubscriptions) {
                auto itr = dst::find(subscription->mSubscribers, this);
                assert(itr != subscription->mSubscribers.end());
                subscription->mSubscribers.erase(itr);
            }
            mSubscriptions.clear();
        }

        /*!
        Removes all of this Subscribable's subscribers and subscriptions.
        */
        inline void clear()
        {
            clear_subscribers();
            clear_subscriptions();
        }
    };

} // namespace Dynamic_Static
