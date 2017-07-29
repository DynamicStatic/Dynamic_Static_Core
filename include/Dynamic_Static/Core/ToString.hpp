
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

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

#include "gsl/string_span"

#include <sstream>
#include <string>

namespace Dynamic_Static {

    /**
     * Gets the std::string representation of a given int.
     * @return The std::string representation of the given int
     */
    inline std::string to_string(int value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given long int.
     * @return The std::string representation of the given long int
     */
    inline std::string to_string(long value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given long long int.
     * @return The std::string representation of the given long long int
     */
    inline std::string to_string(long long value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given unsigned int.
     * @return The std::string representation of the given unsigned int
     */
    inline std::string to_string(unsigned int value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given int.
     * @return The std::string representation of the given int
     */
    inline std::string to_string(unsigned long int value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given unsigned long long int.
     * @return The std::string representation of the given unsigned long long int
     */
    inline std::string to_string(unsigned long long int value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given float.
     * @return The std::string representation of the given float
     */
    inline std::string to_string(float value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given double.
     * @return The std::string representation of the given double
     */
    inline std::string to_string(double value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given long double.
     * @return The std::string representation of the given long double
     */
    inline std::string to_string(long double value)
    {
        return std::to_string(value);
    }

    /**
     * Gets the std::string representation of a given gsl::string_span.
     * @return The std::string representation of the given gsl::string_span
     */
    inline std::string to_string(gsl::string_span<> strSpan)
    {
        return gsl::to_string(strSpan);
    }

    /**
     * Gets the std::string representation of a given object which defines a public to_string() method.
     * @param <T>  The type of the given object
     * @return The std::string representation of the given object
     */
    template <typename T>
    inline std::string to_string(const T& object)
    {
        return object.to_string();
    }

    /**
     * Gets the std::string represetnation of the hex value of a given integral value.
     * @param <T> The type of the given value
     * @return The std::string representation of the hex value of the given value
     */
    template <typename T>
    inline std::string to_hex_string(T value)
    {
        static_assert(
            std::is_integral<T>::value,
            "dst::to_hex_string() can only be used with built in integral types"
        );

        std::stringstream strStr;
        strStr << "0x" << std::hex << value;
        return strStr.str();
    }

} // namespace Dynamic_Static
