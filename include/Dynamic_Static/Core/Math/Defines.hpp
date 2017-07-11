
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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/TypeUtilities.hpp"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ostream>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static
{
    struct Color;
    struct Matrix4x4;
    struct Quaternion;
    struct Rectangle;
    class Transform;
    struct Vector2;
    struct Vector3;
    struct Vector4;
} // namespace Dynamic_Static

namespace Dynamic_Static
{
    namespace detail
    {
        template <typename DSTType, typename GLMType>
        struct VectorBase
            : public GLMType
        {
        public:
            static constexpr size_t Count { sizeof(GLMType) / sizeof(float) };
            using GLMBase = GLMType;

        protected:
            using DSTBase = VectorBase<DSTType, GLMType>;
            using GLMBase::GLMBase;

            /**
             * TODO : Documentation.
             */
            DSTBase& operator+=(const DSTType& rhs)
            {
                *this = static_cast<GLMBase>(*this) + static_cast<GLMBase>(rhs);
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            DSTBase& operator-=(const DSTType& rhs)
            {
                *this = static_cast<GLMBase>(*this) - static_cast<GLMBase>(rhs);
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            template <typename ScalarType>
            DSTBase& operator*=(const ScalarType& rhs)
            {
                *this = static_cast<GLMBase>(*this) * rhs;
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            DSTBase& operator*=(const DSTType& rhs)
            {
                *this = static_cast<GLMBase>(*this) * static_cast<GLMBase>(rhs);
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            template <typename ScalarType>
            DSTBase& operator/=(const ScalarType& rhs)
            {
                *this = static_cast<GLMBase>(*this) / rhs;
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            DSTBase& operator/=(const DSTType& rhs)
            {
                *this = static_cast<GLMBase>(*this) / static_cast<GLMBase>(rhs);
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            operator GLMType&()
            {
                return *this;
            }

            /**
             * TODO : Documentation.
             */
            operator const GLMType&() const
            {
                return *this;
            }

        public:
            /**
             * Gets the std::string representation of this Vector.
             * @return The std::string representation of this Vector
             */
            inline std::string to_string() const
            {
                std::string str = "(";
                for (size_t i = 0; i < Count; ++i) {
                    str += dst::to_string((*this)[i]);
                    if (i < Count - 1) {
                        str += ", ";
                    }
                }

                return str + ")";
            }

            /**
             * TODO : Documentation.
             */
            inline void normalize()
            {
                *this = glm::normalize(*this);
            }

            /**
             * TODO : Documentation.
             */
            inline DSTType normalized() const
            {
                return glm::normalize(*this);
            }
        };
    } // namespace detail
} // namespace Dynamic_Static

namespace Dynamic_Static
{
    namespace detail
    {
        /**
         * TODO : Documentation.
         */
        template <typename VectorType>
        inline VectorType operator+(const VectorType& lhs, const VectorType& rhs)
        {
            return VectorType(
                static_cast<typename VectorType::GLMBase>(lhs) +
                static_cast<typename VectorType::GLMBase>(rhs)
            );
        }

        /**
         * TODO : Documentation.
         */
        template <typename VectorType>
        inline VectorType operator-(const VectorType& lhs, const VectorType& rhs)
        {
            return VectorType(
                static_cast<typename VectorType::GLMBase>(lhs) -
                static_cast<typename VectorType::GLMBase>(rhs)
            );
        }

        /**
         * TODO : Documentation.
         */
        template <typename VectorType, typename ScalarType>
        inline VectorType operator*(const VectorType& lhs, const ScalarType& rhs)
        {
            // NOTE : This cast and construct is lame, but MSVC ADL is having trouble with it otherwise.
            return lhs * VectorType(static_cast<float>(rhs));
        }

        /**
         * TODO : Documentation.
         */
        template <typename VectorType>
        inline VectorType operator*(const VectorType& lhs, const VectorType& rhs)
        {
            return VectorType(
                static_cast<typename VectorType::GLMBase>(lhs) *
                static_cast<typename VectorType::GLMBase>(rhs)
            );
        }

        /**
         * TODO : Documentation.
         */
        template <typename VectorType, typename ScalarType>
        inline VectorType operator/(const VectorType& lhs, const ScalarType& rhs)
        {
            // NOTE : This cast and construct is lame, but MSVC ADL is having trouble with it otherwise.
            return lhs / VectorType(static_cast<float>(rhs));
        }

        /**
         * TODO : Documentation.
         */
        template <typename VectorType>
        inline VectorType operator/(const VectorType& lhs, const VectorType& rhs)
        {
            return VectorType(
                static_cast<typename VectorType::GLMBase>(lhs) /
                static_cast<typename VectorType::GLMBase>(rhs)
            );
        }

        /**
         * TODO : Documentation.
         */
        template <typename DSTType, typename GLMType>
        inline std::ostream& operator<<(std::ostream& stream, const VectorBase<DSTType, GLMType>& vector)
        {
            stream << vector.to_string();
            return stream;
        }
    } // namespace detail
} // namespace Dynamic_Static
