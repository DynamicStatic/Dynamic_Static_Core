
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
#include "dynamic_static/core/string.hpp"

#include <algorithm>
#include <ostream>
#include <string>

namespace dst {

/**
Provides facilites for incrmenting, decrementing, and printing a tab
*/
class Tab final
{
public:
    /**
    Provides automatic incrmenent and decrement for a given Tab within a given scope
    */
    class Scope final
    {
    public:
        /**
        Constructs an instance of Tab::Scope
        @param [in] tab The Tab to increment when this Tab::Scope is constructed
            @note The given Tab will be decremented when this Tab::Scope is destroyed
        */
        inline Scope(Tab& tab)
            : mpTab { &tab }
        {
            ++*mpTab;
        }

        /**
        Destroys this instance of Tab::Scope
            @note The Tab this Tab::Scope was constructed with will be decremented when this Tab::Scope is destroyed
        */
        inline ~Scope()
        {
            --*mpTab;
        }

        /**
        Converts this Tab::Scope to its Tab
        @return A const reference to this Tab::Scope object's Tab
        */
        inline operator const Tab&() const
        {
            return *mpTab;
        }

        /**
        Converts this Tab::Scope to its Tab
        @return A reference to this Tab::Scope object's Tab
        */
        inline operator Tab&()
        {
            return *mpTab;
        }

    private:
        Tab* mpTab { nullptr };
    };

    /**
    Increments this Tab object's count
    @return A reference to this Tab
    */
    inline Tab& operator++()
    {
        ++count;
        return *this;
    }

    /**
    Increments this Tab object's count
    @return A copy of this Tab before incrmenting its count
    */
    inline Tab operator++(int)
    {
        auto other = *this;
        ++count;
        return other;
    }

    /**
    Decrements this Tab object's count
    @return A reference to this Tab
    */
    inline Tab& operator--()
    {
        --count;
        return *this;
    }

    /**
    Decrements this Tab object's count
    @return A copy of this Tab before decrementing its count
    */
    inline Tab operator--(int)
    {
        auto other = *this;
        --count;
        return other;
    }

    /**
    Increments this Tab object's count by a specified value
    @param [in] value The value to increment this Tab object's count by
    @return A copy of this Tab with its count incremented by the given value
    */
    inline Tab operator+(int value) const
    {
        auto other = *this;
        other.count += value;
        return other;
    }

    /**
    Decrements this Tab object's count by a specified value
    @param [in] value The value to decrements this Tab object's count by
    @return A copy of this Tab with its count decremented by the given value
    */
    inline Tab operator-(int value) const
    {
        auto other = *this;
        other.count -= value;
        return other;
    }

    int count { 0 };        //!< This Tab object's count
    int size { 4 };         //!< This Tab object's size
    char character { ' ' }; //!< This Tab object's character
};

/**
Gets the std::string representation of a given Tab
@param [in] tab The Tab to get the std::string representation of
@return The std::string representation of the given Tab
*/
template <>
inline std::string to_string<Tab>(const Tab& tab)
{
    return std::string(std::max(0, tab.count * tab.size), tab.character);
}

/**
Writes a given Tab to a a given std::ostream
@param [in] stream The std::ostream to write the given Tab to
@param [in] tab The Tab to write to the given std::ostream
@return A reference to the given std::ostream
*/
inline std::ostream& operator<<(std::ostream& stream, const Tab& tab)
{
    stream << to_string(tab);
    return stream;
}

} // namespace dst
