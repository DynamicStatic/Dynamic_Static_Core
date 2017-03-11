
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
#include "Dynamic_Static/Core/MoveNotifier.hpp"

#include <type_traits>

namespace Dynamic_Static {
    /**
     * Maintains a handle to a MoveNotifier object.
     * @param <T> The type of the object
     * \n NOTE : This type must extend Dynamic_Static::MoveNotifier<T>
     */
    template <typename T>
    class MoveableHandle
        : NonCopyable {
    private:
        T* mHandle { nullptr };
        Delegate<T&> mDelegate;

    public:
        /**
         * Constructs an instance of MoveableHandle.
         */
        MoveableHandle() = default;

        /**
         * Constructs an instance of MoveableHandle.
         * @param [in] target This MoveableHandle's target
         */
        MoveableHandle(MoveNotifier<T>* target)
            : mHandle { static_cast<T*>(target) }
        {
            reset(target);
        }

        /**
         * Moves an instance of MoveableHandle.
         * @param other The MoveableHandle to move from
         */
        MoveableHandle(MoveableHandle<T>&& other)
        {
            *this = std::move(other);
        }

        /**
         * Moves an instance of MoveableHandle.
         * @param other The MoveableHandle to move from
         */
        MoveableHandle<T>& operator=(MoveableHandle<T>&& other)
        {
            if (this != &other) {
                mHandle = std::move(other.mHandle);
                mDelegate = std::move(other.mDelegate);
                other.mHandle = nullptr;
                bind_delegate();
            }

            return *this;
        }

        /**
         * Assigns this MoveableHandle's underlying pointer.
         * @param [in] target This MoveableHandle's underlying pointer
         */
        MoveableHandle<T>& operator=(MoveableHandle<T>* target)
        {
            reset(target);
        }

        /**
         * Dereferences this MoveableHandle underlying pointer.
         * @return The object pointed to by this MoveableHandle
         */
        typename std::add_lvalue_reference<T>::type operator*() const
        {
            return *mHandle;
        }

        /**
         * Dereferences this MoveableHandle's underlying pointer.
         * @return The object pointed to by this MoveableHandle
         */
        T* operator->() const
        {
            return mHandle;
        }

        /**
         * Gets a value indicating whether or not this MoveableHandle has a valid pointer.
         * @return Whether or not this MoveableHandle has a valid pointer
         */
        explicit operator bool() const
        {
            return mHandle != nullptr;
        }

    public:
        /**
         * Gets this MoveableHandle's underlying pointer.
         * @return This MoveableHandle's underlying pointer
         */
        T* get() const
        {
            return mHandle;
        }

        /**
         * Replaces this MoveableHandle's underlying pointer.
         * @param [in] target This MoveableHandle's underlying pointer
         */
        void reset(MoveNotifier<T>* target = nullptr)
        {
            if (mHandle) {
                static_cast<MoveNotifier<T>*>(mHandle)->OnMoved -= mDelegate;
            }

            mHandle = static_cast<T*>(target);
            if (mHandle) {
                static_cast<MoveNotifier<T>*>(mHandle)->OnMoved += mDelegate;
            }

            bind_delegate();
        }

    private:
        void bind_delegate()
        {
            using namespace std::placeholders;
            mDelegate = std::bind(&MoveableHandle::on_target_moved, this, _1);
        }

        void on_target_moved(T& target)
        {
            mHandle = static_cast<T*>(&target);
        }
    };
} // namespace Dynamic_Static
