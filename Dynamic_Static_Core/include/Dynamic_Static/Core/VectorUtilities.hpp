
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

#include <vector>
#include <algorithm>
#include <functional>

namespace Dynamic_Static {
    /**
     * Converts an std::vector of a specified type to an std::vector of another specified type.
     * @param <T>  ConvertFrom The type to convert from
     * @param <T>  ConvertTo   The type to convert to
     * @param [in] source      The source std::vector
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
     * Converts an std::vector of a specified type to an std::vector of another specified type.
     * @param <T>  ConvertFrom The type to convert from
     * @param <T>  ConvertTo   The type to convert to
     * @param [in] source      The source std::vector
     * @param [in] destination The destination std::vector
     * @param [in] conversion  The conversion function to use
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
     * Removes duplicate elements from a specified std::vector
     * NOTE : This operation will sort the specified std::vector
     * NOTE : The element type of the std::vector must provide operator< and operator==
     * @param <T>  T The element type of the std::vector to remove duplicates from
     * @param [in] v The std::vector to remove duplicates from
     */
    template <typename T>
    void remove_duplicates(std::vector<T>& v)
    {
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
    }
}
