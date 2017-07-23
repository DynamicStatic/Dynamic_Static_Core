
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

#pragma once

#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <utility>

#define DST_CREATE_VECTOR_PAIR(VECTOR_TYPE)                             \
auto vectors = random_vector_pair<VECTOR_TYPE, VECTOR_TYPE::GLMBase>(); \
auto dst0 = std::get<VECTOR_TYPE>(vectors);                             \
auto glm0 = std::get<VECTOR_TYPE::GLMBase>(vectors);                    \

#define DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE)                            \
DST_CREATE_VECTOR_PAIR(VECTOR_TYPE);                                    \
vectors = random_vector_pair<VECTOR_TYPE, VECTOR_TYPE::GLMBase>();      \
auto dst1 = std::get<VECTOR_TYPE>(vectors);                             \
auto glm1 = std::get<VECTOR_TYPE::GLMBase>(vectors);

#define DST_VECTOR_VECTOR_OPERATOR_TEST(VECTOR_TYPE, OPERATOR)                    \
{                                                                                 \
    DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE);                                         \
    SECTION(#VECTOR_TYPE " operator" #OPERATOR "(" #VECTOR_TYPE ")")              \
    {                                                                             \
        auto glmVector = glm0 OPERATOR glm1;                                      \
        auto dstVector = dst0 OPERATOR dst1;                                      \
        auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
        REQUIRE(dstVector == glmVector);                                          \
        REQUIRE(correctType);                                                     \
    }                                                                             \
                                                                                  \
    SECTION(#VECTOR_TYPE " operator" #OPERATOR "=(" #VECTOR_TYPE ")")             \
    {                                                                             \
        glm0 OPERATOR##= glm1;                                                    \
        dst0 OPERATOR##= dst1;                                                    \
        REQUIRE(dst0 == glm0);                                                    \
    }                                                                             \
}

#define DST_VECTOR_SCALAR_OPERATOR_TEST(VECTOR_TYPE, OPERATOR)                    \
{                                                                                 \
    auto scalar = random_float();                                                 \
    DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE);                                         \
    SECTION(#VECTOR_TYPE " operator" #OPERATOR "(scalar)")                        \
    {                                                                             \
        auto glmVector = glm0 OPERATOR scalar;                                    \
        auto dstVector = dst0 OPERATOR scalar;                                    \
        auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
        REQUIRE(dstVector == glmVector);                                          \
        REQUIRE(correctType);                                                     \
    }                                                                             \
                                                                                  \
    SECTION(#VECTOR_TYPE " operator" #OPERATOR "=(scalar)")                       \
    {                                                                             \
        glm0 OPERATOR##= scalar;                                                  \
        dst0 OPERATOR##= scalar;                                                  \
        REQUIRE(dst0 == glm0);                                                    \
    }                                                                             \
}

#define DST_VECTOR_NORMALIZE_TEST(VECTOR_TYPE)                                    \
{                                                                                 \
    DST_CREATE_VECTOR_PAIR(VECTOR_TYPE);                                          \
    SECTION(#VECTOR_TYPE ".normalize()")                                          \
    {                                                                             \
        dst0.normalize();                                                         \
        REQUIRE(dst0 == glm::normalize(glm0));                                    \
    }                                                                             \
                                                                                  \
    SECTION(#VECTOR_TYPE ".normalized()")                                         \
    {                                                                             \
        auto dstVector = dst0.normalized();                                       \
        auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
        REQUIRE(dstVector == glm::normalize(glm0));                               \
        REQUIRE(correctType);                                                     \
    }                                                                             \
}

namespace Dynamic_Static {
namespace Tests {

    static constexpr size_t TestCount { 64 };

    static inline float random_float()
    {
        return dst::Random.range(-1024.0f, 1024.0f);
    }

    template <typename DSTVectorType, typename GLMVectorType>
    static inline std::pair<DSTVectorType, GLMVectorType> random_vector_pair()
    {
        DSTVectorType dstVector;
        GLMVectorType glmVector;
        for (size_t i = 0; i < DSTVectorType::Count; ++i) {
            auto value = random_float();
            dstVector[i] = value;
            glmVector[i] = value;
        }

        return std::make_pair(dstVector, glmVector);
    }

} // namespace Tests
} // namespace Dynamic_Static
