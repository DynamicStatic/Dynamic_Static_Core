
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
#include "Dynamic_Static/Math/3rdParty/glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "Dynamic_Static/Math/3rdParty/glm/gtx/hash.hpp"
#if defined(DYNAMIC_STATIC_VISUAL_STUDIO)
#pragma warning(pop)
#endif

namespace Dynamic_Static {
    namespace Math {
        /**
         * TODO : Documentation.
         */
        struct Vector3 final
            : public glm::vec3::tvec3 {
            using glm::vec3::tvec3;
            static const Vector3 one;
            static const Vector3 zero;
            static const Vector3 x;
            static const Vector3 y;
            static const Vector3 z;
            static const Vector3 up;
            static const Vector3 down;
            static const Vector3 left;
            static const Vector3 right;
            static const Vector3 forward;
            static const Vector3 backward;
        };

        static_assert(
            sizeof(Vector3) == sizeof(float) * 3,
            "sizeof(Vector3) must equal sizeof(float) * 3"
        );
    }
}

namespace std {
    /**
     * TODO : Documentation.
     */
    template <>
    struct hash<dst::math::Vector3> {
        /**
         * TODO : Documentation.
         */
        size_t operator()(const dst::math::Vector3& v) const
        {
            return hash<glm::vec3>()(v);
        }
    };
}
