
/*
==========================================
  Copyright (c) 2015-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <mutex>
#include <queue>
#include <thread>

namespace dst {

/**
TODO : Documentation
*/
class Worker final
{
public:

private:
    std::mutex mMutex;
    std::thread mThread;
};

} // namespace dst
