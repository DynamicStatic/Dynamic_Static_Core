
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

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

#pragma once

#include "Dynamic_Static/Math/Vector2.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"
#include "Dynamic_Static/Math/Vector4.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#define DST_CREATE_VECTORS(SIZE)      \
Vector##SIZE dstVector;               \
glm::vec##SIZE glmVector;             \
random_vectors(dstVector, glmVector);

#define DST_CREATE_VECTOR_PAIRS(SIZE)         \
std::array<Vector##SIZE, SIZE> dstVectors;    \
std::array<glm::vec##SIZE, SIZE> glmVectors;  \
random_vectors(dstVectors[0], glmVectors[0]); \
random_vectors(dstVectors[1], glmVectors[1]);

namespace Dynamic_Static {
    namespace Math {
        namespace Tests {
            static float random_float()
            {
                float value = 64;
                return Random.range<float>(-value, value);
            }

            static Vector2 random_vector2()
            {
                return Vector2(
                    random_float(),
                    random_float()
                );
            }

            static Vector3 random_vector3()
            {
                return Vector3(
                    random_float(),
                    random_float(),
                    random_float()
                );
            }

            static Vector4 random_vector4()
            {
                return Vector4(
                    random_float(),
                    random_float(),
                    random_float(),
                    random_float()
                );
            }

            static void random_vectors(Vector2& dstVector, glm::vec2& glmVector)
            {
                float x = random_float();
                float y = random_float();
                glmVector = { x, y };
                dstVector = { x, y };
            }

            static void random_vectors(Vector3& dstVector, glm::vec3& glmVector)
            {
                float x = random_float();
                float y = random_float();
                float z = random_float();
                glmVector = { x, y, z };
                dstVector = { x, y, z };
            }

            static void random_vectors(Vector4& dstVector, glm::vec4& glmVector)
            {
                float x = random_float();
                float y = random_float();
                float z = random_float();
                float w = random_float();
                glmVector = { x, y, z, w };
                dstVector = { x, y, z, w };
            }

            static bool equal(const Vector2& dstVector, const glm::vec2& glmVec)
            {
                return
                    dstVector.x == glmVec.x &&
                    dstVector.y == glmVec.y &&

                    dstVector.r == glmVec.r &&
                    dstVector.g == glmVec.g &&

                    dstVector[0] == glmVec[0] &&
                    dstVector[1] == glmVec[1];
            }

            static bool equal(const Vector3& dstVector, const glm::vec3& glmVec)
            {
                return
                    dstVector.x == glmVec.x &&
                    dstVector.y == glmVec.y &&
                    dstVector.z == glmVec.z &&

                    dstVector.r == glmVec.r &&
                    dstVector.g == glmVec.g &&
                    dstVector.b == glmVec.b &&

                    dstVector[0] == glmVec[0] &&
                    dstVector[1] == glmVec[1] &&
                    dstVector[2] == glmVec[2];
            }

            static bool equal(const Vector4& dstVector, const glm::vec4& glmVec)
            {
                return
                    dstVector.x == glmVec.x &&
                    dstVector.y == glmVec.y &&
                    dstVector.z == glmVec.z &&
                    dstVector.w == glmVec.w &&

                    dstVector.r == glmVec.r &&
                    dstVector.g == glmVec.g &&
                    dstVector.b == glmVec.b &&
                    dstVector.a == glmVec.a &&

                    dstVector[0] == glmVec[0] &&
                    dstVector[1] == glmVec[1] &&
                    dstVector[2] == glmVec[2] &&
                    dstVector[3] == glmVec[3];
            }
        } // namespace Tests
    } // namespace Math
} // namespace Dynamic_Static
