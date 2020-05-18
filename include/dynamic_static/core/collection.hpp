
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

namespace dst {
namespace collection {

/**
TODO : Documentation
*/
template <typename T, typename U>
inline void append(T& collection0, const U& collection1)
{
    collection0.insert(collection1.begin(), collection1.end());
}

} // namespace collection
} // namespace dst
