
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
TODO : Documentation
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
TODO : Documentation
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
TODO : Documentation
*/
template <typename T>
inline void remove_duplicates(std::vector<T>& vctr)
{
    std::sort(vctr.begin(), vctr.end());
    vctr.erase(std::unique(vctr.begin(), vctr.end()), vctr.end());
}

/**
TODO : Documentation
*/
template <typename T, typename U>
inline void append(T& vctr0, const U& vctr1)
{
    vctr0.insert(vctr0.end(), vctr1.begin(), vctr1.end());
}

} // namespace vector
} // namespace dst
