
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

    TEST_CASE("Vector2 addition", "[Vector2]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector2, +);
    }

    TEST_CASE("Vector2 subtraction", "[Vector2]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector2, -);
    }

    TEST_CASE("Vector2 multiplication", "[Vector2]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector2, *);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector2, *);
    }

    TEST_CASE("Vector2 division", "[Vector2]")
    {
        DST_VECTOR_VECTOR_OPERATOR_TEST(Vector2, /);
        DST_VECTOR_SCALAR_OPERATOR_TEST(Vector2, /);
    }

    TEST_CASE("Vector2 construction", "[Vector2]")
    {
        DST_VECTOR_CONSTRUCTION_TEST(Vector2, Vector2);
        DST_VECTOR_CONSTRUCTION_TEST(Vector2, Vector3);
        DST_VECTOR_CONSTRUCTION_TEST(Vector2, Vector4);
    }

} // namespace Tests
} // namespace Dynamic_Static
