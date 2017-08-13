
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <type_traits>

namespace Dynamic_Static {
namespace detail {

    template <typename TypeBegin, typename ...Types>
    struct Index;

    template <typename TypeBegin, typename ...Types>
    struct Index<TypeBegin, TypeBegin, Types...>
        : std::integral_constant<size_t, 0>
    {
    };

    template <typename TypeItr, typename TypeItrIncr, typename ...Types>
    struct Index<TypeItr, TypeItrIncr, Types...>
        : std::integral_constant<size_t, Index<TypeItr, Types...>::value + 1>
    {
        // FROM : http://stackoverflow.com/a/30736376/3453616
    };

} // namespace detail
} // namespace Dynamic_Static

namespace Dynamic_Static {

    /**
     * Gets the index of a the first occurence of a given type in a template parameter pack.
     * @param <Type>  The type to get the index of
     * @param <Types> The parameter pack containing the type to get the index of
     * @return The index of the type in the template parameter pack
     */
    template <typename Type, typename ...Types>
    constexpr size_t type_index()
    {
        return dst::detail::Index<Type, Types...>::value;
    }

} // namespace Dynamic_Static
