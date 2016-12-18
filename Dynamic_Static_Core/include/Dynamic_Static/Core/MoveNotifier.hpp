
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

#pragma once

#include "Dynamic_Static/Core/Events.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <utility>

namespace Dynamic_Static {
    /**
     * Raises an Event when this object is moved.
     * \n NOTE : MoveNotifier must be extended using CRT
     */
    template <typename T>
    class MoveNotifier
        : NonCopyable {
        friend T;
    public:
        /**
         * Event raised when this MoveNotifier is moved.
         * @param [in] The object being moved
         */
        Event<MoveNotifier<T>, T&> on_moved;

    private:
        MoveNotifier() = default;

    public:
        /**
         * Moves an instance of MoveNotifier.
         * @param [in] other The MoveNotifier to move from
         */
        MoveNotifier(MoveNotifier<T>&& other)
        {
            *this = std::move(other);
        }

        /**
         * Destroys this instance of MoveNotifier.
         */
        virtual ~MoveNotifier() = 0;

        /**
         * Moves an instance of MoveNotifier.
         * @param [in] other The MoveNotifier to move from
         */
        MoveNotifier<T>& operator=(MoveNotifier<T>&& other)
        {
            if (this != &other) {
                on_moved = std::move(other.on_moved);
                on_moved(*static_cast<T*>(this));
            }

            return *this;
        }
    };

    template <typename T>
    MoveNotifier<T>::~MoveNotifier()
    {
    }
}
