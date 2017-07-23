
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

// NOTE : Since Dynamic_Static implements very little mathematical functionality
//        itself, the purpose of these tests is to ensure that the results given
//        by Dynamic_Static are consistent regardless of the underlying library.
//        To this end, the reference library is glm.

#include "Dynamic_Static/Core/Math/Vector4.hpp"
#include "Vector.Tests.inl"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Vector4 addition", "[Vector4]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, +);
    }

    TEST_CASE("Vector4 subtraction", "[Vector4]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, -);
    }

    TEST_CASE("Vector4 multiplication", "[Vector4]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, *);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector4, *);
    }

    TEST_CASE("Vector4 division", "[Vector4]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, /);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector4, /);
    }

} // namespace Tests
} // namespace Dynamic_Static
