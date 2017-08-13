
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Action.hpp"
#include "Dynamic_Static/Core/Defines.hpp"

#include <utility>

namespace Dynamic_Static {

    /**
     * Encapsulates a subscribable Action callable by a given type.
     * @param <CallerType> The type of object that can execute this Callback
     * @param <Args>       This Callback's argument types
     */
    template <typename CallerType, typename ...Args>
    class Callback
    {
        friend CallerType;

    private:
        Action<Args...> mAction;

    public:
        /**
         * Assigns this Callback's Action.
         */
        Callback<CallerType, Args...>& operator=(Action<Args...> action)
        {
            mAction = action;
            return *this;
        }

        /**
         * Gets a value indicating whether or not this Callback has a valid Action.
         * @return Whether or not this Callback has a valid Action
         */
        operator bool() const
        {
            return mAction;
        }

    private:
        /**
         * Executes this Callback.
         * \n NOTE : This method can only be called by an object of type CallerType
         * @param [in] args The arguments to execute this Callback with
         */
        void operator()(Args... args)
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
        void operator()(Args... args) const
        {
            if (mAction) {
                mAction(std::forward<Args>(args)...);
            }
        }
    };

} // namespace Dynamic_Static
