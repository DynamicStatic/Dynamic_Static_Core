
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

/**
Enables operator overloads for a specified enum class type
@param <EnumClassType> The enum class type to enable operator overloads for
    @note To enable enum class operator overloads specialize this struct with `enabled` initialized to `true`
    @example

        namespace widgets {

        enum class WidgetType
        {
            Unknown,
            Foo,
            Bar,
            Baz,
            Qux,
        };

        template <>
        struct EnumClassOperators<WidgetType>
        {
            static constexpr bool enabled { true };
        };

        } // namespace widgets

*/
template <typename EnumClassType>
struct EnumClassOperators
{
    static constexpr bool enabled { false };
};

template <typename EnumClassType>
using EnumClassOperator = typename std::enable_if<EnumClassOperators<EnumClassType>::enabled, EnumClassType>::type;

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator+(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs + (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator+(EnumClassType lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    return (EnumClassType)((typename std::underlying_type<EnumClassType>::type)lhs + rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator+=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator+=(EnumClassType& lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator++(EnumClassType& value)
{
    value += 1;
    return value;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator++(EnumClassType& value, int)
{
    auto currentValue = value;
    value += 1;
    return currentValue;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator-(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs - (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator-(EnumClassType lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    return (EnumClassType)((typename std::underlying_type<EnumClassType>::type)lhs - rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator-=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator-=(EnumClassType& lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator--(EnumClassType& value)
{
    value = (EnumClassType)((typename std::underlying_type<EnumClassType>::type)value - 1);
    return value;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator--(EnumClassType& value, int)
{
    auto currentValue = value;
    value -= 1;
    return currentValue;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator~(EnumClassType value)
{
    return (EnumClassType)(~(typename std::underlying_type<EnumClassType>::type)value);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator&(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs & (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator&=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs & rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator|(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs | (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator|=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator^(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs ^ (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator^=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs ^ rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator<<(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs << (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator<<(EnumClassType lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    return (EnumClassType)((typename std::underlying_type<EnumClassType>::type)lhs << rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator<<=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs << rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator<<=(EnumClassType& lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    lhs = lhs << rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator>>(EnumClassType lhs, EnumClassType rhs)
{
    using UnderlyingType = typename std::underlying_type<EnumClassType>::type;
    return (EnumClassType)((UnderlyingType)lhs >> (UnderlyingType)rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType> operator>>(EnumClassType lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    return (EnumClassType)((typename std::underlying_type<EnumClassType>::type)lhs >> rhs);
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator>>=(EnumClassType& lhs, EnumClassType rhs)
{
    lhs = lhs >> rhs;
    return lhs;
}

template <typename EnumClassType>
EnumClassOperator<EnumClassType>& operator>>=(EnumClassType& lhs, typename std::underlying_type<EnumClassType>::type rhs)
{
    lhs = lhs >> rhs;
    return lhs;
}
