
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/ToString.hpp"
#include "Dynamic_Static/Core/TypeUtilities.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_T_LENGTH
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#if defined(DYNAMIC_STATIC_MSVC)
// NOTE : GLM generates a bunch of warnings on MSVC, we're not going to edit
//        GLM to clear them so we don't want them adding noise to the build.
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ostream>

namespace Dynamic_Static {

    struct Color;
    struct Matrix4x4;
    struct Quaternion;
    struct Rectangle;
    class Transform;
    struct Vector2;
    struct Vector3;
    struct Vector4;

} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace detail {

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

    public:
        /**
         * TODO : Documentation.
         */
        inline VectorBase()
        {
            *this = DSTType::Zero;
        }

        /**
         * TODO : Documentation.
         */
        template <typename DSTTypeOther, typename GLMTypeOther>
        inline VectorBase(const VectorBase<DSTTypeOther, GLMTypeOther>& other)
        {
            *this = other;
        }

        /**
         * TODO : Documentation.
         */
        template <typename DSTTypeOther, typename GLMTypeOther>
        inline DSTBase& operator=(const VectorBase<DSTTypeOther, GLMTypeOther>& other)
        {
            for (size_t i = 0; i < Count; ++i) {
                if (i < other.Count) {
                    (*this)[i] = other[i];
                } else {
                    (*this)[i] = 0;
                }
            }

            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline DSTBase& operator+=(const DSTType& rhs)
        {
            *this = static_cast<GLMBase>(*this) + static_cast<GLMBase>(rhs);
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline DSTBase& operator-=(const DSTType& rhs)
        {
            *this = static_cast<GLMBase>(*this) - static_cast<GLMBase>(rhs);
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        template <typename ScalarType>
        inline DSTBase& operator*=(const ScalarType& rhs)
        {
            *this = static_cast<GLMBase>(*this) * rhs;
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline DSTBase& operator*=(const DSTType& rhs)
        {
            *this = static_cast<GLMBase>(*this) * static_cast<GLMBase>(rhs);
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        template <typename ScalarType>
        inline DSTBase& operator/=(const ScalarType& rhs)
        {
            *this = static_cast<GLMBase>(*this) / rhs;
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline DSTBase& operator/=(const DSTType& rhs)
        {
            *this = static_cast<GLMBase>(*this) / static_cast<GLMBase>(rhs);
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline operator GLMType&()
        {
            return *this;
        }

        /**
         * TODO : Documentation.
         */
        inline operator const GLMType&() const
        {
            return *this;
        }

    public:
        /**
         * TODO : Documentation.
         */
        static inline size_t count()
        {
            return Count;
        }

        /**
         * TODO : Documentation.
         */
        inline float length() const
        {
            return glm::length(static_cast<GLMBase>(*this));
        }

        /**
         * TODO : Documentation.
         */
        inline float length_squared() const
        {
            return glm::length2(static_cast<GLMBase>(*this));
        }

        /**
         * TODO : Documentation.
         */
        inline void normalize()
        {
            *this = glm::normalize(static_cast<GLMBase>(*this));
        }

        /**
         * TODO : Documentation.
         */
        inline DSTType normalized() const
        {
            return glm::normalize(static_cast<GLMBase>(*this));
        }

        /**
         * TODO : Documentation.
         */
        inline float distance(const DSTType& other) const
        {
            return distance(*this, other);
        }

        /**
         * TODO : Documentation.
         */
        inline float distance_squared(const DSTType& other) const
        {
            return distance_squared(*this, other);
        }

        /**
         * TODO : Documentation.
         */
        static inline float distance(const DSTType& lhs, const DSTType& rhs)
        {
            return glm::distance(
                static_cast<typename GLMBase>(lhs),
                static_cast<typename GLMBase>(rhs)
            );
        }

        /**
         * TODO : Documentation.
         */
        static inline float distance_squared(const DSTType& lhs, const DSTType& rhs)
        {
            return glm::distance2(
                static_cast<typename GLMBase>(lhs),
                static_cast<typename GLMBase>(rhs)
            );
        }

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
    };

} // namespace detail
} // namespace Dynamic_Static

namespace Dynamic_Static {
namespace detail {

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
        // NOTE : This cast and construct is lame, but MSVC ADL is having trouble without it.
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
        // NOTE : This cast and construct is lame, but MSVC ADL is having trouble without it.
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
