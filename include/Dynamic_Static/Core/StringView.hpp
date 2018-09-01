
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

#include <string_view>

namespace Dynamic_Static {

    /*!
    Provides a non-owning reference to a contiguous sequence of char-like objects.
    */
    class StringView
        : public std::string_view
    {
    public:
        /*!
        Constructs an instance of dst::string_view.
        @param [in] strView The std::string_view to reference
        */
        StringView(const std::string_view& strView)
            : std::string_view(strView)
        {
        }

        /*!
        Constructs an instance of dst::string_view.
        @param [in] strView The std::string to reference
        */
        StringView(const std::string& str)
            : std::string_view(str)
        {
        }

        /*!
        Constructs an instance of dst::string_view.
        @param [in] strView The const char* to reference
        */
        StringView(const char* cStr)
            : std::string_view(cStr, cStr ? strlen(cStr) : 0)
        {
        }

        /*!
        Constructs an instance of dst::string_view.
        @param [in] strView The char to reference
        */
        StringView(const char& c)
            : std::string_view(&c, 1)
        {
        }
    };

} // namespace Dynamic_Static
