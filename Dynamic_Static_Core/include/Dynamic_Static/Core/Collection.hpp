
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

#include <array>
#include <vector>
#include <cassert>
#include <initializer_list>

namespace Dynamic_Static {
    template <typename T>
    /**
     * TODO : Documentation.
     */
    class Collection final {
        // FROM : vk::ArrayProxy defined in vulkan.hpp (with slight modifications)...
        //        https://github.com/KhronosGroup/Vulkan-Hpp/blob/master/vulkan/vulkan.hpp

    private:
        T* m_data { nullptr };
        size_t m_count { 0 };

    public:
        /**
         * TODO : Documentation.
         */
        Collection() = default;

        /**
         * TODO : Documentation.
         */
        Collection(nullptr_t)
        {
        }

        /**
         * TODO : Documentation.
         */
        Collection(T& data)
            : m_data { &data }
            , m_count { 1 }
        {
        }

        /**
         * TODO : Documentation.
         */
        Collection(T* data, size_t count)
            : m_data { data }
            , m_count { count }
        {
        }

        /**
         * TODO : Documentation.
         */
        template <size_t N>
        Collection(std::array<typename std::remove_const<T>::type, N>& data)
            : m_data { data.data() }
            , m_count { N }
        {
        }

        /**
         * TODO : Documentation.
         */
        template <size_t N>
        Collection(const std::array<typename std::remove_const<T>::type, N>& data)
            : m_data { data.data() }
            , m_count { N }
        {
        }

        /**
         * TODO : Documentation.
         */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Collection(std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : m_data { data.data() }
            , m_count { data.size() }
        {
        }

        /**
         * TODO : Documentation.
         */
        template <class Allocator = std::allocator<typename std::remove_const<T>::type>>
        Collection(const std::vector<typename std::remove_const<T>::type, Allocator>& data)
            : m_data { data.data() }
            , m_count { data.size() }
        {
        }

        /**
         * TODO : Documentation.
         */
        Collection(const std::initializer_list<T>& data)
            : m_data { data.begin() }
            , m_count { data.end() - data.begin() }
        {
        }

        /**
         * Gets a reference to the element at a specified index.
         * @param [in] index The index of the element to get a reference to
         * @return A reference to the element at the specified index
         */
        T& operator[](size_t index)
        {
            return m_data[index];
        }

        /**
         * Gets a reference to the element at a specified index.
         * @param [in] index The index of the element to get a reference to
         * @return A reference to the element at the specified index
         */
        const T& operator[](size_t index) const
        {
            return m_data[index];
        }

    public:
        /**
         * Gets a pointer to the beginning of this Collection.
         * @return A pointer to the beginning of this Collection
         */
        T* begin()
        {
            return m_data;
        }

        /**
         * Gets a pointer to the beginning of this Collection.
         * @return A pointer to the beginning of this Collection
         */
        const T* begin() const
        {
            return m_data;
        }

        /**
         * Gets a pointer to the end of this Collection.
         * @return A pointer to the end of this Collection
         */
        T* end()
        {
            return m_data + m_count;
        }

        /**
         * Gets a pointer to the end of this Collection.
         * @return A pointer to the end of this Collection
         */
        const T* end() const
        {
            return m_data + m_count;
        }

        /**
         * Gets a reference to the first element of this Collection.
         * @return A reference to the first element of this Collection
         */
        T& front()
        {
            // TODO : assert(m_data && m_count);
            return *begin();
        }

        /**
         * Gets a reference to the first element of this Collection.
         * @return A reference to the first element of this Collection
         */
        const T& front() const
        {
            assert(m_data && m_count);
            return *begin();
        }

        /**
         * Gets a reference to the last element of this Collection.
         * @return A reference to the last element of this Collection
         */
        T& back()
        {
            assert(m_data && m_count);
            return *(end() - 1);
        }

        /**
         * Gets a reference to the last element of this Collection.
         * @return A reference to the last element of this Collection
         */
        const T& back() const
        {
            assert(m_data && m_count);
            return *(end() - 1);
        }

        /**
         * Gets a pointer to the underlying array serving as this Collection's storage.
         * @return A pointer to the underlying array serving as this Collection's storage
         */
        T* data()
        {
            return m_data;
        }

        /**
         * Gets a pointer to the underlying array serving as this Collection's storage.
         * @return A pointer to the underlying array serving as this Collection's storage
         */
        const T* data() const
        {
            return m_data;
        }

        /**
         * Gets the number of elements in this Collection.
         * @return The number of elements in this Collection
         */
        size_t size() const
        {
            return m_count;
        }

        /**
         * Gets the size of this Collection in bytes.
         * @return The size of this Collection in bytes
         */
        size_t byte_size() const
        {
            return m_count * sizeof(T);
        }

        /**
         * Gets a value indicating whether or not this Collection is empty
         * @return Whether or not this Collection is empty
         */
        bool empty() const
        {
            return m_count == 0;
        }
    };
}
