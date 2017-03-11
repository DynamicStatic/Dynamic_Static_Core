
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Math/Defines.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"

namespace Dynamic_Static {
    namespace Math {
        struct Color
            : public Vector4 {
        public:
            /**
             * TODO : Documentation.
             */
            inline Color(float r, float g, float b)
                : Vector4(r, g, b, 1)
            {
            }

            /**
             * TODO : Documentation.
             */
            inline Color(float r, float g, float b, float a)
                : Vector4(r, g, b, a)
            {
            }

        public:
            /**
             * TODO : Documentation.
             */
            inline float hue() const
            {
                // TODO : http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
                return 0;
            }

            /**
             * TODO : Documentation.
             */
            inline float luminance() const
            {
                // TODO : http://www.niwa.nu/2013/05/math-behind-colorspace-conversions-rgb-hsl/
                return 0;
            }

        public:
            /**
             * Constant Color (1, 0, 0, 1).
             */
            static const Color R;

            /**
             * Constant Color (0, 1, 0, 1).
             */
            static const Color G;

            /**
             * Constant Color (0, 0, 1, 1).
             */
            static const Color B;

            /**
             * Constant Color (1, 1, 1, 1).
             */
            static const Color White;

            /**
             * Constant Color (0, 0, 0, 1).
             */
            static const Color Black;

            /**
             * Constant Color (0, 0, 0, 0).
             */
            static const Color Transparent;

            /**
             * Constant Color (0.941177f, 0.972549f, 1, 1).
             */
            static const Color AliceBlue;

            /**
             * Constant Color (0.980392f, 0.921569f, 0.843137f, 1).
             */
            static const Color AntiqueWhite;

            /**
             * Constant Color (0, 1, 1, 1).
             */
            static const Color Aqua;

            /**
             * Constant Color (0.498039f, 1, 0.831373f, 1).
             */
            static const Color Aquamarine;

            /**
             * Constant Color (0.941177f, 1, 1, 1).
             */
            static const Color Azure;

            /**
             * Constant Color (0.960784f, 0.960784f, 0.862745f, 1).
             */
            static const Color Beige;

            /**
             * Constant Color (1, 0.894118f, 0.768628f, 1).
             */
            static const Color Bisque;

            /**
             * Constant Color (1, 0.921569f, 0.803922f, 1).
             */
            static const Color BlanchedAlmond;

            /**
             * Constant Color (0, 0, 1, 1).
             */
            static const Color Blue;

            /**
             * Constant Color (0.541176f, 0.168627f, 0.886275f, 1).
             */
            static const Color BlueViolet;

            /**
             * Constant Color (0.647059f, 0.164706f, 0.164706f, 1).
             */
            static const Color Brown;

            /**
             * Constant Color (0.870588f, 0.721569f, 0.529412f, 1).
             */
            static const Color BurlyWood;

            /**
             * Constant Color (0.372549f, 0.619608f, 0.627451f, 1).
             */
            static const Color CadetBlue;

            /**
             * Constant Color (0.498039f, 1, 0, 1).
             */
            static const Color Chartreuse;

            /**
             * Constant Color (0.823529f, 0.411765f, 0.117647f, 1).
             */
            static const Color Chocolate;

            /**
             * Constant Color (1, 0.498039f, 0.313726f, 1).
             */
            static const Color Coral;

            /**
             * Constant Color (0.392157f, 0.584314f, 0.929412f, 1).
             */
            static const Color CornflowerBlue;

            /**
             * Constant Color (1, 0.972549f, 0.862745f, 1).
             */
            static const Color Cornsilk;

            /**
             * Constant Color (0.862745f, 0.0784314f, 0.235294f, 1).
             */
            static const Color Crimson;

            /**
             * Constant Color (0, 1, 1, 1).
             */
            static const Color Cyan;

            /**
             * Constant Color (0, 0, 0.545098f, 1).
             */
            static const Color DarkBlue;

            /**
             * Constant Color (0, 0.545098f, 0.545098f, 1).
             */
            static const Color DarkCyan;

            /**
             * Constant Color (0.721569f, 0.52549f, 0.0431373f, 1).
             */
            static const Color DarkGoldenrod;

            /**
             * Constant Color (0.662745f, 0.662745f, 0.662745f, 1).
             */
            static const Color DarkGray;

            /**
             * Constant Color (0, 0.392157f, 0, 1).
             */
            static const Color DarkGreen;

            /**
             * Constant Color (0.741176f, 0.717647f, 0.419608f, 1).
             */
            static const Color DarkKhaki;

            /**
             * Constant Color (0.545098f, 0, 0.545098f, 1).
             */
            static const Color DarkMagenta;

            /**
             * Constant Color (0.333333f, 0.419608f, 0.184314f, 1).
             */
            static const Color DarkOliveGreen;

            /**
             * Constant Color (1, 0.54902f, 0, 1).
             */
            static const Color DarkOrange;

            /**
             * Constant Color (0.6f, 0.196078f, 0.8f, 1).
             */
            static const Color DarkOrchid;

            /**
             * Constant Color (0.545098f, 0, 0, 1).
             */
            static const Color DarkRed;

            /**
             * Constant Color (0.913726f, 0.588235f, 0.478431f, 1).
             */
            static const Color DarkSalmon;

            /**
             * Constant Color (0.560784f, 0.737255f, 0.545098f, 1).
             */
            static const Color DarkSeaGreen;

            /**
             * Constant Color (0.282353f, 0.239216f, 0.545098f, 1).
             */
            static const Color DarkSlateBlue;

            /**
             * Constant Color (0.184314f, 0.309804f, 0.309804f, 1).
             */
            static const Color DarkSlateGray;

            /**
             * Constant Color (0, 0.807843f, 0.819608f, 1).
             */
            static const Color DarkTurquoise;

            /**
             * Constant Color (0.580392f, 0, 0.827451f, 1).
             */
            static const Color DarkViolet;

            /**
             * Constant Color (1, 0.0784314f, 0.576471f, 1).
             */
            static const Color DeepPink;

            /**
             * Constant Color (0, 0.74902f, 1, 1).
             */
            static const Color DeepSkyBlue;

            /**
             * Constant Color (0.411765f, 0.411765f, 0.411765f, 1).
             */
            static const Color DimGray;

            /**
             * Constant Color (0.117647f, 0.564706f, 1, 1).
             */
            static const Color DodgerBlue;

            /**
             * Constant Color (0.698039f, 0.133333f, 0.133333f, 1).
             */
            static const Color Firebrick;

            /**
             * Constant Color (1, 0.980392f, 0.941177f, 1).
             */
            static const Color FloralWhite;

            /**
             * Constant Color (0.133333f, 0.545098f, 0.133333f, 1).
             */
            static const Color ForestGreen;

            /**
             * Constant Color (1, 0, 1, 1).
             */
            static const Color Fuchsia;

            /**
             * Constant Color (0.862745f, 0.862745f, 0.862745f, 1).
             */
            static const Color Gainsboro;

            /**
             * Constant Color (0.972549f, 0.972549f, 1, 1).
             */
            static const Color GhostWhite;

            /**
             * Constant Color (1, 0.843137f, 0, 1).
             */
            static const Color Gold;

            /**
             * Constant Color (0.854902f, 0.647059f, 0.12549f, 1).
             */
            static const Color Goldenrod;

            /**
             * Constant Color (0.501961f, 0.501961f, 0.501961f, 1).
             */
            static const Color Gray;

            /**
             * Constant Color (0, 0.501961f, 0, 1).
             */
            static const Color Green;

            /**
             * Constant Color (0.678431f, 1, 0.184314f, 1).
             */
            static const Color GreenYellow;

            /**
             * Constant Color (0.941177f, 1, 0.941177f, 1).
             */
            static const Color Honeydew;

            /**
             * Constant Color (1, 0.411765f, 0.705882f, 1).
             */
            static const Color HotPink;

            /**
             * Constant Color (0.803922f, 0.360784f, 0.360784f, 1).
             */
            static const Color IndianRed;

            /**
             * Constant Color (0.294118f, 0, 0.509804f, 1).
             */
            static const Color Indigo;

            /**
             * Constant Color (1, 1, 0.941177f, 1).
             */
            static const Color Ivory;

            /**
             * Constant Color (0.941177f, 0.901961f, 0.54902f, 1).
             */
            static const Color Khaki;

            /**
             * Constant Color (0.901961f, 0.901961f, 0.980392f, 1).
             */
            static const Color Lavender;

            /**
             * Constant Color (1, 0.941177f, 0.960784f, 1).
             */
            static const Color LavenderBlush;

            /**
             * Constant Color (0.486275f, 0.988235f, 0, 1).
             */
            static const Color LawnGreen;

            /**
             * Constant Color (1, 0.980392f, 0.803922f, 1).
             */
            static const Color LemonChiffon;

            /**
             * Constant Color (0.678431f, 0.847059f, 0.901961f, 1).
             */
            static const Color LightBlue;

            /**
             * Constant Color (0.941177f, 0.501961f, 0.501961f, 1).
             */
            static const Color LightCoral;

            /**
             * Constant Color (0.878431f, 1, 1, 1).
             */
            static const Color LightCyan;

            /**
             * Constant Color (0.980392f, 0.980392f, 0.823529f, 1).
             */
            static const Color LightGoldenrodYellow;

            /**
             * Constant Color (0.827451f, 0.827451f, 0.827451f, 1).
             */
            static const Color LightGray;

            /**
             * Constant Color (0.564706f, 0.933333f, 0.564706f, 1).
             */
            static const Color LightGreen;

            /**
             * Constant Color (1, 0.713726f, 0.756863f, 1).
             */
            static const Color LightPink;

            /**
             * Constant Color (1, 0.627451f, 0.478431f, 1).
             */
            static const Color LightSalmon;

            /**
             * Constant Color (0.12549f, 0.698039f, 0.666667f, 1).
             */
            static const Color LightSeaGreen;

            /**
             * Constant Color (0.529412f, 0.807843f, 0.980392f, 1).
             */
            static const Color LightSkyBlue;

            /**
             * Constant Color (0.466667f, 0.533333f, 0.6f, 1).
             */
            static const Color LightSlateGray;

            /**
             * Constant Color (0.690196f, 0.768628f, 0.870588f, 1).
             */
            static const Color LightSteelBlue;

            /**
             * Constant Color (1, 1, 0.878431f, 1).
             */
            static const Color LightYellow;

            /**
             * Constant Color (0, 1, 0, 1).
             */
            static const Color Lime;

            /**
             * Constant Color (0.196078f, 0.803922f, 0.196078f, 1).
             */
            static const Color LimeGreen;

            /**
             * Constant Color (0.980392f, 0.941177f, 0.901961f, 1).
             */
            static const Color Linen;

            /**
             * Constant Color (1, 0, 1, 1).
             */
            static const Color Magenta;

            /**
             * Constant Color (0.501961f, 0, 0, 1).
             */
            static const Color Maroon;

            /**
             * Constant Color (0.4f, 0.803922f, 0.666667f, 1).
             */
            static const Color MediumAquamarine;

            /**
             * Constant Color (0, 0, 0.803922f, 1).
             */
            static const Color MediumBlue;

            /**
             * Constant Color (0.729412f, 0.333333f, 0.827451f, 1).
             */
            static const Color MediumOrchid;

            /**
             * Constant Color (0.576471f, 0.439216f, 0.858824f, 1).
             */
            static const Color MediumPurple;

            /**
             * Constant Color (0.235294f, 0.701961f, 0.443137f, 1).
             */
            static const Color MediumSeaGreen;

            /**
             * Constant Color (0.482353f, 0.407843f, 0.933333f, 1).
             */
            static const Color MediumSlateBlue;

            /**
             * Constant Color (0, 0.980392f, 0.603922f, 1).
             */
            static const Color MediumSpringGreen;

            /**
             * Constant Color (0.282353f, 0.819608f, 0.8f, 1).
             */
            static const Color MediumTurquoise;

            /**
             * Constant Color (0.780392f, 0.0823529f, 0.521569f, 1).
             */
            static const Color MediumVioletRed;

            /**
             * Constant Color (0.0980392f, 0.0980392f, 0.439216f, 1).
             */
            static const Color MidnightBlue;

            /**
             * Constant Color (0.960784f, 1, 0.980392f, 1).
             */
            static const Color MintCream;

            /**
             * Constant Color (1, 0.894118f, 0.882353f, 1).
             */
            static const Color MistyRose;

            /**
             * Constant Color (1, 0.894118f, 0.709804f, 1).
             */
            static const Color Moccasin;

            /**
             * Constant Color (1, 0.870588f, 0.678431f, 1).
             */
            static const Color NavajoWhite;

            /**
             * Constant Color (0, 0, 0.501961f, 1).
             */
            static const Color Navy;

            /**
             * Constant Color (0.992157f, 0.960784f, 0.901961f, 1).
             */
            static const Color OldLace;

            /**
             * Constant Color (0.501961f, 0.501961f, 0, 1).
             */
            static const Color Olive;

            /**
             * Constant Color (0.419608f, 0.556863f, 0.137255f, 1).
             */
            static const Color OliveDrab;

            /**
             * Constant Color (1, 0.647059f, 0, 1).
             */
            static const Color Orange;

            /**
             * Constant Color (1, 0.270588f, 0, 1).
             */
            static const Color OrangeRed;

            /**
             * Constant Color (0.854902f, 0.439216f, 0.839216f, 1).
             */
            static const Color Orchid;

            /**
             * Constant Color (0.933333f, 0.909804f, 0.666667f, 1).
             */
            static const Color PaleGoldenrod;

            /**
             * Constant Color (0.596078f, 0.984314f, 0.596078f, 1).
             */
            static const Color PaleGreen;

            /**
             * Constant Color (0.686275f, 0.933333f, 0.933333f, 1).
             */
            static const Color PaleTurquoise;

            /**
             * Constant Color (0.858824f, 0.439216f, 0.576471f, 1).
             */
            static const Color PaleVioletRed;

            /**
             * Constant Color (1, 0.937255f, 0.835294f, 1).
             */
            static const Color PapayaWhip;

            /**
             * Constant Color (1, 0.854902f, 0.72549f, 1).
             */
            static const Color PeachPuff;

            /**
             * Constant Color (0.803922f, 0.521569f, 0.247059f, 1).
             */
            static const Color Peru;

            /**
             * Constant Color (1, 0.752941f, 0.796079f, 1).
             */
            static const Color Pink;

            /**
             * Constant Color (0.866667f, 0.627451f, 0.866667f, 1).
             */
            static const Color Plum;

            /**
             * Constant Color (0.690196f, 0.878431f, 0.901961f, 1).
             */
            static const Color PowderBlue;

            /**
             * Constant Color (0.501961f, 0, 0.501961f, 1).
             */
            static const Color Purple;

            /**
             * Constant Color (1, 0, 0, 1).
             */
            static const Color Red;

            /**
             * Constant Color (0.737255f, 0.560784f, 0.560784f, 1).
             */
            static const Color RosyBrown;

            /**
             * Constant Color (0.254902f, 0.411765f, 0.882353f, 1).
             */
            static const Color RoyalBlue;

            /**
             * Constant Color (0.545098f, 0.270588f, 0.0745098f, 1).
             */
            static const Color SaddleBrown;

            /**
             * Constant Color (0.980392f, 0.501961f, 0.447059f, 1).
             */
            static const Color Salmon;

            /**
             * Constant Color (0.956863f, 0.643137f, 0.376471f, 1).
             */
            static const Color SandyBrown;

            /**
             * Constant Color (0.180392f, 0.545098f, 0.341176f, 1).
             */
            static const Color SeaGreen;

            /**
             * Constant Color (1, 0.960784f, 0.933333f, 1).
             */
            static const Color SeaShell;

            /**
             * Constant Color (0.627451f, 0.321569f, 0.176471f, 1).
             */
            static const Color Sienna;

            /**
             * Constant Color (0.752941f, 0.752941f, 0.752941f, 1).
             */
            static const Color Silver;

            /**
             * Constant Color (0.529412f, 0.807843f, 0.921569f, 1).
             */
            static const Color SkyBlue;

            /**
             * Constant Color (0.415686f, 0.352941f, 0.803922f, 1).
             */
            static const Color SlateBlue;

            /**
             * Constant Color (0.439216f, 0.501961f, 0.564706f, 1).
             */
            static const Color SlateGray;

            /**
             * Constant Color (1, 0.980392f, 0.980392f, 1).
             */
            static const Color Snow;

            /**
             * Constant Color (0, 1, 0.498039f, 1).
             */
            static const Color SpringGreen;

            /**
             * Constant Color (0.27451f, 0.509804f, 0.705882f, 1).
             */
            static const Color SteelBlue;

            /**
             * Constant Color (0.823529f, 0.705882f, 0.54902f, 1).
             */
            static const Color Tan;

            /**
             * Constant Color (0, 0.501961f, 0.501961f, 1).
             */
            static const Color Teal;

            /**
             * Constant Color (0.847059f, 0.74902f, 0.847059f, 1).
             */
            static const Color Thistle;

            /**
             * Constant Color (1, 0.388235f, 0.278431f, 1).
             */
            static const Color Tomato;

            /**
             * Constant Color (0.25098f, 0.878431f, 0.815686f, 1).
             */
            static const Color Turquoise;

            /**
             * Constant Color (0.933333f, 0.509804f, 0.933333f, 1).
             */
            static const Color Violet;

            /**
             * Constant Color (0.960784f, 0.870588f, 0.701961f, 1).
             */
            static const Color Wheat;

            /**
             * Constant Color (0.960784f, 0.960784f, 0.960784f, 1).
             */
            static const Color WhiteSmoke;

            /**
             * Constant Color (1, 1, 0, 1).
             */
            static const Color Yellow;

            /**
             * Constant Color (0.603922f, 0.803922f, 0.196078f, 1).
             */
            static const Color YellowGreen;
        };

        inline Color saturate(const Color& color)
        {
            return Color {
                dst::clamp(color.r, 0.0f, 1.0f),
                dst::clamp(color.g, 0.0f, 1.0f),
                dst::clamp(color.b, 0.0f, 1.0f),
                dst::clamp(color.a, 0.0f, 1.0f)
            };
        }
    } // namespace Math
} // namespace Dynamic_Static
