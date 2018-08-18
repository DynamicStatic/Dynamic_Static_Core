
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <array>
#include <initializer_list>
#include <type_traits>
#include <vector>

namespace Dynamic_Static {

    /*
    * Represents a non-owning reference to a contiguous sequence of objects.
    */
    template <typename T>
    class Span
    {
        // FROM : Modified ArrayProxy https://github.com/KhronosGroup/Vulkan-Hpp

    private:
        T* mData { nullptr };
        size_t mCount { 0 };

    public:
        /*
        * Constructs an instance of Span.
        */
        Span() = default;

        /*
        * Constructs an instance of Span.
        */
        constexpr Span(std::nullptr_t)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        Span(T& data)
            : mData { &data }
            , mCount { 1 }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        * @param [in] count This Span's count
        */
        Span(T* data, size_t count)
            : mData { data }
            , mCount { count }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param <N> This Span's count
        * @param [in] data This Span's data
        */
        template <size_t N>
        Span(std::array<typename std::remove_const<T>::type, N>& data)
            : mData(data.data())
            , mCount(N)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param <N> This Span's count
        * @param [in] data This Span's data
        */
        template <size_t N>
        Span(const std::array<typename std::remove_const<T>::type, N>& data)
            : mData(data.data())
            , mCount(N)
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Span(std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : mData { data.data() }
            , mCount { data.size() }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Span(const std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : mData { data.data() }
            , mCount { data.size() }
        {
        }

        /*
        * Constructs an instance of Span.
        * @param [in] data This Span's data
        */
        Span(const std::initializer_list<T>& data)
            : mData { data.begin() }
            , mCount { data.end() - data.begin() }
        {
        }

        /*
        * Gets a reference to an element at a given index.
        * @param [in] index The index of the element to get
        * @return The element at the given index
        */
        T& operator[](size_t index)
        {
            return mData[index];
        }

        /*
        * Gets a reference to an element at a given index.
        * @param [in] index The index of the element to get
        * @return The element at the given index
        */
        const T& operator[](size_t index) const
        {
            return mData[index];
        }

    public:
        /*
        * Gets an iterator to the beginning of this Span's sequence.
        * @return An iterator to the beginning of this Span's sequence
        */
        const T* begin() const
        {
            return mData;
        }

        /*
        * Gets an iterator to the end of this Span's sequence.
        * @return An iterator to the end of this Span's sequence
        */
        const T* end() const
        {
            return mData + mCount;
        }

        /*
        * Gets a reference to this Span's first element.
        * @return A reference to this Span's first element
        */
        T& front()
        {
            assert(mData && mCount);
            return *mData;
        }

        /*
        * Gets a reference to this Span's first element.
        * @return A reference to this Span's first element
        */
        const T& front() const
        {
            assert(mData && mCount);
            return *mData;
        }

        /*
        * Gets a reference to this Span's last element.
        * @return A reference to this Span's last element
        */
        T& back()
        {
            assert(mData && mCount);
            return *(mData + mCount - 1);
        }

        /*
        * Gets a reference to this Span's last element.
        * @return A reference to this Span's last element
        */
        const T& back() const
        {
            assert(mData && mCount);
            return *(mData + mCount - 1);
        }

        /*
        * Gets a value indicating whether or not this Span is empty.
        * @return A value indicating whether or not this Span is empty
        */
        bool empty() const
        {
            return (mCount == 0);
        }

        /*
        * Gets this Span's count.
        * @return This Span's count
        */
        size_t size() const
        {
            return mCount;
        }

        /*
        * Gets this Span's size in bytes.
        * @return This Span's size in bytes
        */
        size_t size_bytes() const
        {
            return mCount * sizeof(T);
        }

        /*
        * Gets a pointer to this Span's underlying storage.
        * @return A pointer to this Span's underlying storage
        */
        T* data() const
        {
            return mData;
        }
    };

} // namespace Dynamic_Static
