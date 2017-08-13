
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/NotImplementedError.hpp"

namespace Dynamic_Static {

    NotImplementedError::NotImplementedError(const std::string& message)
        : std::logic_error("Not implemented" + (!message.empty() ? " : " + message : message))
    {
    }

} // namespace Dynamic_Static
