#if 0
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

#include <functional>

namespace dst {

    /*!
    Represents an std::function<> with no return value.
    */
    template <typename ...Args>
    using Action = std::function<void(Args...)>;

} // namespace dst
#endif