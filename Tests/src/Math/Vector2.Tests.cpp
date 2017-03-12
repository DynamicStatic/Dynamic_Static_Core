
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
            TEST_CASE("Vector2 assignment and access", "[Math::Vector2]")
            {
                float x = random_float();
                float y = random_float();

                SECTION("Initializer list")
                {
                    Vector2 dstVector { x, y };
                    glm::vec2 glmVector { x, y };
                    REQUIRE(equal(dstVector, glmVector));
                }

                SECTION("Constructor")
                {
                    Vector2 dstVector(x, y);
                    glm::vec2 glmVector(x, y);
                    REQUIRE(equal(dstVector, glmVector));
                }

                SECTION("Construct from Vector3")
                {
                    auto randomizedDstVector = random_vector3();
                    Vector2 dstVector = randomizedDstVector;
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1];
                    REQUIRE(success);
                }

                SECTION("Construct from Vector4")
                {
                    auto randomizedDstVector = random_vector4();
                    Vector2 dstVector = randomizedDstVector;
                    bool success =
                        dstVector[0] == randomizedDstVector[0] &&
                        dstVector[1] == randomizedDstVector[1];
                    REQUIRE(success);
                }
            }

            TEST_CASE("Vector2 addition", "[Math::Vector2]")
            {
                DST_CREATE_VECTOR_PAIRS(2)
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

            TEST_CASE("Vector2 subtraction", "[Math::Vector2]")
            {
                DST_CREATE_VECTOR_PAIRS(2)
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

            TEST_CASE("Vector2 multiplication", "[Math::Vector2]")
            {
                float scalar = random_float();
                DST_CREATE_VECTOR_PAIRS(2)
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

            TEST_CASE("Vector2 division", "[Math::Vector2]")
            {
                float scalar = random_float();
                DST_CREATE_VECTOR_PAIRS(2)
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

            TEST_CASE("Vector2 magnitude", "[Math::Vector2]")
            {
                DST_CREATE_VECTORS(2)
                SECTION("Magnitude")
                {
                    REQUIRE(dstVector.magnitude() == glm::length(glmVector));
                }

                SECTION("Magnitude squared")
                {
                    REQUIRE(dstVector.magnitude_squared() == glm::length2(glmVector));
                }
            }

            TEST_CASE("Vector2 normalize", "[Math::Vector2]")
            {
                DST_CREATE_VECTORS(2)
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
