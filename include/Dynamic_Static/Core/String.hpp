
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

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>

// NOTE : This file can be removed once std::string_view is fully supported.

namespace Dynamic_Static {

    /**
     * Provides a common interface for passing std::string, char*, char[], and char as function arguments.
     */
    class String final
    {
        // NOTE : This type's purpose is similar to gsl::string_span
        //        https://github.com/Microsoft/GSL

    private:
        std::string mStr;

    public:
        /**
         * Constructs an instance of String.
         */
        String() = default;

        /**
         * Constructs an instance of String.
         * @param [in] c This String's value
         */
        String(char c);

        /**
         * Constructs an instance of String.
         * @param [in] str This String's value
         */
        String(const char* str);

        /**
         * Constructs an instance of String.
         * @param [in] str This String's value
         */
        String(const std::string& str);

        /**
         * Converts this String to an std::string.
         */
        operator std::string&();

        /**
         * Converts this String to an std::string.
         */
        operator const std::string&() const;
    };

} // namespace Dynamic_Static
