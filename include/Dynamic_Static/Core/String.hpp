
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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
