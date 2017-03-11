
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

#include "Dynamic_Static/Math/Defines.hpp"

#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(push, 0)
#endif
#include <glm/gtc/quaternion.hpp>
#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        struct Quaternion final {
            friend struct Vector2;
            friend struct Vector3;
            friend struct Vector4;
            friend struct Matrix3x3;
            friend struct Matrix4x4;
            friend Quaternion operator*(const Quaternion&, const Quaternion&);
        private:
            glm::quat mQuat;

        public:
            Quaternion();
            Quaternion(float x, float y, float z, float w);
            Quaternion(const Vector3& v);

            float x() const;
            float y() const;
            float z() const;
            float w() const;
            void x(float x);
            void y(float y);
            void z(float z);
            void w(float w);

            void normalize();
            Vector3 rotate(const Vector3& v);
            Vector4 rotate(const Vector4& v);
            static Quaternion angle_axis(float angle, const Vector3& axis);

            static const Quaternion identity;

        private:
            Quaternion(const glm::quat& quat);
        };

        Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);

        static_assert(
            sizeof(Quaternion) == sizeof(float) * 4,
            "sizeof(Quaternion) must equal sizeof(float) * 4"
        );
    } // namespace Math
} // namespace Dynamic_Static
