
/*
================================================================================

  MIT License

  Copyright (c) 2017 Dynamic_Static

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

#include "Dynamic_Static/Core/Math/Defines.hpp"
#include "Dynamic_Static/Core/Math/Vector3.hpp"
#include "Dynamic_Static/Core/Math/Vector2.hpp"S

#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(push, 0)
#endif
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/string_cast.hpp"
#if defined(DYNAMIC_STATIC_MSVC)
    #pragma warning(pop)
#endif

namespace Dynamic_Static
{
    /**
     * Represents a 4 x 4 matrix.
     */
    struct Matrix4x4
        : public glm::mat4
    {
    public:
        static const Matrix4x4 Identity;

    public:
        using glm::mat4::tmat4x4;

    public:
        /**
         * Gets the std::string representation of this Matrix4x4.
         * @return The std::string representation of this Matrix4x4
         */
        inline std::string to_string() const
        {
            return glm::to_string(*this);
        }

        /**
         * Creates a view Matrix4x4.
         * @param [in] position The position to create the view from
         * @param [in] target   The target point of the view
         * @param [in] up       The view's up vector
         * @return The view Matrix4x4
         */
        static inline Matrix4x4 create_view(
            const Vector3& position, const Vector3& target, const Vector3& up
        )
        {
            return glm::lookAt(position, target, up);
        }

        /**
         * Creates a perspective projection Matrix4x4.
         * @param [in] fieldOfView The projection's field of view
         * @param [in] aspectRatio The projection's aspect ratio
         * @param [in] nearPlane   The projection's near plane
         * @param [in] farPlane    The projection's far plane
         * @return The perspective projection Matrix4x4
         */
        static inline Matrix4x4 create_perspective(
            float fieldOfView, float aspectRatio, float nearPlane, float farPlane
        )
        {
            return glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        }

        /**
         * Creates an orthographic projection Matrix4x4.
         * @param [in] left      The projection's left edge
         * @param [in] right     The projection's right edge
         * @param [in] top       The projection's top edge
         * @param [in] bottom    The projection's bottom edge
         * @param [in] nearPlane The projection's near plane
         * @param [in] farPlane  The projection's far plane
         * @return The orhtographic projection Matrix4x4
         */
        static inline Matrix4x4 create_orhtographic(
            float left, float right, float top, float bottom, float nearPlane, float farPlane
        )
        {
            return glm::ortho(left, right, bottom, top, nearPlane, farPlane);
        }
    };

    const Matrix4x4 Matrix4x4::Identity {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    static_assert(
        sizeof(Matrix4x4) == sizeof(glm::mat4),
        "sizeof(Matrix4x4) must equal sizeof(glm::mat4)"
    );
} // namespace Dynamic_Static
