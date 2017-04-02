
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

#include "Dynamic_Static/Core/Defines.hpp"

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

namespace Dynamic_Static {
    /**
     * Converts an std::vector of one type to an std::vector of another type.
     * @param <T> ConvertFrom The type to convert from
     * @param <T> ConvertTo The type to convert to
     * @param [in] source The source std::vector
     * @param [in] destination The destination std::vector
     * @param [in] conversion The conversion function to use
     */
    template <typename ConvertFrom, typename ConvertTo>
    void convert(
        const std::vector<ConvertFrom>& source,
        std::vector<ConvertTo>& destination,
        std::function<ConvertTo(const ConvertFrom&)> conversion)
    {
        destination.clear();
        destination.reserve(source.size());
        for (const auto& object : source) {
            destination.push_back(conversion(object));
        }
    }

    /**
     * Converts an std::vector of one type to an std::vector of another type.
     * @param <T> ConvertFrom The type to convert from
     * @param <T> ConvertTo The type to convert to
     * @param [in] source The source std::vector
     * @param [in] conversion  The conversion function to use
     * @return An std::vector containing the converted objects
     */
    template <typename ConvertFrom, typename ConvertTo>
    std::vector<ConvertTo> convert(
        const std::vector<ConvertFrom>& source,
        std::function<ConvertTo(const ConvertFrom&)> conversion)
    {
        std::vector<ConvertTo> destination;
        convert(source, destination, conversion);
        return destination;
    }

    /**
     * Removes duplicate elements from an std::vector
     * NOTE : This operation will sort the std::vector
     * NOTE : The element type of the std::vector must provide operator< and operator==
     * @param <T> T The element type of the std::vector to remove duplicates from
     * @param [in] v The std::vector to remove duplicates from
     */
    template <typename T>
    void remove_duplicates(std::vector<T>& v)
    {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }

    /**
     * Takes ownership of an std::unique_ptr from an std::vector.
     * \n NOTE : This function returns a null std::unique_ptr if the target isn't found
     * @param <T> The type of the std::unique_ptr and std::vector
     * @param [in] target The std::unique_ptr to take
     * @param [in] v The std::vector to take the std::unique_ptr from
     * @return The std::unique_ptr taken from the std::vector
     */
    template <typename T>
    std::unique_ptr<T> take_ownership(const std::unique_ptr<T>& target, std::vector<std::unique_ptr<T>>& v)
    {
        return take_ownership(*target, v);
    }

    /**
     * Takes ownership of an std::unique_ptr from an std::vector.
     * \n NOTE : This function returns a null std::unique_ptr if the target isn't found
     * @param <T> The type of the std::unique_ptr and std::vector
     * @param [in] target The object pointed to by the std::unique_ptr to take
     * @param [in] v The std::vector to take the std::unique_ptr from
     * @return The std::unique_ptr taken from the std::vector
     */
    template <typename T>
    std::unique_ptr<T> take_ownership(const T& target, std::vector<std::unique_ptr<T>>& v)
    {
        auto uptr = std::unique_ptr<T>(nullptr);
        auto itr = std::find_if(
            v.begin(),
            v.end(),
            [&](std::unique_ptr<T>& element)
            {
                return element.get() == &target;
            }
        );

        if (itr != v.end()) {
            uptr = std::unique_ptr<T>(itr->release());
            v.erase(itr);
        }

        return uptr;
    }
} // namespace Dynamic_Static
