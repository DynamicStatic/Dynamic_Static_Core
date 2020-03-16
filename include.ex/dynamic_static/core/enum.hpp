
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <type_traits>

#define DYNAMIC_STATIC_ENABLE_BITWISE_OPERATORS(EnumType) \
template <>                                               \
struct dst::EnableBitwiseOperators<EnumType>              \
{                                                         \
    static constexpr bool value { true };                 \
};

namespace dst {

/**
TODO : Documentation
*/
template <typename EnumType>
struct EnableBitwiseOperators
{
    static constexpr bool value { false }; //!< TODO : Documentation
};

/**
TODO : Documentation
*/
template <typename EnumType>
using EnableBitwiseOperator = typename std::enable_if<EnableBitwiseOperators<EnumType>::value, EnumType>::type;

/**
TODO : Documentation
*/
template <typename EnumType>
EnableBitwiseOperator<EnumType> operator~(EnumType value)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(~static_cast<UnderlyingType>(value));
}

/**
TODO : Documentation
*/
template <typename EnumType>
EnableBitwiseOperator<EnumType> operator&(EnumType lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));
}

/**
TODO : Documentation
*/
template <typename EnumType>
EnableBitwiseOperator<EnumType> operator|(EnumType lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));
}

/**
TODO : Documentation
*/
template <typename EnumType>
EnableBitwiseOperator<EnumType> operator^(EnumType lhs, EnumType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumType>::type;
    return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) ^ static_cast<UnderlyingType>(rhs));
}

} // namespace dst
