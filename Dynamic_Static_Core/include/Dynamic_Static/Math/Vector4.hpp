
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
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif

namespace std {
    template <>
    struct hash<dst::math::Vector3>;
}

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        struct Vector4 final {
            friend struct Vector2;
            friend struct Vector3;
            friend struct Matrix3x3;
            friend struct Matrix4x4;
            friend struct Quaternion;
            friend struct std::hash<Vector4>;
        private:
            glm::vec4 mVec4;

        public:
            Vector4() = default;
            Vector4(float x, float y, float z, float w);
            Vector4(const Vector4& other);
            Vector4(const Vector3& other);
            Vector4(const Vector3& other, float w);

            float x() const;
            float y() const;
            float z() const;
            float w() const;
            void x(float x);
            void y(float y);
            void z(float z);
            void w(float w);

            void normalize();

            static const Vector4 one;
            static const Vector4 zero;
            static const Vector4 up;
            static const Vector4 down;
            static const Vector4 left;
            static const Vector4 right;
            static const Vector4 forward;
            static const Vector4 backward;

        private:
            Vector4(const glm::vec4 vec4);
        };

        bool operator==(const Vector4& lhs, const Vector4& rhs);
        Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
        Vector4 operator-(const Vector4& v);

        static_assert(
            sizeof(Vector4) == sizeof(float) * 4,
            "sizeof(Vector4) must equal sizeof(float) * 4"
        );
    }
}

namespace std {
    /**
     * TODO : Documentation.
     */
    template <>
    struct hash<dst::math::Vector4> {
        /**
         * TODO : Documentation.
         */
        size_t operator()(const dst::math::Vector4& v) const
        {
            return hash<glm::vec4>()(v.mVec4);
        }
    };
}
