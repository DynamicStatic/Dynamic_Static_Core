
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/ToString.hpp"

#include <string>
#include <iostream>

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class IPrintable {
    public:
        /**
         * Writes this IPrintable to a specified std::ostream.
         * @param [in] stream The std::ostream to write this IPrintable to
         * @return The std::ostream this IPrintable was written to
         */
        virtual std::ostream& operator<<(std::ostream& stream) const;

    public:
        /**
         * Gets this IPrintable's std::string representation.
         * @return This IPrintable's std::string representation
         */
        virtual std::string to_string() const = 0;

        /**
         * Gets this IPrintable's std::wstring representation.
         * @return This IPrintable's std::wstring representation
         */
        virtual std::wstring to_wstring() const;
    };
}

namespace Dynamic_Static {
    /**
     * Gets the specified IPrintable's std::string representation.
     * @return The specified IPrintable's std::string representation
     */
    template <>
    std::string to_string<IPrintable>(const IPrintable& printable);

    /**
     * Gets the specified IPrintable's std::string representation.
     * @return The specified IPrintable's std::string representation
     */
    template <>
    std::wstring to_wstring<IPrintable>(const IPrintable& printable);
}
