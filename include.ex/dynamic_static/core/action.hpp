
/*
==========================================
  Copyright (c) 2016-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <functional>

namespace dst {

/**
TODO : Documentation
*/
template <typename ...Args>
using Action = std::function<void(Args...)>;

} // namespace dst
