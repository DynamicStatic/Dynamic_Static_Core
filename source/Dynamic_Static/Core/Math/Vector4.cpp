
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Math/Vector4.hpp"

namespace Dynamic_Static {

    const Vector4 Vector4::Zero     {  0,  0,  0,  0 };
    const Vector4 Vector4::One      {  1,  1,  1,  1 };
    const Vector4 Vector4::Up       {  0,  1,  0,  0 };
    const Vector4 Vector4::Down     {  0, -1,  0,  0 };
    const Vector4 Vector4::Left     { -1,  0,  0,  0 };
    const Vector4 Vector4::Right    {  1,  0,  0,  0 };
    const Vector4 Vector4::Forward  {  0,  0, -1,  0 };
    const Vector4 Vector4::Backward {  0,  0,  1,  0 };
    const Vector4 Vector4::UnitX    {  1,  0,  0,  0 };
    const Vector4 Vector4::UnitY    {  0,  1,  0,  0 };
    const Vector4 Vector4::UnitZ    {  0,  0,  1,  0 };
    const Vector4 Vector4::UnitW    {  0,  0,  0,  1 };

} // namespace Dynamic_Static

#endif
