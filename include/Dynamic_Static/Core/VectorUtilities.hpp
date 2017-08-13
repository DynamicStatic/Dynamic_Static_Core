
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace Dynamic_Static {

    /**
     * Populates a given std::vector with objects converted from another std::vector using a given conversion function.
     * @param <T>              The type of the source std::vector
     * @param <U>              The type of the destination std::vector
     * @param <Conversion>     The type of the conversion function
     * @param [in] source      The source std::vector
     * @param [in] destination The destination std::vector
     * @param [in] conversion  The conversion function
     */
    template <typename T, typename U, typename Conversion>
    void convert(
        const std::vector<T>& source,
        std::vector<U>& destination,
        Conversion conversion)
    {
        destination.clear();
        destination.reserve(source.size());
        for (const auto& object : source) {
            destination.push_back(conversion(object));
        }
    }

    /**
     * Gets a std::vector populated with objects converted from another std::vector using a given conversion function.
     * @param <T>             The type of the source std::vector
     * @param <U>             The type of the destination std::vector
     * @param <Conversion>    The type of the conversion function
     * @param [in] source     The source std::vector
     * @param [in] conversion The conversion function
     * @return A std::vector containing the converted objects
     */
    template <typename T, typename U, typename Conversion>
    std::vector<U> convert(
        const std::vector<T>& source,
        Conversion conversion)
    {
        std::vector<U> destination;
        convert(source, destination, conversion);
        return destination;
    }

    /**
     * Removes duplicate elements from a given std::vector
     * \n NOTE : This operation will sort the given std::vector
     * \n NOTE : The type of the given std::vector must provide operator< and operator==
     * \n        The type of the given std::vector must fulfill the Compare concept
     * \n        (http://en.cppreference.com/w/cpp/concept/Compare)
     * @param <T>  T    The type of the std::vector to remove duplicates from
     * @param [in] vctr The std::vector to remove duplicates from
     */
    template <typename T>
    void remove_duplicates(std::vector<T>& vctr)
    {
        std::sort(vctr.begin(), vctr.end());
        vctr.erase(std::unique(vctr.begin(), vctr.end()), vctr.end());
    }

} // namespace Dynamic_Static
