
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/event/subscribable.hpp"
#include "dynamic_static/core/action.hpp"
#include "dynamic_static/core/defines.hpp"

#include <functional>
#include <utility>

namespace dst {

/**
TODO : Documentation
*/
template <typename ...Args>
class Delegate
    : private Subscribable
{
public:
    /**
    Constructs an instance of Delegate<>
    */
    Delegate() = default;

    /**
    Constructs an instance of Delegate<>
    @param [in] action This Delegate<> object's Action<>
    */
    inline Delegate(Action<Args...> action)
        : mAction { action }
    {
    }

    /**
    Constructs an instance of Delegate<>
    @param [in] action This Delegate<> object's Action<>
    */
    inline Delegate(nullptr_t action)
        : mAction { action }
    {
    }

    /**
    Assigns this Delegate<> object's Action<>
    @param [in] action This Delegate<> object's Action<>
    @return A reference to this Delegate<>
    */
    inline Delegate& operator=(Action<Args...> action)
    {
        mAction = action;
        return *this;
    }

    /**
    Assigns this Delegate<> object's Action<>
    @param [in] action This Delegate<> object's Action<>
    @return A reference to this Delegate<>
    */
    inline Delegate& operator=(nullptr_t action)
    {
        mAction = action;
        return *this;
    }

    /**
    Moves an instance of Delegate<>
    @param [in] other The Delegate<> to move from
    */
    inline Delegate(Delegate<Args...>&& other)
    {
        *this = std::move(other);
    }

    /**
    Moves an instance of Delegate<>
    @param [in] other The Delegate<> to move from
    @return A reference to this Delegate<>
    */
    inline Delegate<Args...>& operator=(Delegate<Args...>&& other)
    {
        Subscribable::operator=(std::move(other));
        mAction = std::move(other.mAction);
    }

    /**
    TODO : Documentation
    */
    inline Delegate& operator+=(Delegate<Args...>& other)
    {
        Subscribable::operator+=(other);
        return *this;
    }

    /**
    TODO : Documentation
    */
    inline Delegate& operator-=(Delegate<Args...>& other)
    {
        Subscribable::operator-=(other);
        return *this;
    }

    /**
    TODO : Documentation
    */
    inline void operator()(Args&&... args) const
    {
        if (mAction) {
            mAction(std:forward<Args>(args)...);
        }
        for (auto pSubscriber : Subscribable::get_subscribers()) {
            *((const Delegate<Args...>*)pSubscriber)(std::forward<Args>(args)...);
        }
    }

    /**
    TODO : Documentation
    */
    inline operator bool() const
    {
        return mAction != nullptr;
    }

private:
    Action<Args...> mAction;
};

} // namespace dst
