
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static
{
    /**
     * Represents a 4 channel color.
     */
    struct Color
        : public glm::vec4
    {
    public:
        static const Color White;
        static const Color Black;
        static const Color Transparent;
        static const Color AliceBlue;
        static const Color AntiqueWhite;
        static const Color Aqua;
        static const Color Aquamarine;
        static const Color Azure;
        static const Color Beige;
        static const Color Bisque;
        static const Color BlanchedAlmond;
        static const Color Blue;
        static const Color BlueViolet;
        static const Color Brown;
        static const Color BurlyWood;
        static const Color CadetBlue;
        static const Color Chartreuse;
        static const Color Chocolate;
        static const Color Coral;
        static const Color CornflowerBlue;
        static const Color Cornsilk;
        static const Color Crimson;
        static const Color Cyan;
        static const Color DarkBlue;
        static const Color DarkCyan;
        static const Color DarkGoldenrod;
        static const Color DarkGray;
        static const Color DarkGreen;
        static const Color DarkKhaki;
        static const Color DarkMagenta;
        static const Color DarkOliveGreen;
        static const Color DarkOrange;
        static const Color DarkOrchid;
        static const Color DarkRed;
        static const Color DarkSalmon;
        static const Color DarkSeaGreen;
        static const Color DarkSlateBlue;
        static const Color DarkSlateGray;
        static const Color DarkTurquoise;
        static const Color DarkViolet;
        static const Color DeepPink;
        static const Color DeepSkyBlue;
        static const Color DimGray;
        static const Color DodgerBlue;
        static const Color Firebrick;
        static const Color FloralWhite;
        static const Color ForestGreen;
        static const Color Fuchsia;
        static const Color Gainsboro;
        static const Color GhostWhite;
        static const Color Gold;
        static const Color Goldenrod;
        static const Color Gray;
        static const Color Green;
        static const Color GreenYellow;
        static const Color Honeydew;
        static const Color HotPink;
        static const Color IndianRed;
        static const Color Indigo;
        static const Color Ivory;
        static const Color Khaki;
        static const Color Lavender;
        static const Color LavenderBlush;
        static const Color LawnGreen;
        static const Color LemonChiffon;
        static const Color LightBlue;
        static const Color LightCoral;
        static const Color LightCyan;
        static const Color LightGoldenrodYellow;
        static const Color LightGray;
        static const Color LightGreen;
        static const Color LightPink;
        static const Color LightSalmon;
        static const Color LightSeaGreen;
        static const Color LightSkyBlue;
        static const Color LightSlateGray;
        static const Color LightSteelBlue;
        static const Color LightYellow;
        static const Color Lime;
        static const Color LimeGreen;
        static const Color Linen;
        static const Color Magenta;
        static const Color Maroon;
        static const Color MediumAquamarine;
        static const Color MediumBlue;
        static const Color MediumOrchid;
        static const Color MediumPurple;
        static const Color MediumSeaGreen;
        static const Color MediumSlateBlue;
        static const Color MediumSpringGreen;
        static const Color MediumTurquoise;
        static const Color MediumVioletRed;
        static const Color MidnightBlue;
        static const Color MintCream;
        static const Color MistyRose;
        static const Color Moccasin;
        static const Color NavajoWhite;
        static const Color Navy;
        static const Color OldLace;
        static const Color Olive;
        static const Color OliveDrab;
        static const Color Orange;
        static const Color OrangeRed;
        static const Color Orchid;
        static const Color PaleGoldenrod;
        static const Color PaleGreen;
        static const Color PaleTurquoise;
        static const Color PaleVioletRed;
        static const Color PapayaWhip;
        static const Color PeachPuff;
        static const Color Peru;
        static const Color Pink;
        static const Color Plum;
        static const Color PowderBlue;
        static const Color Purple;
        static const Color Red;
        static const Color RosyBrown;
        static const Color RoyalBlue;
        static const Color SaddleBrown;
        static const Color Salmon;
        static const Color SandyBrown;
        static const Color SeaGreen;
        static const Color SeaShell;
        static const Color Sienna;
        static const Color Silver;
        static const Color SkyBlue;
        static const Color SlateBlue;
        static const Color SlateGray;
        static const Color Snow;
        static const Color SpringGreen;
        static const Color SteelBlue;
        static const Color Tan;
        static const Color Teal;
        static const Color Thistle;
        static const Color Tomato;
        static const Color Turquoise;
        static const Color Violet;
        static const Color Wheat;
        static const Color WhiteSmoke;
        static const Color Yellow;
        static const Color YellowGreen;

    public:
        using glm::vec4::tvec4;

    public:
        /**
         * Gets the std::string representation of this Vector4.
         * @return The std::string representation of this Vector4
         */
        inline std::string to_string() const
        {
            return glm::to_string(*this);
        }
    };

    static_assert(
        sizeof(Color) == sizeof(glm::vec4),
        "sizeof(Color) must equal sizeof(glm::vec4)"
    );
} // namespace Dynamic_Static
