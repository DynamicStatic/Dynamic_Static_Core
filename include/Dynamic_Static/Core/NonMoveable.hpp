
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

namespace Dynamic_Static {

    /**
     * Removes a derived class's move and move assignment constructors.
     */
    class NonMoveable
    {
    protected:
        NonMoveable() = default;
        ~NonMoveable() = default;

    private:
        NonMoveable(NonMoveable&&) = delete;
        NonMoveable& operator=(NonMoveable&&) = delete;
    };

} // namespace Dynamic_Static
