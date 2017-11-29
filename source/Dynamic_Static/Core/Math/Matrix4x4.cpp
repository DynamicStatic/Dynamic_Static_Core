
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Math/Matrix4x4.hpp"

namespace Dynamic_Static {

    const Matrix4x4 Matrix4x4::Identity {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

} // namespace Dynamic_Static

#endif
