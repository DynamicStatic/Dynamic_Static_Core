#if 0
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

#include <array>
#include <string>
#include <string_view>

namespace dst {

    /*!
    Provides a non-owning reference to a contiguous, null-terminated sequence of char-like objects.
    @param <CharType> This BasicStringView's cahracter type
    @param <TraitsType> This BasicStringView's character traits (optional = std::char_traits<CharType>)
    */
    template <typename CharType, typename TraitsType = std::char_traits<CharType>>
    class BasicStringView
        : private std::basic_string_view<CharType, TraitsType>
    {
        // FROM : Modified https://stackoverflow.com/a/41722533/3453616

    public:
        using BaseType = std::basic_string_view<CharType, TraitsType>;
        using BaseType::value_type;
        using BaseType::traits_type;
        using BaseType::pointer;
        using BaseType::const_pointer;
        using BaseType::reference;
        using BaseType::const_reference;
        using BaseType::iterator;
        using BaseType::const_iterator;
        using BaseType::reverse_iterator;
        using BaseType::const_reverse_iterator;
        using BaseType::difference_type;
        using BaseType::npos;
        using BaseType::size_type;

        /*
        Constructs an instance of BasicStringView.
        */
        inline constexpr BasicStringView() = default;

        /*!
        Constructs an instance of BasicStringView from a given BasicStringView.
        */
        inline constexpr BasicStringView(const BasicStringView&) = default;

        /*!
        Constructs an instance of BasicStringView.
        @param [in] cStr The const CharType* to reference
        */
        inline constexpr BasicStringView(const CharType* cStr)
            : BaseType(cStr ? cStr : "")
        {
            // TODO : The empty char array literal here will have to be dealt
            //  with to handle other CharTypes whenever it comes up.
        }

        /*!
        Constructs an instance of BasicStringView.
        @param [in] str The std::basic_string<> to reference
        */
        template <typename StrAllocatorType>
        inline constexpr BasicStringView(const std::basic_string<CharType, TraitsType, StrAllocatorType>& str)
            : BaseType(str)
        {
        }

        /*!
        Copies a given BasicStringView.
        */
        inline constexpr BasicStringView& operator=(const BasicStringView&) = default;

        /*!
        Gets a value indicating whether or not a given BasicStringView is equal to this BasicStringView.
        @param [in] other The BasicStringView to compare against this BasicStringView
        @return Whether or not the given BasicStringView is equal to this BasicStringView
        */
        inline constexpr bool operator==(const BasicStringView& other)
        {
            return *(BaseType*)this == *(BaseType*)&other;
        }

        /*!
        Gets a value indicating whether or not a given BasicStringView is inequal to this BasicStringView.
        @param [in] other The BasicStringView to compare against this BasicStringView
        @return Whether or not the given BasicStringView is inequal to this BasicStringView
        */
        inline constexpr bool operator!=(const BasicStringView& other)
        {
            return !(*this == other);
        }

        /*!
        Converts this BasicStringView to its referenced character array.
        @return Converts this BasicStringView to its referenced character array
        */
        inline constexpr operator const CharType* () const
        {
            return c_str();
        }

        using BaseType::operator[];

    public:
        using BaseType::begin;
        using BaseType::end;
        using BaseType::cbegin;
        using BaseType::cend;
        using BaseType::rbegin;
        using BaseType::rend;
        using BaseType::crbegin;
        using BaseType::crend;
        using BaseType::size;
        using BaseType::length;
        using BaseType::max_size;
        using BaseType::empty;
        using BaseType::at;
        using BaseType::front;
        using BaseType::back;
        using BaseType::data;
        using BaseType::swap;
        using BaseType::copy;
        using BaseType::substr;
        using BaseType::compare;
        using BaseType::find;

        /*!
        Gets this BasicStringView's referenced character array.
        @return This BasicStringView's referenced character array
        */
        inline constexpr const CharType* c_str() const
        {
            return data();
        }

        /*!
        Gets a std::basic_string_view<> constructed from this BasicStringView's referenced character array.
        @return A std::basic_string_view<> constructed from this BasicStringView's referenced character array.
        */
        inline constexpr std::basic_string_view<CharType, TraitsType> str_view() const
        {
            return *this;
        }

        /*!
        Gets a std::basic_string<> constructed from this BasicStringView's referenced character array.
        @param <AllocatorType> The type of allocator to construct the std::basic_string<> with (optional = std::allocator<CharType>)
        @param allocator The allocator to construct the std::basic_string<> with (optional = AllocatorType { })
        @return A std::basic_string<> constructed from this BasicStringView's referenced character array.
        */
        template <typename AllocatorType = std::allocator<CharType>>
        inline std::basic_string<CharType, TraitsType, AllocatorType> str(const AllocatorType& allocator = AllocatorType { }) const
        {
            return std::basic_string<CharType, Traits, AllocatorType>(begin(), end(), allocator);
        }
    };

    using StringView = BasicStringView<char>;
    using U16StringView = BasicStringView<char16_t>;
    using U32StringView = BasicStringView<char32_t>;
    using WStringView = BasicStringView<wchar_t>;

} // namespace dst

/*!
TODO : Documentation.
*/
template <typename CharType, typename TraitsType, typename AllocatorType>
inline constexpr bool operator==(
    const dst::BasicStringView<CharType, TraitsType>& lhs,
    const std::basic_string<CharType, TraitsType, AllocatorType>& rhs
)
{
    return lhs == dst::BasicStringView(rhs);
}

/*!
TODO : Documentation.
*/
template <typename CharType, typename TraitsType, typename AllocatorType>
inline constexpr bool operator==(
    const std::basic_string<CharType, TraitsType, AllocatorType>& lhs,
    const dst::BasicStringView<CharType, TraitsType>& rhs
)
{
    return dst::BasicStringView(lhs) == rhs;
}

/*!
TODO : Documentation.
*/
template <typename CharType, typename TraitsType, typename AllocatorType>
inline constexpr bool operator!=(
    const dst::BasicStringView<CharType, TraitsType>& lhs,
    const std::basic_string<CharType, TraitsType, AllocatorType>& rhs
)
{
    return !(lhs == dst::BasicStringView(rhs));
}

/*!
TODO : Documentation.
*/
template <typename CharType, typename TraitsType, typename AllocatorType>
inline constexpr bool operator!=(
    const std::basic_string<CharType, TraitsType, AllocatorType>& lhs,
    const dst::BasicStringView<CharType, TraitsType>& rhs
)
{
    return !(dst::BasicStringView(lhs) == rhs);
}
#endif