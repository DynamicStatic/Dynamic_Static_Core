
/*
==========================================
    Copyright (c) 2017 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <functional>

namespace Dynamic_Static {

    /**
     * Represents a std::function with no return value.
     */
    template <typename ...Args>
    using Action = std::function<void(Args...)>;

} // namespace Dynamic_Static
