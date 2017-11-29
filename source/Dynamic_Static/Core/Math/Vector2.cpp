
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Math/Vector2.hpp"

namespace Dynamic_Static {

    const Vector2 Vector2::Zero  {  0,  0 };
    const Vector2 Vector2::One   {  1,  1 };
    const Vector2 Vector2::Up    {  0,  1 };
    const Vector2 Vector2::Down  {  0, -1 };
    const Vector2 Vector2::Left  { -1,  0 };
    const Vector2 Vector2::Right {  1,  0 };
    const Vector2 Vector2::UnitX {  1,  0 };
    const Vector2 Vector2::UnitY {  0,  1 };

} // namespace Dynamic_Static

#endif
