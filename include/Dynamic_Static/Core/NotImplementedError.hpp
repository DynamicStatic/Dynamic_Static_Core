
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <stdexcept>
#include <string>

namespace Dynamic_Static {

    /**
     * Exception throw when a requested function or operation is not implemented.
     */
    class NotImplementedError
        : public std::logic_error
    {
    public:
        /**
         * Constructs an instance of NotImplementedError.
         * @param [in] message This NotImplementedError's message
         */
        NotImplementedError(const std::string& message = std::string());
    };

} // namespace Dynamic_Static
