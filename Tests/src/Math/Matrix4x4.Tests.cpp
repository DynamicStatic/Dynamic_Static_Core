
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

#include "Dynamic_Static/Math/Matrix4x4.hpp"
#include "Vector.Tests.inl"

#include "Dynamic_Static/Math/glm/glm.hpp"

namespace Dynamic_Static {
    namespace Math {
        namespace Tests {
            TEST_CASE("Matrix4x4 assignment and access", "[Math::Matrix4x4]")
            {
                glm::mat4 glmMatrix;
                Matrix4x4 dstMatrix;

                SECTION("1D indexed assignment")
                {
                    for (glm::length_t i = 0; i < 4; ++i) {
                        auto v = random_vector4();
                        glmMatrix[i] = DST_TO_GLM_VEC4_CONST(v);
                        dstMatrix[i] = v;
                    }
                }

                SECTION("2D indexed assignment")
                {
                    for (glm::length_t i = 0; i < 4; ++i) {
                        for (glm::length_t j = 0; j < 4; ++j) {
                            float f = random_float();
                            glmMatrix[i][j] = f;
                            dstMatrix[i][j] = f;
                        }
                    }
                }

                for (glm::length_t i = 0; i < 4; ++i) {
                    bool success =
                        dstMatrix[i][0] == glmMatrix[i][0] &&
                        dstMatrix[i][1] == glmMatrix[i][1] &&
                        dstMatrix[i][2] == glmMatrix[i][2] &&
                        dstMatrix[i][3] == glmMatrix[i][3];
                    REQUIRE(success);
                }
            }
        } // namespace Tests
    } // namespace Math
} // namespace Dynamic_Static
