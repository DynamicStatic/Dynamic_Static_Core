
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

#pragma once

// #include "Dynamic_Static/Core/Random.hpp"
// #include "Dynamic_Static/Core/Math/Vector2.hpp"
// #include "Dynamic_Static/Core/Math/Vector3.hpp"
// #include "Dynamic_Static/Core/Math/Vector4.hpp"
// 
// #include "catch.hpp"
// 
// #include <utility>
// 
// #define DST_CREATE_VECTOR_PAIR(VECTOR_TYPE)                             \
// auto vectors = random_vector_pair<VECTOR_TYPE, VECTOR_TYPE::GLMBase>(); \
// auto dst0 = std::get<VECTOR_TYPE>(vectors);                             \
// auto glm0 = std::get<VECTOR_TYPE::GLMBase>(vectors);                    \
// 
// #define DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE)                            \
// DST_CREATE_VECTOR_PAIR(VECTOR_TYPE);                                    \
// vectors = random_vector_pair<VECTOR_TYPE, VECTOR_TYPE::GLMBase>();      \
// auto dst1 = std::get<VECTOR_TYPE>(vectors);                             \
// auto glm1 = std::get<VECTOR_TYPE::GLMBase>(vectors);
// 
// #define DST_VECTOR_VECTOR_OPERATOR_TEST(VECTOR_TYPE, OPERATOR)                    \
// {                                                                                 \
//     DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE);                                         \
//     SECTION(#VECTOR_TYPE " operator" #OPERATOR "(" #VECTOR_TYPE ")")              \
//     {                                                                             \
//         auto glmVector = glm0 OPERATOR glm1;                                      \
//         auto dstVector = dst0 OPERATOR dst1;                                      \
//         auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
//         REQUIRE(dstVector == glmVector);                                          \
//         REQUIRE(correctType);                                                     \
//     }                                                                             \
//                                                                                   \
//     SECTION(#VECTOR_TYPE " operator" #OPERATOR "=(" #VECTOR_TYPE ")")             \
//     {                                                                             \
//         glm0 OPERATOR##= glm1;                                                    \
//         dst0 OPERATOR##= dst1;                                                    \
//         REQUIRE(dst0 == glm0);                                                    \
//     }                                                                             \
// }
// 
// #define DST_VECTOR_SCALAR_OPERATOR_TEST(VECTOR_TYPE, OPERATOR)                    \
// {                                                                                 \
//     auto scalar = random_float();                                                 \
//     DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE);                                         \
//     SECTION(#VECTOR_TYPE " operator" #OPERATOR "(scalar)")                        \
//     {                                                                             \
//         auto glmVector = glm0 OPERATOR scalar;                                    \
//         auto dstVector = dst0 OPERATOR scalar;                                    \
//         auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
//         REQUIRE(dstVector == glmVector);                                          \
//         REQUIRE(correctType);                                                     \
//     }                                                                             \
//                                                                                   \
//     SECTION(#VECTOR_TYPE " operator" #OPERATOR "=(scalar)")                       \
//     {                                                                             \
//         glm0 OPERATOR##= scalar;                                                  \
//         dst0 OPERATOR##= scalar;                                                  \
//         REQUIRE(dst0 == glm0);                                                    \
//     }                                                                             \
// }
// 
// #define DST_VECTOR_NORMALIZE_TEST(VECTOR_TYPE)                                    \
// {                                                                                 \
//     DST_CREATE_VECTOR_PAIR(VECTOR_TYPE);                                          \
//     SECTION(#VECTOR_TYPE ".normalize()")                                          \
//     {                                                                             \
//         dst0.normalize();                                                         \
//         REQUIRE(dst0 == glm::normalize(glm0));                                    \
//     }                                                                             \
//                                                                                   \
//     SECTION(#VECTOR_TYPE ".normalized()")                                         \
//     {                                                                             \
//         auto dstVector = dst0.normalized();                                       \
//         auto correctType = std::is_same<decltype(dstVector), VECTOR_TYPE>::value; \
//         REQUIRE(dstVector == glm::normalize(glm0));                               \
//         REQUIRE(correctType);                                                     \
//     }                                                                             \
// }
// 
// #define DST_VECTOR_LENGTH_TEST(VECTOR_TYPE)                   \
// {                                                             \
//     DST_CREATE_VECTOR_PAIR(VECTOR_TYPE);                      \
//     SECTION(#VECTOR_TYPE ".length()")                         \
//     {                                                         \
//         REQUIRE(dst0.length() == glm::length(glm0));          \
//     }                                                         \
//                                                               \
//     SECTION(#VECTOR_TYPE ".length_squared()")                 \
//     {                                                         \
//         REQUIRE(dst0.length_squared() == glm::length2(glm0)); \
//     }                                                         \
// }
// 
// #define DST_VECTOR_DISTANCE_TEST(VECTOR_TYPE)                           \
// {                                                                       \
//     DST_CREATE_VECTOR_PAIRS(VECTOR_TYPE);                               \
//     SECTION(#VECTOR_TYPE "::distance()")                                \
//     {                                                                   \
//         REQUIRE(dst0.distance(dst1) == glm::distance(glm0, glm1));      \
//     }                                                                   \
//                                                                         \
//     SECTION(#VECTOR_TYPE "::distance_squared()")                        \
//     {                                                                   \
//         REQUIRE(dst0.distance_squared() == glm::distance2(glm0, glm1)); \
//     }                                                                   \
// }
// 
// #define DST_VECTOR_CONSTRUCTION_TEST(TO_VECTOR_TYPE, FROM_VECTOR_TYPE) \
// {                                                                      \
//     SECTION(#TO_VECTOR_TYPE " from " #FROM_VECTOR_TYPE)                \
//     {                                                                  \
//         auto sourceVector = random_vector<FROM_VECTOR_TYPE>();         \
//         TO_VECTOR_TYPE targetVector0 = sourceVector;                   \
//         TO_VECTOR_TYPE targetVector1(sourceVector);                    \
//         for (size_t i = 0; i < TO_VECTOR_TYPE::Count; ++i) {           \
//             if (i < FROM_VECTOR_TYPE::Count) {                         \
//                 REQUIRE(targetVector0[i] == sourceVector[i]);          \
//                 REQUIRE(targetVector1[i] == sourceVector[i]);          \
//             } else {                                                   \
//                 REQUIRE(targetVector0[i] == 0);                        \
//                 REQUIRE(targetVector1[i] == 0);                        \
//             }                                                          \
//         }                                                              \
//     }                                                                  \
// }

namespace Dynamic_Static {
namespace Tests {

    // static constexpr size_t TestCount { 64 };
    // 
    // static inline float random_float()
    // {
    //     return dst::Random.range(-1024.0f, 1024.0f);
    // }
    // 
    // template <typename DSTVectorType>
    // static inline DSTVectorType random_vector()
    // {
    //     DSTVectorType dstVector;
    //     for (size_t i = 0; i < DSTVectorType::Count; ++i) {
    //         auto value = random_float();
    //         dstVector[i] = value;
    //     }
    // 
    //     return dstVector;
    // }
    // 
    // template <typename DSTVectorType, typename GLMVectorType>
    // static inline std::pair<DSTVectorType, GLMVectorType> random_vector_pair()
    // {
    //     DSTVectorType dstVector;
    //     GLMVectorType glmVector;
    //     for (size_t i = 0; i < DSTVectorType::Count; ++i) {
    //         auto value = random_float();
    //         dstVector[i] = value;
    //         glmVector[i] = value;
    //     }
    // 
    //     return std::make_pair(dstVector, glmVector);
    // }

} // namespace Tests
} // namespace Dynamic_Static
