
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

#include "Dynamic_Static/Core/Math.hpp"

#include "Vector.Tests.inl"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {

    // TEST_CASE("Vector4 addition", "[Vector4]")
    // {
    //     DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, +);
    // }
    // 
    // TEST_CASE("Vector4 subtraction", "[Vector4]")
    // {
    //     DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, -);
    // }
    // 
    // TEST_CASE("Vector4 multiplication", "[Vector4]")
    // {
    //     DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, *);
    //     DST_VECTOR_SCALAR_OPERATOR_TEST(Vector4, *);
    // }
    // 
    // TEST_CASE("Vector4 division", "[Vector4]")
    // {
    //     DST_VECTOR_VECTOR_OPERATOR_TEST(Vector4, /);
    //     DST_VECTOR_SCALAR_OPERATOR_TEST(Vector4, /);
    // }
    // 
    // TEST_CASE("Vector4 length", "[Vector4]")
    // {
    //     DST_VECTOR_LENGTH_TEST(Vector4);
    // }
    // 
    // TEST_CASE("Vector4 construction", "[Vector4]")
    // {
    //     DST_VECTOR_CONSTRUCTION_TEST(Vector4, Vector2);
    //     DST_VECTOR_CONSTRUCTION_TEST(Vector4, Vector3);
    //     DST_VECTOR_CONSTRUCTION_TEST(Vector4, Vector4);
    // }

} // namespace Tests
} // namespace Dynamic_Static
