
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"
#include "dynamic_static/core/vector.hpp"

#include <algorithm>
#include <array>
#include <initializer_list>
#include <type_traits>
#include <vector>

namespace dst {

/**
TODO : Documentation
*/
template <typename T>
class Span final
{
public:
    /**
    TODO : Documentation
    */
    Span() = default;

    /**
    TODO : Documenation
    */
    inline constexpr Span(std::nullptr_t)
    {
    }

    /**
    TODO : Documentation
    */
    inline Span(T& data)
        : mData { &data }
        , mCount { 1 }
    {
    }

    /**
    TODO : Documentation
    */
    inline Span(T* data, size_t count)
        : mData { count ? data : nullptr }
        , mCount { data ? count : 0 }
    {
    }

    /**
    TODO : Documentation
    */
    template <size_t N>
    inline Span(std::array<typename std::remove_const<T>::type, N>& data)
        : mData { N ? data.data() : nullptr }
        , mCount { N }
    {
    }

    /**
    TODO : Documentation
    */
    template <size_t N>
    inline Span(const std::array<typename std::remove_const<T>::type, N>& data)
        : mData { N ? data.data() : nullptr }
        , mCount { N }
    {
    }

    /**
    Constructs an instance of Span
    @param [in] data This Span object's data
    */
    template <class AllocatorType = std::allocator<typename std::remove_const<T>::type>>
    inline Span(std::vector<typename std::remove_const<T>::type, AllocatorType>& data)
        : mData { vector::data(data) }
        , mCount { data.size() }
    {
    }

    /**
    Constructs an instance of Span
    @param [in] data This Span object's data
    */
    template <class AllocatorType = std::allocator<typename std::remove_const<T>::type>>
    inline Span(const std::vector<typename std::remove_const<T>::type, AllocatorType>& data)
        : mData { vector::data(data) }
        , mCount { data.size() }
    {
    }

    /**
    Constructs an instance of Span
    @param [in] data This Span object's data
    */
    inline Span(const std::initializer_list<T>& data)
        : mData { data.begin() }
        , mCount { data.end() - data.begin() }
    {
    }

    /**
    Gets a reference to an element at a given index
    @param [in] index The index of the element to get
    @return The element at the given index
    */
    const T& operator[](size_t index) const
    {
        assert(mData && mCount);
        return mData[index];
    }

    /**
    Gets a reference to an element at a given index
    @param [in] index The index of the element to get
    @return The element at the given index
    */
    T& operator[](size_t index)
    {
        assert(mData && mCount);
        return mData[index];
    }

    /**
    Gets an iterator to the beginning of this Span object's sequence
    @return An iterator to the beginning of this Span object's sequence
    */
    const T* begin() const
    {
        return mData;
    }

    /**
    Gets an iterator to the beginning of this Span object's sequence
    @return An iterator to the beginning of this Span object's sequence
    */
    T* begin()
    {
        return mData;
    }

    /**
    Gets an iterator to the end of this Span object's sequence
    @return An iterator to the end of this Span object's sequence
    */
    const T* end() const
    {
        return mData + mCount;
    }

    /**
    Gets an iterator to the end of this Span object's sequence
    @return An iterator to the end of this Span object's sequence
    */
    T* end()
    {
        return mData + mCount;
    }

    /**
    Gets a reference to this Span object's first element
    @return A reference to this Span object's first element
    */
    const T& front() const
    {
        assert(mData && mCount);
        return *mData;
    }

    /**
    Gets a reference to this Span object's first element
    @return A reference to this Span object's first element
    */
    T& front()
    {
        assert(mData && mCount);
        return *mData;
    }

    /**
    Gets a reference to this Span object's last element
    @return A reference to this Span object's last element
    */
    const T& back() const
    {
        assert(mData && mCount);
        return *(mData + mCount - 1);
    }

    /**
    Gets a reference to this Span object's last element
    @return A reference to this Span object's last element
    */
    T& back()
    {
        assert(mData && mCount);
        return *(mData + mCount - 1);
    }

    /**
    Gets a value indicating whether or not this Span is empty
    @return A value indicating whether or not this Span is empty
    */
    bool empty() const
    {
        return (mCount == 0);
    }

    /**
    Gets this Span object's count
    @return This Span object's count
    */
    size_t size() const
    {
        return mCount;
    }

    /**
    Gets this Span object's size in bytes
    @return This Span object's size in bytes
    */
    size_t size_bytes() const
    {
        return mCount * sizeof(T);
    }

    /**
    Gets a pointer to this Span object's underlying storage
    @return A pointer to this Span object's underlying storage
    */
    T* data() const
    {
        return mData;
    }

private:
    T* mData { nullptr };
    size_t mCount { 0 };
};

/**
TODO : Documentation
*/
template <typename T>
inline bool operator==(const Span<T>& lhs, const Span<T>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
TODO : Documentation
*/
template <typename T>
inline bool operator!=(const Span<T>& lhs, const Span<T>& rhs)
{
    return !(lhs == rhs);
}

/**
TODO : Documentation
*/
template <typename T>
inline bool operator<(const Span<T>& lhs, const Span<T>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
TODO : Documentation
*/
template <typename T>
inline bool operator>(const Span<T>& lhs, const Span<T>& rhs)
{
    return rhs < lhs;
}

/**
TODO : Documentation
*/
template <typename T>
inline bool operator<=(const Span<T>& lhs, const Span<T>& rhs)
{
    return !(rhs < lhs);
}

/**
TODO : Documentation
*/
template <typename T>
inline bool operator>=(const Span<T>& lhs, const Span<T>& rhs)
{
    return !(lhs < rhs);
}

} // namespace dst
