
/*
==========================================
    Copyright (c) 2016 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Math/Defines.hpp"
#if !defined(DYNAMIC_STATIC_DISABLE_MATH_BUILD)

#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Quaternion.hpp"
#include "Dynamic_Static/Core/Math/Vector2.hpp"
#include "Dynamic_Static/Core/Math/Vector3.hpp"
#include "Dynamic_Static/Core/Math/Vector4.hpp"

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/transform.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static {

    /**
     * Represents a 4 x 4 matrix.
     */
    struct Matrix4x4
        : public glm::mat4
    {
    public:
        static const Matrix4x4 Identity;

    public:
        using glm::mat4::mat;

        /**
         * Constructs an instance of Matrix4x4.
         */
        inline Matrix4x4()
        {
            *this = Identity;
        }

        /**
         * Constructs an instance of Matrix4x4.
         * @param [in] translation This Matrix4x4's translation
         * @param [in] rotation    This Matrix4x4's rotation
         * @param [in] scale       This Matrix4x4's scale
         */
        inline Matrix4x4(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
        {
            *this = create_translation(translation) * create_rotation(rotation) * create_scale(scale);
        }

        /**
         * TODO : Documentation.
         */
        inline Matrix4x4& operator*=(const Matrix4x4& other)
        {
            *this = glm::operator*(*this, other);
            return *this;
        }

    public:
        /**
         * Gets the std::string representation of this Matrix4x4.
         * @return The std::string representation of this Matrix4x4
         */
        inline std::string to_string() const
        {
            // TODO : Hide operator[]().
            return
                "{" +
                    Vector4(this->operator[](0)).to_string() + ", " +
                    Vector4(this->operator[](1)).to_string() + ", " +
                    Vector4(this->operator[](2)).to_string() + ", " +
                    Vector4(this->operator[](3)).to_string() +
                "}";
        }

        /**
         * Translates this Matrix4x4.
         * @param [in] translation The translation to apply to this Matrix4x4
         */
        inline void translate(const Vector3& translation)
        {
            *this = glm::translate(*this, translation);
        }

        /**
         * Rotates this Matrix4x4.
         * @param [in] angle The angle to rotate this Matrix4x4 by
         * @param [in] axis  The axis to rotate this Matrix4x4 along
         */
        inline void rotate(float angle, const Vector3 axis)
        {
            *this = glm::rotate(*this, angle, axis);
        }

        /**
         * Rotates this Matrix4x4.
         * @param [in] rotation The rotation to apply to this Matrix4x4
         */
        inline void rotate(const Quaternion& rotation)
        {
            *this *= create_rotation(rotation);
        }

        /**
         * Scales this Matrix4x4.
         * @param [in] scale The scale to apply to this Matrix4x4
         */
        inline void scale(const Vector3& scale)
        {
            *this = glm::scale(*this, scale);
        }

        /**
         * Gets this Matrix4x4's inverse.
         * @return This Matrix4x4's inverse
         */
        inline Matrix4x4 inverse() const
        {
            return glm::inverse(*static_cast<const glm::mat4*>(this));
        }

        /**
         * Creates a translation.
         * @param [in] translation The translation
         * @param [in] The Matrix4x4 representation of the given translation
         */
        static inline Matrix4x4 create_translation(const Vector3& translation)
        {
            return glm::translate(Identity, translation);
        }

        /**
         * Creates a rotation.
         * @param [in] angle The angle of the rotation
         * @param [in] axis  The axis of the rotation
         */
        static inline Matrix4x4 create_rotation(float angle, const Vector3& axis)
        {
            return glm::rotate(Identity, angle, axis);
        }

        /**
         * Creates a rotation.
         * @param [in] rotation The rotation
         * @param [in] The Matrix4x4 representation of the given rotation
         */
        static inline Matrix4x4 create_rotation(const Quaternion& rotation)
        {
            return glm::toMat4(rotation);
        }

        /**
         * Creates a scale.
         * @param [in] scale The scale
         * @param [in] The Matrix4x4 representation of the given scale
         */
        static inline Matrix4x4 create_scale(const Vector3& scale)
        {
            return glm::scale(Identity, scale);
        }

        /**
         * Creates a view.
         * @param [in] position The position to create the view from
         * @param [in] target   The target point of the view
         * @param [in] up       The view's up vector
         * @return The view
         */
        static inline Matrix4x4 create_view(
            const Vector3& position, const Vector3& target, const Vector3& up
        )
        {
            return glm::lookAt(position, target, up);
        }

        /**
         * Creates a perspective projection.
         * @param [in] fieldOfView The projection's field of view
         * @param [in] aspectRatio The projection's aspect ratio
         * @param [in] nearPlane   The projection's near plane
         * @param [in] farPlane    The projection's far plane
         * @return The perspective projection
         */
        static inline Matrix4x4 create_perspective(
            float fieldOfView, float aspectRatio, float nearPlane, float farPlane
        )
        {
            return glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        }

        /**
         * Creates an orthographic projection.
         * @param [in] left      The projection's left edge
         * @param [in] right     The projection's right edge
         * @param [in] top       The projection's top edge
         * @param [in] bottom    The projection's bottom edge
         * @param [in] nearPlane The projection's near plane
         * @param [in] farPlane  The projection's far plane
         * @return The orhtographic projection
         */
        static inline Matrix4x4 create_orhtographic(
            float left, float right, float top, float bottom, float nearPlane, float farPlane
        )
        {
            return glm::ortho(left, right, bottom, top, nearPlane, farPlane);
        }
    };

    /**
     * TODO : Documentation.
     */
    inline Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
    {
        return glm::operator*(lhs, rhs);
    }

    /**
     * TODO : Documentation.
     */
    inline Vector2 operator*(const Matrix4x4& lhs, const Vector2& rhs)
    {
        return glm::operator*(lhs, Vector4(rhs));
    }

    /**
     * TODO : Documentation.
     */
    inline Vector3 operator*(const Matrix4x4& lhs, const Vector3& rhs)
    {
        return glm::operator*(lhs, Vector4(rhs));
    }

    /**
     * TODO : Documentation.
     */
    inline Vector4 operator*(const Matrix4x4& lhs, const Vector4& rhs)
    {
        return glm::operator*(lhs, rhs);
    }

    static_assert(
        sizeof(Matrix4x4) == sizeof(glm::mat4),
        "sizeof(Matrix4x4) must equal sizeof(glm::mat4)"
    );

} // namespace Dynamic_Static

#endif
