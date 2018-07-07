
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <functional>
#include <utility>

namespace Dynamic_Static {

    /*
    * Encapsulates an std::function<void(Args...)> that is callable by a given type.
    * @param <CallerType> The type of object that can execute this Callback
    * @param <Args> This Callback's argument types
    */
    template <
        typename CallerType,
        typename ...Args
    >
    class Callback
    {
        friend CallerType;

    private:
        std::function<void(Args...)> mAction;

    public:
        /*
        * Assigns this Callback's std::function<void(Args...)>.
        * @return This Callback
        */
        inline Callback<CallerType, Args...>& operator=(const std::function<void(Args...)>& action)
        {
            mAction = action;
            return *this;
        }

        /**
        * Gets a value indicating whether or not this Callback has a valid std::function<void(Args...)>.
        * @return Whether or not this Callback has a valid std::function<void(Args...)>
        */
        inline operator bool() const
        {
            return mAction != nullptr;
        }

    private:
        /**
        * Executes this Callback.
        * \n NOTE : This method can only be called by an object of type CallerType
        * @param [in] args The arguments to execute this Callback with
        */
        inline void operator()(Args...&& args)
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
        }

        /**
        * Executes this Callback.
        * \n NOTE : This method can only be called by an object of type CallerType
        * @param [in] args The arguments to execute this Callback with
        */
        inline void operator()(Args...&& args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
        }
    };

} // namespace Dynamic_Static
