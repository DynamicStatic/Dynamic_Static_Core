
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/core/enum.hpp"

#include "catch2/catch.hpp"

#include <type_traits>

namespace dst {
namespace tests {

enum class WidgetType
{
    Unknown = 0,
    Foo     = 1,
    Bar     = 1 << 1,
    Baz     = 1 << 2,
    Qux     = 1 << 3,
};

template <>
struct EnumClassOperators<WidgetType>
{
    static constexpr bool enabled { true };
};

/**
Validates that enum class operator overloads work correctly
*/
TEST_CASE("EnumClassOperators<>", "[EnumClassOperators<>]")
{
    WidgetType widgetType = WidgetType::Baz;
    using UnderlyingType = typename std::underlying_type<WidgetType>::type;
    auto valueType = (UnderlyingType)widgetType;
    auto widgetTypeResult = widgetType;
    auto valueTypeResult = valueType;
    SECTION("operator+()")
    {
        widgetTypeResult = widgetType + WidgetType::Qux;
        valueTypeResult = valueType + (UnderlyingType)WidgetType::Qux;
        widgetTypeResult = widgetType + 3;
        valueTypeResult = valueType + 3;
    }
    SECTION("operator+=()")
    {
        widgetTypeResult += WidgetType::Bar;
        valueTypeResult += (UnderlyingType)WidgetType::Bar;
        widgetTypeResult += 3;
        valueTypeResult += 3;
    }
    SECTION("operator++()")
    {
        auto widgetTypeResultPrefixIncrement = ++widgetTypeResult;
        auto widgetTypeResultPostfixIncrement = widgetTypeResult++;
        auto valueTypeResultPrefixIncrement = ++valueTypeResult;
        auto valueTypeResultPostfixIncrement = valueTypeResult++;
        CHECK(widgetTypeResultPrefixIncrement == (WidgetType)valueTypeResultPrefixIncrement);
        CHECK(widgetTypeResultPostfixIncrement == (WidgetType)valueTypeResultPostfixIncrement);
    }
    SECTION("operator-()")
    {
        widgetTypeResult = widgetType - WidgetType::Qux;
        valueTypeResult = valueType - (UnderlyingType)WidgetType::Qux;
        widgetTypeResult = widgetType - 3;
        valueTypeResult = valueType - 3;
    }
    SECTION("operator-=()")
    {
        widgetTypeResult -= WidgetType::Bar;
        valueTypeResult -= (UnderlyingType)WidgetType::Bar;
        widgetTypeResult -= 3;
        valueTypeResult -= 3;
    }
    SECTION("operator--()")
    {
        auto widgetTypeResultPrefixIncrement = --widgetTypeResult;
        auto widgetTypeResultPostfixIncrement = widgetTypeResult--;
        auto valueTypeResultPrefixIncrement = --valueTypeResult;
        auto valueTypeResultPostfixIncrement = valueTypeResult--;
        CHECK(widgetTypeResultPrefixIncrement == (WidgetType)valueTypeResultPrefixIncrement);
        CHECK(widgetTypeResultPostfixIncrement == (WidgetType)valueTypeResultPostfixIncrement);
    }
    SECTION("operator~()")
    {
        widgetTypeResult = ~widgetTypeResult;
        valueTypeResult = ~valueTypeResult;
    }
    SECTION("operator&()")
    {
        widgetTypeResult = widgetTypeResult & WidgetType::Foo;
        valueTypeResult = valueTypeResult & (UnderlyingType)WidgetType::Foo;
    }
    SECTION("operator&=()")
    {
        widgetTypeResult &= WidgetType::Qux;
        valueTypeResult &= (UnderlyingType)WidgetType::Qux;
    }
    SECTION("operator|()")
    {
        widgetTypeResult = widgetTypeResult | WidgetType::Foo;
        valueTypeResult = valueTypeResult | (UnderlyingType)WidgetType::Foo;
    }
    SECTION("operator|=()")
    {
        widgetTypeResult |= WidgetType::Bar;
        valueTypeResult |= (UnderlyingType)WidgetType::Bar;
    }
    SECTION("operator^()")
    {
        widgetTypeResult = widgetTypeResult ^ WidgetType::Foo;
        valueTypeResult = valueTypeResult ^ (UnderlyingType)WidgetType::Foo;
    }
    SECTION("operator^=()")
    {
        widgetTypeResult ^= WidgetType::Qux;
        valueTypeResult ^= (UnderlyingType)WidgetType::Qux;
    }
    SECTION("operator<<()")
    {
        widgetTypeResult = widgetType << WidgetType::Qux;
        valueTypeResult = valueType << (UnderlyingType)WidgetType::Qux;
        widgetTypeResult = widgetType << 3;
        valueTypeResult = valueType << 3;
    }
    SECTION("operator<<=()")
    {
        widgetTypeResult <<= WidgetType::Qux;
        valueTypeResult <<= (UnderlyingType)WidgetType::Qux;
        widgetTypeResult <<= 3;
        valueTypeResult <<= 3;
    }
    SECTION("operator>>()")
    {
        widgetTypeResult = widgetType >> WidgetType::Qux;
        valueTypeResult = valueType >> (UnderlyingType)WidgetType::Qux;
        widgetTypeResult = widgetType >> 3;
        valueTypeResult = valueType >> 3;
    }
    SECTION("operator>>=()")
    {
        widgetTypeResult >>= WidgetType::Qux;
        valueTypeResult >>= (UnderlyingType)WidgetType::Qux;
        widgetTypeResult >>= 3;
        valueTypeResult >>= 3;
    }
    CHECK(widgetTypeResult == (WidgetType)valueTypeResult);
}

} // namespace tests
} // namespace dst
