
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Action.hpp"

#include <functional>

namespace Dynamic_Static {
    /**
     * Enables a specified object type to execute arbitrary Actions.
     * @param <CallerType> The type of object that can execute this Callback
     * @param <Args> This Callback's argument types
     */
    template <typename CallerType, typename ...Args>
    class Callback {
        friend CallerType;
    private:
        Action<Args...> mAction;

    public:
        /**
         * Assigns this Callback's Action.
         * @param [in] action This Callback's Action
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
         * \n NOTE : This method can only be called by an object of type OwnerType
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
         * \n NOTE : This method can only be called by an object of type OwnerType
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
