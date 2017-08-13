
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

#include "Vector.Tests.inl"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Vector3 addition", "[Vector3]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector3, +);
    }

    TEST_CASE("Vector3 subtraction", "[Vector3]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector3, -);
    }

    TEST_CASE("Vector3 multiplication", "[Vector3]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector3, *);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector3, *);
    }

    TEST_CASE("Vector3 division", "[Vector3]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector3, /);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector3, /);
    }

    TEST_CASE("Vector3 normalize", "[Vector3]")
    {
        DST_VECTOR_NORMALIZE_TEST(Vector3);
    }

    TEST_CASE("Vector3 construction", "[Vector3]")
    {
        DST_VECTOR_CONSTRUCTION_TEST(Vector3, Vector2);
        DST_VECTOR_CONSTRUCTION_TEST(Vector3, Vector3);
        DST_VECTOR_CONSTRUCTION_TEST(Vector3, Vector4);
    }

} // namespace Tests
} // namespace Dynamic_Static
