
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
#include <glm/gtc/matrix_transform.hpp>
#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif

namespace Dynamic_Static {
    namespace Math {
        const Matrix4x4 Matrix4x4::Identity {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        };
    } // namespace Math
} // namespace Dynamic_Static

//namespace Dynamic_Static {
//    namespace Math {
//        Matrix4x4::Matrix4x4(const glm::mat4x4& other)
//            : glm::mat4x4(other)
//        {
//        }
//
//        Matrix4x4& Matrix4x4::operator=(const glm::mat4x4& other)
//        {
//            glm::mat4x4::operator=(other);
//            return *this;
//        }
//
//        void Matrix4x4::rotate(float angle, const Vector3& axis)
//        {
//            *this = glm::rotate(*this, angle, axis._vec3);
//        }
//
//        void Matrix4x4::rotate_x(float angleRadians)
//        {
//            rotate(angleRadians, Vector3(1, 0, 0));
//        }
//
//        void Matrix4x4::rotate_y(float angleRadians)
//        {
//            rotate(angleRadians, Vector3(0, 1, 0));
//        }
//
//        void Matrix4x4::rotate_z(float angleRadians)
//        {
//            rotate(angleRadians, Vector3(0, 0, 1));
//        }
//
//        void Matrix4x4::look_at(const Vector3& eye, const Vector3& center, const Vector3& up)
//        {
//            *this = glm::lookAt(eye._vec3, center._vec3, up._vec3);
//        }
//
//        Matrix4x4 Matrix4x4::rotate(const Matrix4x4& matrix, float angle, const Vector3& axis)
//        {
//            return glm::rotate(matrix, angle, axis._vec3);
//        }
//
//        Matrix4x4 Matrix4x4::perspective(float fovY, float aspect_ratio, float nearPlane, float farPlane)
//        {
//            return glm::perspective(fovY, aspect_ratio, nearPlane, farPlane);
//        }
//
//        Matrix4x4 Matrix4x4::create_rotation_x(float angleRadians)
//        {
//            return glm::rotate(glm::mat4x4(), angleRadians, glm::vec3(1, 0, 0));
//        }
//
//        Matrix4x4 Matrix4x4::create_rotation_y(float angleRadians)
//        {
//            return glm::rotate(glm::mat4x4(), angleRadians, glm::vec3(0, 1, 0));
//        }
//
//        Matrix4x4 Matrix4x4::create_rotation_z(float angleRadians)
//        {
//            return glm::rotate(glm::mat4x4(), angleRadians, glm::vec3(0, 0, 1));
//        }
//
//        Matrix4x4 Matrix4x4::create_scale(const Vector3& scale)
//        {
//            return glm::scale(glm::mat4x4(), scale._vec3);
//        }
//
//        const Matrix4x4 Matrix4x4::identity;
//    } // namespace Math
//} // namespace Dynamic_Static
