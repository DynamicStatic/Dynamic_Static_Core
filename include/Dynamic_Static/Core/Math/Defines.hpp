
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#ifndef DYNAMIC_STATIC_CORE_GLM_DISABLED
#ifndef DYNAMIC_STATIC_CORE_GLM_ENABLED
#define DYNAMIC_STATIC_CORE_GLM_ENABLED
#endif
#endif

#ifdef DYNAMIC_STATIC_CORE_GLM_ENABLED

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#ifdef DYNAMIC_STATIC_MSVC
#pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"
#ifdef DYNAMIC_STATIC_MSVC
#pragma warning(pop)
#endif

#endif // DYNAMIC_STATIC_CORE_GLM_ENABLED
