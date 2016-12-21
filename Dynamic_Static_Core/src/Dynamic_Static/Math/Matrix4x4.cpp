
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

#include "Dynamic_Static/Math/Matrix4x4.hpp"
#include "Dynamic_Static/Math/Vector3.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif
#include "Dynamic_Static/Math/glm/gtc/matrix_transform.hpp"
#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif

namespace Dynamic_Static {
    namespace Math {
        Matrix4x4::Matrix4x4(const glm::mat4x4& other)
            : glm::mat4x4(other)
        {
        }

        Matrix4x4& Matrix4x4::operator=(const glm::mat4x4& other)
        {
            glm::mat4x4::operator=(other);
            return *this;
        }

        void Matrix4x4::rotate(float angle, const Vector3& axis)
        {
            glm::rotate(*this, angle, axis);
        }

        void Matrix4x4::look_at(const Vector3& eye, const Vector3& center, const Vector3& up)
        {
            *this = glm::lookAt(eye, center, up);
        }

        Matrix4x4 Matrix4x4::rotate(const Matrix4x4& matrix, float angle, const Vector3& axis)
        {
            return glm::rotate(matrix, angle, axis);
        }

        Matrix4x4 Matrix4x4::perspective(float fov_y, float aspect_ratio, float near_plane, float far_plane)
        {
            return glm::perspective(fov_y, aspect_ratio, near_plane, far_plane);
        }

        const Matrix4x4 Matrix4x4::identity;
    }
}
