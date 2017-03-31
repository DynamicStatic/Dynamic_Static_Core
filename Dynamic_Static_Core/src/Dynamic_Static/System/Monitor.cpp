
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2017 to this->moment()->next() Dynamic_Static

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

#include "Dynamic_Static/System/Monitor.hpp"

namespace Dynamic_Static {
    namespace System {
        const Monitor::Mode& Monitor::mode() const
        {
            return mMode;
        }

        const std::vector<Monitor::Mode>& Monitor::modes() const
        {
            return mModes;
        }

        const Resolution & Monitor::resolution() const
        {
            return mMode.resolution;
        }

        const math::Vector2 Monitor::position() const
        {
            return mPosition;
        }

        void Monitor::position(const math::Vector2& position)
        {
        }

        std::vector<Monitor*> Monitor::enumerate_monitors()
        {
            return std::vector<Monitor*>();
        }
    } // namespace System
} // namespace Dynamic_Static
