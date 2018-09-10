
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
#include "Dynamic_Static/Core/Span.hpp"

#include <algorithm>
#include <vector>

namespace Dynamic_Static {

    /*!
    Populates a given std::vector<> with objects converted from another std::vector<> using a given conversion function.
    @param <SourceType> The type of the source std::vector<>
    @param <DestinationType> The type of the destination std::vector<>
    @param <ConversionFunctionType> The type of the conversion function
    @param [in] source The source std::vector<>
    @param [out] destination The destination std::vector<>
    @param [in] conversion The conversion function
    */
    template <
        typename SourceType,
        typename DestinationType,
        typename ConversionFunctionType
    >
    inline void convert(
        const std::vector<SourceType>& source,
        std::vector<DestinationType>& destination,
        ConversionFunctionType conversion
    )
    {
        destination.clear();
        destination.reserve(source.size());
        for (const auto& object : source) {
            destination.push_back(conversion(object));
        }
    }

    /*!
    Gets a std::vector<> populated with objects converted from another std::vector<> using a given conversion function.
    @param <SourceType> The type of the source std::vector<>
    @param <DestinationType> The type of the destination std::vector<>
    @param <ConversionFunctionType> The type of the conversion function
    @param [in] source The source std::vector<>
    @param [in] conversion The conversion function
    @return A std::vector<> containing the converted objects
    */
    template <
        typename SourceType,
        typename DestinationType,
        typename ConversionFunctionType
    >
    inline std::vector<DestinationType> convert(
        const std::vector<SourceType>& source,
        ConversionFunctionType conversion
    )
    {
        std::vector<DestinationType> destination;
        convert(source, destination, conversion);
        return destination;
    }

    /*!
    Removes duplicate elements from a given std::vector<>.
    \n NOTE : This function will sort the given std::vector<>
    \n NOTE : The type of the given std::vector<> must provide operator< and operator==
    \n NOTE : The type of the given std::vector<> must fulfill the Compare concept (http://en.cppreference.com/w/cpp/concept/Compare)
    @param <T> T The type of the std::vector<> to remove duplicates from
    @param [in, out] vctr The std::vector<> to remove duplicates from
    */
    template <typename T>
    inline void remove_duplicates(std::vector<T>& vctr)
    {
        std::sort(vctr.begin(), vctr.end());
        vctr.erase(std::unique(vctr.begin(), vctr.end()), vctr.end());
    }

} // namespace Dynamic_Static
