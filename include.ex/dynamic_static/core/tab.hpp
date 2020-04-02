
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
#include "dynamic_static/core/to-string.hpp"

#include <algorithm>
#include <ostream>
#include <string>

namespace dst {

/**
TODO : Documentation
*/
class Tab final
{
public:
    /**
    TODO : Documentation
    */
    class Scope final
    {
    public:
        /**
        Constructs an instance of Tab::Scope
        TODO : Documentation
        */
        inline Scope(Tab& tab)
            : mTab { &tab }
        {
            ++*mTab;
        }

        /**
        Destroys this instance of Tab::Scope
        TODO : Documentation
        */
        inline ~Scope()
        {
            --*mTab;
        }

    private:
        Tab* mTab { nullptr };
    };

    /**
    TODO : Documentation
    */
    inline Tab& operator++()
    {
        ++count;
        return *this;
    }

    /**
    TODO : Documentation
    */
    inline Tab operator++(int)
    {
        auto other = *this;
        ++count;
        return other;
    }

    /**
    TODO : Documentation
    */
    inline Tab& operator--()
    {
        --count;
        return *this;
    }

    /**
    TODO : Documentation
    */
    inline Tab operator--(int)
    {
        auto other = *this;
        --count;
        return other;
    }

    int count { 0 };
    int size { 4 };
    char character { ' ' };
};

/**
TODO : Documentation
*/
template <>
inline std::string to_string<Tab>(const Tab& tab)
{
    return std::string(std::max(0, tab.count * tab.size), tab.character);
}

} // namespace

/**
TODO : Documentation
*/
std::ostream& operator<<(std::ostream& stream, const dst::Tab& tab)
{
    stream << to_string(tab);
    return stream;
}
