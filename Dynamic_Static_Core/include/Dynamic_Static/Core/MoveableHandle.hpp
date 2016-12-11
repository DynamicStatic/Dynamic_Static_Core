
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
#include "Dynamic_Static/Core/NonCopyable.hpp"
#include "Dynamic_Static/Core/MoveNotifier.hpp"

#include <type_traits>

namespace Dynamic_Static {
    template <typename T>
    class MoveableHandle
        : NonCopyable {
    private:
        T* m_handle { nullptr };
        Delegate<T&> m_delegate;

    public:
        /**
         * Constructs an instance of MoveableHandle.
         */
        MoveableHandle() = default;

        /**
         * Constructs an instance of MoveableHandle.
         * @param [in] target This MoveableHandle's target
         */
        MoveableHandle(MoveNotifier<T>& target)
            : m_handle { &target }
        {
            using namespace std::placeholders;
            m_delegate = std::bind(&MoveableHandle::on_target_moved, this, _1);
            target.on_moved += m_delegate;
        }

        /**
         * Converts this MoveableHandle to its underlying pointer.
         * @return This MoveableHandle's underlying pointer
         */
        operator T*() const { return m_handle; }

    private:
        void on_target_moved(T& target)
        {
            m_handle = static_cast<T*>(&target);
        }
    };
}
