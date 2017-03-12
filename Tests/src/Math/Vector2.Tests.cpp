
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
#include "Dynamic_Static/Core/Random.hpp"

#include "glm/glm.hpp"

#include <array>

namespace Dynamic_Static {
    namespace Math {
        namespace Tests {
            static float random_float()
            {
                float value = 64;
                return Random.range<float>(-value, value);
            }

            static void random_vectors(Vector2& dstVector, glm::vec2& glmVec)
            {
                float f0 = random_float();
                float f1 = random_float();
                glmVec    = { f0, f1 };
                dstVector = { f0, f1 };
            }

            static bool equal(const Vector2& dstVector, const glm::vec2& glmVec)
            {
                return
                    dstVector.x == glmVec.x &&
                    dstVector.y == glmVec.y &&

                    dstVector.r == glmVec.r &&
                    dstVector.g == glmVec.g &&

                    dstVector.s == glmVec.s &&
                    dstVector.t == glmVec.t &&

                    dstVector[0] == glmVec[0] &&
                    dstVector[1] == glmVec[1];
            }

            TEST_CASE("Assignment and access", "[Math::Vector2]")
            {
                float f0 = random_float();
                float f1 = random_float();

                SECTION("Initializer list")
                {
                    glm::vec2 vec  { f0, f1 };
                    Vector2 vector { f0, f1 };
                    REQUIRE(equal(vector, vec));
                }

                SECTION("Constructor")
                {
                    glm::vec2 glmVec (f0, f1);
                    Vector2 dstVector(f0, f1);
                    REQUIRE(equal(dstVector, glmVec));
                }
            }

            TEST_CASE("Addition", "[Math::Vector2]")
            {
                std::array<glm::vec2, 2> glmVecs;
                std::array<Vector2,   2> dstVectors;
                random_vectors(dstVectors[0], glmVecs[0]);
                random_vectors(dstVectors[1], glmVecs[1]);

                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] + dstVectors[1],
                            glmVecs   [0] + glmVecs   [1]
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVecs   [0] += glmVecs   [1];
                    dstVectors[0] += dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }
            }

            TEST_CASE("Subtraction", "[Math::Vector2]")
            {
                std::array<glm::vec2, 2> glmVecs;
                std::array<Vector2,   2> dstVectors;
                random_vectors(dstVectors[0], glmVecs[0]);
                random_vectors(dstVectors[1], glmVecs[1]);

                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] - dstVectors[1],
                            glmVecs   [0] - glmVecs   [1]
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVecs   [0] -= glmVecs   [1];
                    dstVectors[0] -= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }
            }

            TEST_CASE("Multiplication", "[Math::Vector2]")
            {
                float scalar = random_float();
                std::array<glm::vec2, 2> glmVecs;
                std::array<Vector2,   2> dstVectors;
                random_vectors(dstVectors[0], glmVecs[0]);
                random_vectors(dstVectors[1], glmVecs[1]);

                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] * dstVectors[1],
                            glmVecs   [0] * glmVecs   [1]
                        )
                    );
                }

                SECTION("Non assignment with scalar")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] * scalar,
                            glmVecs   [0] * scalar
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVecs   [0] *= glmVecs   [1];
                    dstVectors[0] *= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }

                SECTION("Assignment with scalar")
                {
                    glmVecs   [0] *= scalar;
                    dstVectors[0] *= scalar;
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }
            }

            TEST_CASE("Division", "[Math::Vector2]")
            {
                float scalar = random_float();
                std::array<glm::vec2, 2> glmVecs;
                std::array<Vector2,   2> dstVectors;
                random_vectors(dstVectors[0], glmVecs[0]);
                random_vectors(dstVectors[1], glmVecs[1]);

                SECTION("Non assignment")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] / dstVectors[1],
                            glmVecs   [0] / glmVecs   [1]
                        )
                    );
                }

                SECTION("Non assignment with scalar")
                {
                    REQUIRE(
                        equal(
                            dstVectors[0] / scalar,
                            glmVecs   [0] / scalar
                        )
                    );
                }

                SECTION("Assignment")
                {
                    glmVecs   [0] /= glmVecs   [1];
                    dstVectors[0] /= dstVectors[1];
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }

                SECTION("Assignment with scalar")
                {
                    glmVecs   [0] /= scalar;
                    dstVectors[0] /= scalar;
                    REQUIRE(equal(dstVectors[0], glmVecs[0]));
                }
            }

            TEST_CASE("Magnitude", "[Math::Vector2]")
            {
                glm::vec2 glmVec;
                Vector2 dstVector;
                random_vectors(dstVector, glmVec);

                SECTION("Magnitude")
                {
                    REQUIRE(dstVector.magnitude() == glm::length(glmVec));
                }

                SECTION("Magnitude squared")
                {
                    REQUIRE(dstVector.magnitude_squared() == glm::length2(glmVec));
                }
            }

            TEST_CASE("Normalize", "[Math::Vector2]")
            {
                glm::vec2 glmVec;
                Vector2 dstVector;
                random_vectors(dstVector, glmVec);

                SECTION("Normalize")
                {
                    dstVector.normalize();
                    glmVec = glm::normalize(glmVec);
                    REQUIRE(equal(dstVector, glmVec));
                }

                SECTION("Normalized")
                {
                    REQUIRE(equal(dstVector.normalized(), glm::normalize(glmVec)));
                }
            }
        } // namespace Tests
    } // namespace Math
} // namespace Dynamic_Static
