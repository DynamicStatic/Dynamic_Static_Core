
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
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
