
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

#include "Dynamic_Static/Core/Collection.hpp"

namespace Dynamic_Static {
    namespace Tests {
        static const size_t g_test_count { 64 };

        TEST_CASE("Collection can wrap a raw array", "[Collection]")
        {
            int* integer_array = new int[g_test_count];
            auto integer_collection = Collection<int>(integer_array, g_test_count);
            REQUIRE(integer_collection.data() == integer_array);
            REQUIRE(integer_collection.count() == g_test_count);
            delete [] integer_array;
        }

        TEST_CASE("Collection can wrap an std::array<T>", "[Collection]")
        {
            std::array<int, g_test_count> integer_array;
            auto integer_collection = Collection<int>(integer_array);
            REQUIRE(integer_collection.data() == integer_array.data());
            REQUIRE(integer_collection.count() == integer_array.size());
        }

        TEST_CASE("Collection can wrap an std::vector<T>", "[Collection]")
        {
            std::vector<int> integer_vector(g_test_count);
            auto integer_collection = Collection<int>(integer_vector);
            REQUIRE(integer_collection.data() == integer_vector.data());
            REQUIRE(integer_collection.count() == integer_vector.size());
        }
    }
}
