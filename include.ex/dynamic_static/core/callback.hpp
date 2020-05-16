
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/action.hpp"
#include "dynamic_static/core/defines.hpp"

#include <functional>
#include <utility>

namespace dst {

/**
TODO : Documentation
*/
template <typename CallerType, typename ...Args>
class Callback final
{
public:
    /**
    TODO : Documentation
    */
    template <typename ActionType>
    inline Callback<CallerType, Args...>& operator=(ActionType action)
    {
        mAction = action;
        return *this;
    }

private:
    /**
    TODO : Documentation
    */
    inline void operator()(Args&&... args) const
    {
        if (mAction) {
            mAction(std::forward<Args>(args)...);
        }
    }

    Action<Args...> mAction;
    friend CallerType;
};

} // namespace dst
