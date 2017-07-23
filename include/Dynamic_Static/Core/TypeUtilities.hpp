
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
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
