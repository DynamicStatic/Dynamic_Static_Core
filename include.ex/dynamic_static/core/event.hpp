
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/event/delegate.hpp"
#include "dynamic_static/core/action.hpp"
#include "dynamic_static/core/defines.hpp"

#include <functional>
#include <utility>

namespace dst {

template <typename CallerType, typename ...Args>
class Event
    : private Delegate<Args...>
{
public:
    /**
    TODO : Documentation
    */
    Event() = default;

    /**
    TODO : Documentation
    */
    inline Event(Action<Args...> action)
        : Delegate<Args...>(action)
    {
    }

    /**
    TODO : Documentation
    */
    inline Event(Event<CallerType, Args...>&& other)
    {
        *this = std::move(other);
    }

    /**
    TODO : Documentation
    */
    inline Event<CallerType, Args...>& operator=(Event<CallerType, Args...>&& other)
    {
        Delegate<Args...>::operator=(std::move(other));
    }

    /**
    TODO : Documentation
    */
    inline Event<CallerType, Args...>& operator=(Action<Args...> action)
    {
        Delegate<Args...>::operator=(action);
    }

private:
    /**
    TODO : Documentation
    */
    inline void operator()(Args&&... args) const
    {
        Delegate<Args...>::operator()(std::forward<Args>(args)...);
    }

    friend CallerType;
};

} // namespace dst
