#if 0
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Callback.hpp"
#include "Dynamic_Static/Core/Defines.hpp"

#include <utility>

namespace dst {

    /*!
    Provides a Callback<> for move notification.
    */
    template <typename T>
    class MoveNotifier
    {
    public:
        /*!
        Callback<> executed when this MoveNotifier is moved.
        @param [in] (MoveNotifier*) The address moved to
        @param [in] (MoveNotifier*) The address moved from
        */
        Callback<MoveNotifier<T>, MoveNotifier<T>*, MoveNotifier<T>*> on_move;

    public:
        /*!
        Constructs an instance of MoveNotifier<T>.
        */
        MoveNotifier() = default;

        /*!
        Moves this instance of MoveNotifier.
        @param [in] other The MoveNotifier to move from
        */
        MoveNotifier(MoveNotifier<T>&& other)
        {
            *this = std::move(other);
        }

        /*!
        Moves this instance of MoveNotifier.
        @param [in] other The MoveNotifier to move from
        @return This MoveNotifier
        */
        MoveNotifier<T>& operator=(MoveNotifier<T>&& other)
        {
            if (this != &other) {
                on_move = std::move(other);
                other.on_move = nullptr;
                on_move(this, &other);
            }
            return *this;
        }
    };

} // namespace dst
#endif