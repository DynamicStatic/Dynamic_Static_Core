
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

/*

    NOTE : Since Dynamic_Static::Math implements very little mathematical functionality itself,
           the purpose of these tests is to ensure that the results of Dynamic_Static::Math are
           always the same regardless of what math library is used underneath.  To this end, the
           reference library is glm.

*/

#include "catch.hpp"

#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"
#include "Vector.Tests.inl"

#include "glm/glm.hpp"

#include <array>

namespace Dynamic_Static {
    namespace Math {
        namespace Tests {
            TEST_CASE("Vector4 assignment and access", "[Math::Vector4]")
            {
                float x = random_float();
                float y = random_float();
                float z = random_float();
                float w = random_float();

                SECTION("Initializer list")
                {
                    Vector4 dstVector { x, y, z, w };
                    glm::vec4 glmVector { x, y, z, w };
                    REQUIRE(equal(dstVector, glmVector));
                }

                SECTION("Constructor")
                {
                    Vector4 dstVector(x, y, z, w);
                    glm::vec4 glmVector(x, y, z, w);
                    REQUIRE(equal(dstVector, glmVector));
                }

                SECTION("Construct from Vector2")
                {
                    auto randomizedDstVector = random_vector2();
                    Vector4 dstVector = randomizedDstVector;
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1] &&
                        dstVector[2] == 0 &&
                        dstVector[3] == 0;
                    REQUIRE(success);
                }

                SECTION("Construct from Vector2, float, and float")
                {
                    auto randomizedDstVector = random_vector2();
                    Vector4 dstVector(randomizedDstVector, z, w);
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1] &&
                        dstVector[2] == z &&
                        dstVector[3] == w;
                    REQUIRE(success);
                }

                SECTION("Construct from float, Vector2, and float")
                {
                    auto randomizedDstVector = random_vector2();
                    Vector4 dstVector(x, randomizedDstVector, w);
                    bool success =
                        dstVector[0] == x &&
                        dstVector[1] == randomizedDstVector[0] &&
                        dstVector[2] == randomizedDstVector[1] &&
                        dstVector[3] == w;
                    REQUIRE(success);
                }

                SECTION("Construct from float, float, and Vector2")
                {
                    auto randomizedDstVector = random_vector2();
                    Vector4 dstVector(x, y, randomizedDstVector);
                    bool success =
                        dstVector[0] == x &&
                        dstVector[1] == y &&
                        dstVector[2] == randomizedDstVector[0] &&
                        dstVector[3] == randomizedDstVector[1];
                    REQUIRE(success);
                }

                SECTION("Construct from Vector2 and Vector2")
                {
                    auto randomizedDstVector0 = random_vector2();
                    auto randomizedDstVector1 = random_vector2();
                    Vector4 dstVector(randomizedDstVector0, randomizedDstVector1);
                    bool success =
                        dstVector[0] == randomizedDstVector0[0] &&
                        dstVector[1] == randomizedDstVector0[1] &&
                        dstVector[2] == randomizedDstVector1[0] &&
                        dstVector[3] == randomizedDstVector1[1];
                    REQUIRE(success);
                }

                SECTION("Construct from Vector3")
                {
                    auto randomizedDstVector = random_vector3();
                    Vector4 dstVector = randomizedDstVector;
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1] &&
                        dstVector[2] == randomizedDstVector[2] &&
                        dstVector[3] == 0;
                    REQUIRE(success);
                }

                SECTION("Construct from Vector3 and float")
                {
                    auto randomizedDstVector = random_vector3();
                    Vector4 dstVector(randomizedDstVector, w);
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1] &&
                        dstVector[2] == randomizedDstVector[2] &&
                        dstVector[3] == w;
                    REQUIRE(success);
                }

                SECTION("Construct from float and Vector3")
                {
                    auto randomizedDstVector = random_vector3();
                    Vector4 dstVector(x, randomizedDstVector);
                    bool success =
                        dstVector[0] == x &&
                        dstVector[1] == randomizedDstVector[0] &&
                        dstVector[2] == randomizedDstVector[1] &&
                        dstVector[3] == randomizedDstVector[2];
                    REQUIRE(success);
                }
            }

            TEST_CASE("Vector4 addition", "[Math::Vector4]")
            {
                DST_CREATE_VECTOR_PAIRS(4)
                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] + dstVectors[1],
                            glmVectors[0] + glmVectors[1]
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVectors[0] += glmVectors[1];
                    dstVectors[0] += dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }
            }

            TEST_CASE("Vector4 subtraction", "[Math::Vector4]")
            {
                DST_CREATE_VECTOR_PAIRS(4)
                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] - dstVectors[1],
                            glmVectors[0] - glmVectors[1]
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVectors[0] -= glmVectors[1];
                    dstVectors[0] -= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }
            }

            TEST_CASE("Vector4 multiplication", "[Math::Vector4]")
            {
                float scalar = random_float();
                DST_CREATE_VECTOR_PAIRS(4)
                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] * dstVectors[1],
                            glmVectors[0] * glmVectors[1]
                        )
                    );
                }

                SECTION("Non assignment with scalar")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] * scalar,
                            glmVectors[0] * scalar
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVectors[0] *= glmVectors[1];
                    dstVectors[0] *= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }

                SECTION("Assignment with scalar")
                {
                    glmVectors[0] *= scalar;
                    dstVectors[0] *= scalar;
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }
            }

            TEST_CASE("Vector4 division", "[Math::Vector4]")
            {
                float scalar = random_float();
                DST_CREATE_VECTOR_PAIRS(4)
                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] / dstVectors[1],
                            glmVectors[0] / glmVectors[1]
                        )
                    );
                }

                SECTION("Non assignment with scalar")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] / scalar,
                            glmVectors[0] / scalar
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVectors[0] /= glmVectors[1];
                    dstVectors[0] /= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }

                SECTION("Assignment with scalar")
                {
                    glmVectors[0] /= scalar;
                    dstVectors[0] /= scalar;
                    REQUIRE(equal(dstVectors[0], glmVectors[0]));
                }
            }

            TEST_CASE("Vector4 magnitude", "[Math::Vector4]")
            {
                DST_CREATE_VECTORS(4)
                SECTION("Magnitude")
                {
                    REQUIRE(dstVector.magnitude() == glm::length(glmVector));
                }

                SECTION("Magnitude squared")
                {
                    REQUIRE(dstVector.magnitude_squared() == glm::length2(glmVector));
                }
            }

            TEST_CASE("Vector4 normalize", "[Math::Vector4]")
            {
                DST_CREATE_VECTORS(4)
                SECTION("Normalize")
                {
                    dstVector.normalize();
                    glmVector = glm::normalize(glmVector);
                    REQUIRE(equal(dstVector, glmVector));
                }

                SECTION("Normalized")
                {
                    REQUIRE(equal(dstVector.normalized(), glm::normalize(glmVector)));
                }
            }
        } // namespace Tests
    } // namespace Math
} // namespace Dynamic_Static
