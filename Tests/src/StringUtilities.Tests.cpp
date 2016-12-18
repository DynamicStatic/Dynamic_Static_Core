
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
        static const std::string TestString = "The quick brown fox jumps over the lazy dog.";

        TEST_CASE("remove() works correctly", "[StringUtilities]")
        {
            std::string str = TestString;
            str = remove(str, " brow");
            str = remove(str, 'n');
            str = remove(str, " lazy");
            str = remove(str, "-dog-");
            REQUIRE(str == "The quick fox jumps over the dog.");
        }

        TEST_CASE("replace() works correctly", "[StringUtilities]")
        {
            std::string str = TestString;
            str = replace(str, "quick", "slow");
            str = replace(str, "jumps", "trips");
            str = replace(str, "lazy", "sleeping");
            REQUIRE(str == "The slow brown fox trips over the sleeping dog.");
        }

        TEST_CASE("replace() ignores empty arguments for find", "[StringUtilities]")
        {
            std::string str = TestString;
            str = replace(str, std::string(), "hello");
            REQUIRE(str == TestString);
        }

        TEST_CASE("reduce_sequence() works correctly", "[StringUtilities]")
        {
            std::string str = "Some\\Windows\\/\\//\\Path\\With\\A/////Broken\\\\Extension.....ext";
            str = replace(str, '\\', '/');
            str = reduce_sequence(str, '/');
            str = reduce_sequence(str, '.');
            str = replace(str, "Broken", "Good");
            REQUIRE(str == "Some/Windows/Path/With/A/Good/Extension.ext");
        }
    }
}
