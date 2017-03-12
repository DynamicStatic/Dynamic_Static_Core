
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

#include "Dynamic_Static/Core/Random.hpp"
#include "Dynamic_Static/Math/Math.hpp"

#include <glm/glm.hpp>

namespace Dynamic_Static {
    namespace Math {
        namespace Tests {
            Vector4 create_randomized_vector4()
            {
                float value = 64;
                return Vector4 {
                    Random.range(-value, value),
                    Random.range(-value, value),
                    Random.range(-value, value),
                    Random.range(-value, value)
                };
            }

            TEST_CASE("Indexed access works correctly", "[Math::Matrix4x4]")
            {
                SECTION("1D access works correctly")
                {
                    glm::mat4 mat4;
                    Matrix4x4 matrix4x4;
                    for (size_t i = 0; i < mat4.length(); ++i) {
                        auto v = create_randomized_vector4();
                        mat4[i] = DST_TO_GLMVEC4_CONST(v);
                        matrix4x4[i] = v;
                    }

                    for (size_t i = 0; i < mat4.length(); ++i) {
                        bool success =
                            mat4[i][0] == matrix4x4[i][0] &&
                            mat4[i][1] == matrix4x4[i][1] &&
                            mat4[i][2] == matrix4x4[i][2] &&
                            mat4[i][3] == matrix4x4[i][3];
                        REQUIRE(success);
                    }
                }

                SECTION("2D access works correctly")
                {

                }
            }
        } // namespace Tests
    } // namespace Math
} // namespace Dynamic_Static
