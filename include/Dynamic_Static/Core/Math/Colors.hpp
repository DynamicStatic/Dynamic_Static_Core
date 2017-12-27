
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/Math/Defines.hpp"

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    struct Color final
    {
        Color() = delete;
        static const glm::vec4 White;                /*!< Constant color { 1.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Black;                /*!< Constant color { 0.0f,       0.0f,       0.0f,       1.0f } */
        static const glm::vec4 Transparent;          /*!< Constant color { 0.0f,       0.0f,       0.0f,       0.0f } */
        static const glm::vec4 AliceBlue;            /*!< Constant color { 0.941177f,  0.972549f,  1.0f,       1.0f } */
        static const glm::vec4 AntiqueWhite;         /*!< Constant color { 0.980392f,  0.921569f,  0.843137f,  1.0f } */
        static const glm::vec4 Aqua;                 /*!< Constant color { 0.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Aquamarine;           /*!< Constant color { 0.498039f,  1.0f,       0.831373f,  1.0f } */
        static const glm::vec4 Azure;                /*!< Constant color { 0.941177f,  1.0f,       1.0f,       1.0f } */
        static const glm::vec4 Beige;                /*!< Constant color { 0.960784f,  0.960784f,  0.862745f,  1.0f } */
        static const glm::vec4 Bisque;               /*!< Constant color { 1.0f,       0.894118f,  0.768628f,  1.0f } */
        static const glm::vec4 BlanchedAlmond;       /*!< Constant color { 1.0f,       0.921569f,  0.803922f,  1.0f } */
        static const glm::vec4 Blue;                 /*!< Constant color { 0.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 BlueViolet;           /*!< Constant color { 0.541176f,  0.168627f,  0.886275f,  1.0f } */
        static const glm::vec4 Brown;                /*!< Constant color { 0.647059f,  0.164706f,  0.164706f,  1.0f } */
        static const glm::vec4 BurlyWood;            /*!< Constant color { 0.870588f,  0.721569f,  0.529412f,  1.0f } */
        static const glm::vec4 CadetBlue;            /*!< Constant color { 0.372549f,  0.619608f,  0.627451f,  1.0f } */
        static const glm::vec4 Chartreuse;           /*!< Constant color { 0.498039f,  1.0f,       0.0f,       1.0f } */
        static const glm::vec4 Chocolate;            /*!< Constant color { 0.823529f,  0.411765f,  0.117647f,  1.0f } */
        static const glm::vec4 Coral;                /*!< Constant color { 1.0f,       0.498039f,  0.313726f,  1.0f } */
        static const glm::vec4 CornflowerBlue;       /*!< Constant color { 0.392157f,  0.584314f,  0.929412f,  1.0f } */
        static const glm::vec4 Cornsilk;             /*!< Constant color { 1.0f,       0.972549f,  0.862745f,  1.0f } */
        static const glm::vec4 Crimson;              /*!< Constant color { 0.862745f,  0.0784314f, 0.235294f,  1.0f } */
        static const glm::vec4 Cyan;                 /*!< Constant color { 0.0f,       1.0f,       1.0f,       1.0f } */
        static const glm::vec4 DarkBlue;             /*!< Constant color { 0.0f,       0.0f,       0.545098f,  1.0f } */
        static const glm::vec4 DarkCyan;             /*!< Constant color { 0.0f,       0.545098f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkGoldenrod;        /*!< Constant color { 0.721569f,  0.52549f,   0.0431373f, 1.0f } */
        static const glm::vec4 DarkGray;             /*!< Constant color { 0.662745f,  0.662745f,  0.662745f,  1.0f } */
        static const glm::vec4 DarkGreen;            /*!< Constant color { 0.0f,       0.392157f,  0.0f,       1.0f } */
        static const glm::vec4 DarkKhaki;            /*!< Constant color { 0.741176f,  0.717647f,  0.419608f,  1.0f } */
        static const glm::vec4 DarkMagenta;          /*!< Constant color { 0.545098f,  0.0f,       0.545098f,  1.0f } */
        static const glm::vec4 DarkOliveGreen;       /*!< Constant color { 0.333333f,  0.419608f,  0.184314f,  1.0f } */
        static const glm::vec4 DarkOrange;           /*!< Constant color { 1.0f,       0.54902f,   0.0f,       1.0f } */
        static const glm::vec4 DarkOrchid;           /*!< Constant color { 0.6f,       0.196078f,  0.8f,       1.0f } */
        static const glm::vec4 DarkRed;              /*!< Constant color { 0.545098f,  0.0f,       0.0f,       1.0f } */
        static const glm::vec4 DarkSalmon;           /*!< Constant color { 0.913726f,  0.588235f,  0.478431f,  1.0f } */
        static const glm::vec4 DarkSeaGreen;         /*!< Constant color { 0.560784f,  0.737255f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkSlateBlue;        /*!< Constant color { 0.282353f,  0.239216f,  0.545098f,  1.0f } */
        static const glm::vec4 DarkSlateGray;        /*!< Constant color { 0.184314f,  0.309804f,  0.309804f,  1.0f } */
        static const glm::vec4 DarkTurquoise;        /*!< Constant color { 0.0f,       0.807843f,  0.819608f,  1.0f } */
        static const glm::vec4 DarkViolet;           /*!< Constant color { 0.580392f,  0.0f,       0.827451f,  1.0f } */
        static const glm::vec4 DeepPink;             /*!< Constant color { 1.0f,       0.0784314f, 0.576471f,  1.0f } */
        static const glm::vec4 DeepSkyBlue;          /*!< Constant color { 0.0f,       0.74902f,   1.0f,       1.0f } */
        static const glm::vec4 DimGray;              /*!< Constant color { 0.411765f,  0.411765f,  0.411765f,  1.0f } */
        static const glm::vec4 DodgerBlue;           /*!< Constant color { 0.117647f,  0.564706f,  1.0f,       1.0f } */
        static const glm::vec4 Firebrick;            /*!< Constant color { 0.698039f,  0.133333f,  0.133333f,  1.0f } */
        static const glm::vec4 FloralWhite;          /*!< Constant color { 1.0f,       0.980392f,  0.941177f,  1.0f } */
        static const glm::vec4 ForestGreen;          /*!< Constant color { 0.133333f,  0.545098f,  0.133333f,  1.0f } */
        static const glm::vec4 Fuchsia;              /*!< Constant color { 1.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 Gainsboro;            /*!< Constant color { 0.862745f,  0.862745f,  0.862745f,  1.0f } */
        static const glm::vec4 GhostWhite;           /*!< Constant color { 0.972549f,  0.972549f,  1.0f,       1.0f } */
        static const glm::vec4 GearsBlue;            /*!< Constant color { 0.2f,       0.2f,       1.0f,       1.0f } */
        static const glm::vec4 GearsGreen;           /*!< Constant color { 0.0f,       0.8f,       0.2f,       1.0f } */
        static const glm::vec4 GearsRed;             /*!< Constant color { 0.8f,       0.1f,       0.0f,       1.0f } */
        static const glm::vec4 Gold;                 /*!< Constant color { 1.0f,       0.843137f,  0.0f,       1.0f } */
        static const glm::vec4 Goldenrod;            /*!< Constant color { 0.854902f,  0.647059f,  0.12549f,   1.0f } */
        static const glm::vec4 Gray;                 /*!< Constant color { 0.501961f,  0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 Green;                /*!< Constant color { 0.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 GreenYellow;          /*!< Constant color { 0.678431f,  1.0f,       0.184314f,  1.0f } */
        static const glm::vec4 HalfGray;             /*!< Constant color { 0.5f,       0.5f,       0.5f,       1.0f } */
        static const glm::vec4 Honeydew;             /*!< Constant color { 0.941177f,  1.0f,       0.941177f,  1.0f } */
        static const glm::vec4 HotPink;              /*!< Constant color { 1.0f,       0.411765f,  0.705882f,  1.0f } */
        static const glm::vec4 IndianRed;            /*!< Constant color { 0.803922f,  0.360784f,  0.360784f,  1.0f } */
        static const glm::vec4 Indigo;               /*!< Constant color { 0.294118f,  0.0f,       0.509804f,  1.0f } */
        static const glm::vec4 Ivory;                /*!< Constant color { 1.0f,       1.0f,       0.941177f,  1.0f } */
        static const glm::vec4 Khaki;                /*!< Constant color { 0.941177f,  0.901961f,  0.54902f,   1.0f } */
        static const glm::vec4 Lavender;             /*!< Constant color { 0.901961f,  0.901961f,  0.980392f,  1.0f } */
        static const glm::vec4 LavenderBlush;        /*!< Constant color { 1.0f,       0.941177f,  0.960784f,  1.0f } */
        static const glm::vec4 LawnGreen;            /*!< Constant color { 0.486275f,  0.988235f,  0.0f,       1.0f } */
        static const glm::vec4 LemonChiffon;         /*!< Constant color { 1.0f,       0.980392f,  0.803922f,  1.0f } */
        static const glm::vec4 LightBlue;            /*!< Constant color { 0.678431f,  0.847059f,  0.901961f,  1.0f } */
        static const glm::vec4 LightCoral;           /*!< Constant color { 0.941177f,  0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 LightCyan;            /*!< Constant color { 0.878431f,  1.0f,       1.0f,       1.0f } */
        static const glm::vec4 LightGoldenrodYellow; /*!< Constant color { 0.980392f,  0.980392f,  0.823529f,  1.0f } */
        static const glm::vec4 LightGray;            /*!< Constant color { 0.827451f,  0.827451f,  0.827451f,  1.0f } */
        static const glm::vec4 LightGreen;           /*!< Constant color { 0.564706f,  0.933333f,  0.564706f,  1.0f } */
        static const glm::vec4 LightPink;            /*!< Constant color { 1.0f,       0.713726f,  0.756863f,  1.0f } */
        static const glm::vec4 LightSalmon;          /*!< Constant color { 1.0f,       0.627451f,  0.478431f,  1.0f } */
        static const glm::vec4 LightSeaGreen;        /*!< Constant color { 0.12549f,   0.698039f,  0.666667f,  1.0f } */
        static const glm::vec4 LightSkyBlue;         /*!< Constant color { 0.529412f,  0.807843f,  0.980392f,  1.0f } */
        static const glm::vec4 LightSlateGray;       /*!< Constant color { 0.466667f,  0.533333f,  0.6f,       1.0f } */
        static const glm::vec4 LightSteelBlue;       /*!< Constant color { 0.690196f,  0.768628f,  0.870588f,  1.0f } */
        static const glm::vec4 LightYellow;          /*!< Constant color { 1.0f,       1.0f,       0.878431f,  1.0f } */
        static const glm::vec4 Lime;                 /*!< Constant color { 0.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 LimeGreen;            /*!< Constant color { 0.196078f,  0.803922f,  0.196078f,  1.0f } */
        static const glm::vec4 Linen;                /*!< Constant color { 0.980392f,  0.941177f,  0.901961f,  1.0f } */
        static const glm::vec4 Magenta;              /*!< Constant color { 1.0f,       0.0f,       1.0f,       1.0f } */
        static const glm::vec4 Maroon;               /*!< Constant color { 0.501961f,  0.0f,       0.0f,       1.0f } */
        static const glm::vec4 MediumAquamarine;     /*!< Constant color { 0.4f,       0.803922f,  0.666667f,  1.0f } */
        static const glm::vec4 MediumBlue;           /*!< Constant color { 0.0f,       0.0f,       0.803922f,  1.0f } */
        static const glm::vec4 MediumOrchid;         /*!< Constant color { 0.729412f,  0.333333f,  0.827451f,  1.0f } */
        static const glm::vec4 MediumPurple;         /*!< Constant color { 0.576471f,  0.439216f,  0.858824f,  1.0f } */
        static const glm::vec4 MediumSeaGreen;       /*!< Constant color { 0.235294f,  0.701961f,  0.443137f,  1.0f } */
        static const glm::vec4 MediumSlateBlue;      /*!< Constant color { 0.482353f,  0.407843f,  0.933333f,  1.0f } */
        static const glm::vec4 MediumSpringGreen;    /*!< Constant color { 0.0f,       0.980392f,  0.603922f,  1.0f } */
        static const glm::vec4 MediumTurquoise;      /*!< Constant color { 0.282353f,  0.819608f,  0.8f,       1.0f } */
        static const glm::vec4 MediumVioletRed;      /*!< Constant color { 0.780392f,  0.0823529f, 0.521569f,  1.0f } */
        static const glm::vec4 MidnightBlue;         /*!< Constant color { 0.0980392f, 0.0980392f, 0.439216f,  1.0f } */
        static const glm::vec4 MintCream;            /*!< Constant color { 0.960784f,  1.0f,       0.980392f,  1.0f } */
        static const glm::vec4 MistyRose;            /*!< Constant color { 1.0f,       0.894118f,  0.882353f,  1.0f } */
        static const glm::vec4 Moccasin;             /*!< Constant color { 1.0f,       0.894118f,  0.709804f,  1.0f } */
        static const glm::vec4 NavajoWhite;          /*!< Constant color { 1.0f,       0.870588f,  0.678431f,  1.0f } */
        static const glm::vec4 Navy;                 /*!< Constant color { 0.0f,       0.0f,       0.501961f,  1.0f } */
        static const glm::vec4 OldLace;              /*!< Constant color { 0.992157f,  0.960784f,  0.901961f,  1.0f } */
        static const glm::vec4 Olive;                /*!< Constant color { 0.501961f,  0.501961f,  0.0f,       1.0f } */
        static const glm::vec4 OliveDrab;            /*!< Constant color { 0.419608f,  0.556863f,  0.137255f,  1.0f } */
        static const glm::vec4 Orange;               /*!< Constant color { 1.0f,       0.647059f,  0.0f,       1.0f } */
        static const glm::vec4 OrangeRed;            /*!< Constant color { 1.0f,       0.270588f,  0.0f,       1.0f } */
        static const glm::vec4 Orchid;               /*!< Constant color { 0.854902f,  0.439216f,  0.839216f,  1.0f } */
        static const glm::vec4 PaleGoldenrod;        /*!< Constant color { 0.933333f,  0.909804f,  0.666667f,  1.0f } */
        static const glm::vec4 PaleGreen;            /*!< Constant color { 0.596078f,  0.984314f,  0.596078f,  1.0f } */
        static const glm::vec4 PaleTurquoise;        /*!< Constant color { 0.686275f,  0.933333f,  0.933333f,  1.0f } */
        static const glm::vec4 PaleVioletRed;        /*!< Constant color { 0.858824f,  0.439216f,  0.576471f,  1.0f } */
        static const glm::vec4 PapayaWhip;           /*!< Constant color { 1.0f,       0.937255f,  0.835294f,  1.0f } */
        static const glm::vec4 PeachPuff;            /*!< Constant color { 1.0f,       0.854902f,  0.72549f,   1.0f } */
        static const glm::vec4 Peru;                 /*!< Constant color { 0.803922f,  0.521569f,  0.247059f,  1.0f } */
        static const glm::vec4 Pink;                 /*!< Constant color { 1.0f,       0.752941f,  0.796079f,  1.0f } */
        static const glm::vec4 Plum;                 /*!< Constant color { 0.866667f,  0.627451f,  0.866667f,  1.0f } */
        static const glm::vec4 PowderBlue;           /*!< Constant color { 0.690196f,  0.878431f,  0.901961f,  1.0f } */
        static const glm::vec4 Purple;               /*!< Constant color { 0.501961f,  0.0f,       0.501961f,  1.0f } */
        static const glm::vec4 QuarterGray;          /*!< Constant color { 0.25f,      0.25f,      0.25f,      1.0f } */
        static const glm::vec4 Red;                  /*!< Constant color { 1.0f,       0.0f,       0.0f,       1.0f } */
        static const glm::vec4 RosyBrown;            /*!< Constant color { 0.737255f,  0.560784f,  0.560784f,  1.0f } */
        static const glm::vec4 RoyalBlue;            /*!< Constant color { 0.254902f,  0.411765f,  0.882353f,  1.0f } */
        static const glm::vec4 SaddleBrown;          /*!< Constant color { 0.545098f,  0.270588f,  0.0745098f, 1.0f } */
        static const glm::vec4 Salmon;               /*!< Constant color { 0.980392f,  0.501961f,  0.447059f,  1.0f } */
        static const glm::vec4 SandyBrown;           /*!< Constant color { 0.956863f,  0.643137f,  0.376471f,  1.0f } */
        static const glm::vec4 SeaGreen;             /*!< Constant color { 0.180392f,  0.545098f,  0.341176f,  1.0f } */
        static const glm::vec4 SeaShell;             /*!< Constant color { 1.0f,       0.960784f,  0.933333f,  1.0f } */
        static const glm::vec4 Sienna;               /*!< Constant color { 0.627451f,  0.321569f,  0.176471f,  1.0f } */
        static const glm::vec4 Silver;               /*!< Constant color { 0.752941f,  0.752941f,  0.752941f,  1.0f } */
        static const glm::vec4 SkyBlue;              /*!< Constant color { 0.529412f,  0.807843f,  0.921569f,  1.0f } */
        static const glm::vec4 SlateBlue;            /*!< Constant color { 0.415686f,  0.352941f,  0.803922f,  1.0f } */
        static const glm::vec4 SlateGray;            /*!< Constant color { 0.439216f,  0.501961f,  0.564706f,  1.0f } */
        static const glm::vec4 Snow;                 /*!< Constant color { 1.0f,       0.980392f,  0.980392f,  1.0f } */
        static const glm::vec4 SpringGreen;          /*!< Constant color { 0.0f,       1.0f,       0.498039f,  1.0f } */
        static const glm::vec4 SteelBlue;            /*!< Constant color { 0.27451f,   0.509804f,  0.705882f,  1.0f } */
        static const glm::vec4 Tan;                  /*!< Constant color { 0.823529f,  0.705882f,  0.54902f,   1.0f } */
        static const glm::vec4 Teal;                 /*!< Constant color { 0.0f,       0.501961f,  0.501961f,  1.0f } */
        static const glm::vec4 ThirdGray;            /*!< Constant color { 0.3f,       0.3f,       0.3f,       1.0f } */
        static const glm::vec4 Thistle;              /*!< Constant color { 0.847059f,  0.74902f,   0.847059f,  1.0f } */
        static const glm::vec4 Tomato;               /*!< Constant color { 1.0f,       0.388235f,  0.278431f,  1.0f } */
        static const glm::vec4 Turquoise;            /*!< Constant color { 0.25098f,   0.878431f,  0.815686f,  1.0f } */
        static const glm::vec4 Violet;               /*!< Constant color { 0.933333f,  0.509804f,  0.933333f,  1.0f } */
        static const glm::vec4 Wheat;                /*!< Constant color { 0.960784f,  0.870588f,  0.701961f,  1.0f } */
        static const glm::vec4 WhiteSmoke;           /*!< Constant color { 0.960784f,  0.960784f,  0.960784f,  1.0f } */
        static const glm::vec4 Yellow;               /*!< Constant color { 1.0f,       1.0f,       0.0f,       1.0f } */
        static const glm::vec4 YellowGreen;          /*!< Constant color { 0.603922f,  0.803922f,  0.196078f,  1.0f } */
    };

} // namespace Dynamic_Static