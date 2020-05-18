
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

#include <algorithm>
#include <vector>

namespace dst {
namespace vector {

/**
Populates a given std::vector<> with objects converted from another std::vector<> using a given conversion function
@param <SourceType> The type of the source std::vector<>
@param <DestinationType> The type of the destination std::vector<>
@param <ConversionFunctionType> The type of the conversion function
@param [in] source The source std::vector<>
@param [out] destination The destination std::vector<>
@param [in] conversionFunction The conversion function
*/
template <
    typename SourceType,
    typename DestinationType,
    typename ConversionFunctionType
>
inline void convert(
    const std::vector<SourceType>& source,
    std::vector<DestinationType>& destination,
    ConversionFunctionType conversionFunction
)
{
    destination.clear();
    destination.reserve(source.size());
    for (const auto& object : source) {
        destination.push_back(conversionFunction(object));
    }
}

/**
Gets a std::vector<> populated with objects converted from another std::vector<> using a given conversion function
@param <SourceType> The type of the source std::vector<>
@param <DestinationType> The type of the destination std::vector<>
@param <ConversionFunctionType> The type of the conversion function
@param [in] source The source std::vector<>
@param [in] conversion The conversion function
@return A std::vector<> populated with the converted objects
*/
template <
    typename SourceType,
    typename DestinationType,
    typename ConversionFunctionType
>
inline std::vector<DestinationType> convert(
    const std::vector<SourceType>& source,
    ConversionFunctionType conversionFunction
)
{
    std::vector<DestinationType> destination;
    convert(source, destination, conversionFunction);
    return destination;
}

/**
Removes duplicate elements from a given std::vector<>
@param <T> T The type of the std::vector<> to remove duplicates from
@param [in, out] vctr The std::vector<> to remove duplicates from
    @note This function will sort the given std::vector<>
    @note The type of the given std::vector<> must provide operator< and operator==
    @note The type of the given std::vector<> must fulfill the Compare concept (http://en.cppreference.com/w/cpp/concept/Compare)
*/
template <typename T>
inline void remove_duplicates(std::vector<T>& vctr)
{
    std::sort(vctr.begin(), vctr.end());
    vctr.erase(std::unique(vctr.begin(), vctr.end()), vctr.end());
}

/**
Appends copies of the elements of one collection to the end of another
@param <T> The type of the collection to append to
@param <U> The type of the collection to copy from
@param [in] dst The collection to append to
@param [in] src The collection to copy from
*/
template <typename T, typename U>
inline void append(T& dst, const U& src)
{
    dst.insert(dst.end(), src.begin(), src.end());
}

/**
Gets the pointer obtained from a given std::vector<> object's data() member, or nullptr if the given std::vector<> is empty
@param <T> The type of the given std::vector<>
@param [in] vctr The std::vector<> to get the data() pointer from
@return The pointer obtained from the given std::vector<> object's data() member, or nullptr if the given std::vector<> is empty
*/
template <typename T>
inline const T* data(const std::vector<T>& vctr)
{
    return !vctr.empty() ? vctr.data() : nullptr;
}

/**
Gets the pointer obtained from a given std::vector<> object's data() member, or nullptr if the given std::vector<> is empty
@param <T> The type of the given std::vector<>
@param [in] vctr The std::vector<> to get the data() pointer from
@return The pointer obtained from the given std::vector<> object's data() member, or nullptr if the given std::vector<> is empty
*/
template <typename T>
inline T* data(std::vector<T>& vctr)
{
    return !vctr.empty() ? vctr.data() : nullptr;
}

} // namespace vector
} // namespace dst
