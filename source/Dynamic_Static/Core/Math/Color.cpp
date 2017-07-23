
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

#include "Dynamic_Static/Core/Math/Color.hpp"

namespace Dynamic_Static {

    const Color Color::White                { 1.0f,       1.0f,       1.0f,       1.0f };
    const Color Color::Black                { 0.0f,       0.0f,       0.0f,       1.0f };
    const Color Color::Transparent          { 0.0f,       0.0f,       0.0f,       0.0f };
    const Color Color::AliceBlue            { 0.941177f,  0.972549f,  1.0f,       1.0f };
    const Color Color::AntiqueWhite         { 0.980392f,  0.921569f,  0.843137f,  1.0f };
    const Color Color::Aqua                 { 0.0f,       1.0f,       1.0f,       1.0f };
    const Color Color::Aquamarine           { 0.498039f,  1.0f,       0.831373f,  1.0f };
    const Color Color::Azure                { 0.941177f,  1.0f,       1.0f,       1.0f };
    const Color Color::Beige                { 0.960784f,  0.960784f,  0.862745f,  1.0f };
    const Color Color::Bisque               { 1.0f,       0.894118f,  0.768628f,  1.0f };
    const Color Color::BlanchedAlmond       { 1.0f,       0.921569f,  0.803922f,  1.0f };
    const Color Color::Blue                 { 0.0f,       0.0f,       1.0f,       1.0f };
    const Color Color::BlueViolet           { 0.541176f,  0.168627f,  0.886275f,  1.0f };
    const Color Color::Brown                { 0.647059f,  0.164706f,  0.164706f,  1.0f };
    const Color Color::BurlyWood            { 0.870588f,  0.721569f,  0.529412f,  1.0f };
    const Color Color::CadetBlue            { 0.372549f,  0.619608f,  0.627451f,  1.0f };
    const Color Color::Chartreuse           { 0.498039f,  1.0f,       0.0f,       1.0f };
    const Color Color::Chocolate            { 0.823529f,  0.411765f,  0.117647f,  1.0f };
    const Color Color::Coral                { 1.0f,       0.498039f,  0.313726f,  1.0f };
    const Color Color::CornflowerBlue       { 0.392157f,  0.584314f,  0.929412f,  1.0f };
    const Color Color::Cornsilk             { 1.0f,       0.972549f,  0.862745f,  1.0f };
    const Color Color::Crimson              { 0.862745f,  0.0784314f, 0.235294f,  1.0f };
    const Color Color::Cyan                 { 0.0f,       1.0f,       1.0f,       1.0f };
    const Color Color::DarkBlue             { 0.0f,       0.0f,       0.545098f,  1.0f };
    const Color Color::DarkCyan             { 0.0f,       0.545098f,  0.545098f,  1.0f };
    const Color Color::DarkGoldenrod        { 0.721569f,  0.52549f,   0.0431373f, 1.0f };
    const Color Color::DarkGray             { 0.662745f,  0.662745f,  0.662745f,  1.0f };
    const Color Color::DarkGreen            { 0.0f,       0.392157f,  0.0f,       1.0f };
    const Color Color::DarkKhaki            { 0.741176f,  0.717647f,  0.419608f,  1.0f };
    const Color Color::DarkMagenta          { 0.545098f,  0.0f,       0.545098f,  1.0f };
    const Color Color::DarkOliveGreen       { 0.333333f,  0.419608f,  0.184314f,  1.0f };
    const Color Color::DarkOrange           { 1.0f,       0.54902f,   0.0f,       1.0f };
    const Color Color::DarkOrchid           { 0.6f,       0.196078f,  0.8f,       1.0f };
    const Color Color::DarkRed              { 0.545098f,  0.0f,       0.0f,       1.0f };
    const Color Color::DarkSalmon           { 0.913726f,  0.588235f,  0.478431f,  1.0f };
    const Color Color::DarkSeaGreen         { 0.560784f,  0.737255f,  0.545098f,  1.0f };
    const Color Color::DarkSlateBlue        { 0.282353f,  0.239216f,  0.545098f,  1.0f };
    const Color Color::DarkSlateGray        { 0.184314f,  0.309804f,  0.309804f,  1.0f };
    const Color Color::DarkTurquoise        { 0.0f,       0.807843f,  0.819608f,  1.0f };
    const Color Color::DarkViolet           { 0.580392f,  0.0f,       0.827451f,  1.0f };
    const Color Color::DeepPink             { 1.0f,       0.0784314f, 0.576471f,  1.0f };
    const Color Color::DeepSkyBlue          { 0.0f,       0.74902f,   1.0f,       1.0f };
    const Color Color::DimGray              { 0.411765f,  0.411765f,  0.411765f,  1.0f };
    const Color Color::DodgerBlue           { 0.117647f,  0.564706f,  1.0f,       1.0f };
    const Color Color::Firebrick            { 0.698039f,  0.133333f,  0.133333f,  1.0f };
    const Color Color::FloralWhite          { 1.0f,       0.980392f,  0.941177f,  1.0f };
    const Color Color::ForestGreen          { 0.133333f,  0.545098f,  0.133333f,  1.0f };
    const Color Color::Fuchsia              { 1.0f,       0.0f,       1.0f,       1.0f };
    const Color Color::Gainsboro            { 0.862745f,  0.862745f,  0.862745f,  1.0f };
    const Color Color::GhostWhite           { 0.972549f,  0.972549f,  1.0f,       1.0f };
    const Color Color::Gold                 { 1.0f,       0.843137f,  0.0f,       1.0f };
    const Color Color::Goldenrod            { 0.854902f,  0.647059f,  0.12549f,   1.0f };
    const Color Color::Gray                 { 0.501961f,  0.501961f,  0.501961f,  1.0f };
    const Color Color::Green                { 0.0f,       1.0f,       0.0f,       1.0f };
    const Color Color::GreenYellow          { 0.678431f,  1.0f,       0.184314f,  1.0f };
    const Color Color::Honeydew             { 0.941177f,  1.0f,       0.941177f,  1.0f };
    const Color Color::HotPink              { 1.0f,       0.411765f,  0.705882f,  1.0f };
    const Color Color::IndianRed            { 0.803922f,  0.360784f,  0.360784f,  1.0f };
    const Color Color::Indigo               { 0.294118f,  0.0f,       0.509804f,  1.0f };
    const Color Color::Ivory                { 1.0f,       1.0f,       0.941177f,  1.0f };
    const Color Color::Khaki                { 0.941177f,  0.901961f,  0.54902f,   1.0f };
    const Color Color::Lavender             { 0.901961f,  0.901961f,  0.980392f,  1.0f };
    const Color Color::LavenderBlush        { 1.0f,       0.941177f,  0.960784f,  1.0f };
    const Color Color::LawnGreen            { 0.486275f,  0.988235f,  0.0f,       1.0f };
    const Color Color::LemonChiffon         { 1.0f,       0.980392f,  0.803922f,  1.0f };
    const Color Color::LightBlue            { 0.678431f,  0.847059f,  0.901961f,  1.0f };
    const Color Color::LightCoral           { 0.941177f,  0.501961f,  0.501961f,  1.0f };
    const Color Color::LightCyan            { 0.878431f,  1.0f,       1.0f,       1.0f };
    const Color Color::LightGoldenrodYellow { 0.980392f,  0.980392f,  0.823529f,  1.0f };
    const Color Color::LightGray            { 0.827451f,  0.827451f,  0.827451f,  1.0f };
    const Color Color::LightGreen           { 0.564706f,  0.933333f,  0.564706f,  1.0f };
    const Color Color::LightPink            { 1.0f,       0.713726f,  0.756863f,  1.0f };
    const Color Color::LightSalmon          { 1.0f,       0.627451f,  0.478431f,  1.0f };
    const Color Color::LightSeaGreen        { 0.12549f,   0.698039f,  0.666667f,  1.0f };
    const Color Color::LightSkyBlue         { 0.529412f,  0.807843f,  0.980392f,  1.0f };
    const Color Color::LightSlateGray       { 0.466667f,  0.533333f,  0.6f,       1.0f };
    const Color Color::LightSteelBlue       { 0.690196f,  0.768628f,  0.870588f,  1.0f };
    const Color Color::LightYellow          { 1.0f,       1.0f,       0.878431f,  1.0f };
    const Color Color::Lime                 { 0.0f,       1.0f,       0.0f,       1.0f };
    const Color Color::LimeGreen            { 0.196078f,  0.803922f,  0.196078f,  1.0f };
    const Color Color::Linen                { 0.980392f,  0.941177f,  0.901961f,  1.0f };
    const Color Color::Magenta              { 1.0f,       0.0f,       1.0f,       1.0f };
    const Color Color::Maroon               { 0.501961f,  0.0f,       0.0f,       1.0f };
    const Color Color::MediumAquamarine     { 0.4f,       0.803922f,  0.666667f,  1.0f };
    const Color Color::MediumBlue           { 0.0f,       0.0f,       0.803922f,  1.0f };
    const Color Color::MediumOrchid         { 0.729412f,  0.333333f,  0.827451f,  1.0f };
    const Color Color::MediumPurple         { 0.576471f,  0.439216f,  0.858824f,  1.0f };
    const Color Color::MediumSeaGreen       { 0.235294f,  0.701961f,  0.443137f,  1.0f };
    const Color Color::MediumSlateBlue      { 0.482353f,  0.407843f,  0.933333f,  1.0f };
    const Color Color::MediumSpringGreen    { 0.0f,       0.980392f,  0.603922f,  1.0f };
    const Color Color::MediumTurquoise      { 0.282353f,  0.819608f,  0.8f,       1.0f };
    const Color Color::MediumVioletRed      { 0.780392f,  0.0823529f, 0.521569f,  1.0f };
    const Color Color::MidnightBlue         { 0.0980392f, 0.0980392f, 0.439216f,  1.0f };
    const Color Color::MintCream            { 0.960784f,  1.0f,       0.980392f,  1.0f };
    const Color Color::MistyRose            { 1.0f,       0.894118f,  0.882353f,  1.0f };
    const Color Color::Moccasin             { 1.0f,       0.894118f,  0.709804f,  1.0f };
    const Color Color::NavajoWhite          { 1.0f,       0.870588f,  0.678431f,  1.0f };
    const Color Color::Navy                 { 0.0f,       0.0f,       0.501961f,  1.0f };
    const Color Color::OldLace              { 0.992157f,  0.960784f,  0.901961f,  1.0f };
    const Color Color::Olive                { 0.501961f,  0.501961f,  0.0f,       1.0f };
    const Color Color::OliveDrab            { 0.419608f,  0.556863f,  0.137255f,  1.0f };
    const Color Color::Orange               { 1.0f,       0.647059f,  0.0f,       1.0f };
    const Color Color::OrangeRed            { 1.0f,       0.270588f,  0.0f,       1.0f };
    const Color Color::Orchid               { 0.854902f,  0.439216f,  0.839216f,  1.0f };
    const Color Color::PaleGoldenrod        { 0.933333f,  0.909804f,  0.666667f,  1.0f };
    const Color Color::PaleGreen            { 0.596078f,  0.984314f,  0.596078f,  1.0f };
    const Color Color::PaleTurquoise        { 0.686275f,  0.933333f,  0.933333f,  1.0f };
    const Color Color::PaleVioletRed        { 0.858824f,  0.439216f,  0.576471f,  1.0f };
    const Color Color::PapayaWhip           { 1.0f,       0.937255f,  0.835294f,  1.0f };
    const Color Color::PeachPuff            { 1.0f,       0.854902f,  0.72549f,   1.0f };
    const Color Color::Peru                 { 0.803922f,  0.521569f,  0.247059f,  1.0f };
    const Color Color::Pink                 { 1.0f,       0.752941f,  0.796079f,  1.0f };
    const Color Color::Plum                 { 0.866667f,  0.627451f,  0.866667f,  1.0f };
    const Color Color::PowderBlue           { 0.690196f,  0.878431f,  0.901961f,  1.0f };
    const Color Color::Purple               { 0.501961f,  0.0f,       0.501961f,  1.0f };
    const Color Color::Red                  { 1.0f,       0.0f,       0.0f,       1.0f };
    const Color Color::RosyBrown            { 0.737255f,  0.560784f,  0.560784f,  1.0f };
    const Color Color::RoyalBlue            { 0.254902f,  0.411765f,  0.882353f,  1.0f };
    const Color Color::SaddleBrown          { 0.545098f,  0.270588f,  0.0745098f, 1.0f };
    const Color Color::Salmon               { 0.980392f,  0.501961f,  0.447059f,  1.0f };
    const Color Color::SandyBrown           { 0.956863f,  0.643137f,  0.376471f,  1.0f };
    const Color Color::SeaGreen             { 0.180392f,  0.545098f,  0.341176f,  1.0f };
    const Color Color::SeaShell             { 1.0f,       0.960784f,  0.933333f,  1.0f };
    const Color Color::Sienna               { 0.627451f,  0.321569f,  0.176471f,  1.0f };
    const Color Color::Silver               { 0.752941f,  0.752941f,  0.752941f,  1.0f };
    const Color Color::SkyBlue              { 0.529412f,  0.807843f,  0.921569f,  1.0f };
    const Color Color::SlateBlue            { 0.415686f,  0.352941f,  0.803922f,  1.0f };
    const Color Color::SlateGray            { 0.439216f,  0.501961f,  0.564706f,  1.0f };
    const Color Color::Snow                 { 1.0f,       0.980392f,  0.980392f,  1.0f };
    const Color Color::SpringGreen          { 0.0f,       1.0f,       0.498039f,  1.0f };
    const Color Color::SteelBlue            { 0.27451f,   0.509804f,  0.705882f,  1.0f };
    const Color Color::Tan                  { 0.823529f,  0.705882f,  0.54902f,   1.0f };
    const Color Color::Teal                 { 0.0f,       0.501961f,  0.501961f,  1.0f };
    const Color Color::Thistle              { 0.847059f,  0.74902f,   0.847059f,  1.0f };
    const Color Color::Tomato               { 1.0f,       0.388235f,  0.278431f,  1.0f };
    const Color Color::Turquoise            { 0.25098f,   0.878431f,  0.815686f,  1.0f };
    const Color Color::Violet               { 0.933333f,  0.509804f,  0.933333f,  1.0f };
    const Color Color::Wheat                { 0.960784f,  0.870588f,  0.701961f,  1.0f };
    const Color Color::WhiteSmoke           { 0.960784f,  0.960784f,  0.960784f,  1.0f };
    const Color Color::Yellow               { 1.0f,       1.0f,       0.0f,       1.0f };
    const Color Color::YellowGreen          { 0.603922f,  0.803922f,  0.196078f,  1.0f };

} // namespace Dynamic_Static
