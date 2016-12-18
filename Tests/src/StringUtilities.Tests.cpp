
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

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

#include "catch.hpp"

#include "Dynamic_Static/Core/StringUtilities.hpp"

#include <string>

namespace Dynamic_Static {
    namespace Tests {
        TEST_CASE("Replace works correctly", "[StringUtilities]")
        {
            std::string str = "Some\\Windows\\\\Path\\With\\A/Shitty\\\\Extension.....ext";
            str = replace(str, "\\", '/');
            str = replace(str, "//", '/');
            str = replace(str, "..", '.');
            str = replace(str, "Shitty", "Good");
            REQUIRE(str == "Some/Windows/Path/With/A/Good/Extension.ext");
        }

        TEST_CASE("Remove works correctly", "[StringUtilities]")
        {
            std::string str = "The quick brown fox jumps over the lazy dog";
            str = remove(str, "brow");
            str = remove(str, 'n');
            str = remove(str, "lazy");
            str = remove(str, "-dog-");
            str = replace(str, "  ", ' ');
            REQUIRE(str == "The quick fox jumps over the dog");
        }
    }
}
