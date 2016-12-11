
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

#include "Dynamic_Static/Core/Object.hpp"

#include <utility>

namespace Dynamic_Static {
    Object::Object(Object&& other) { *this = std::move(other); }
    Object::~Object() { }
    Object& Object::operator=(Object&& other)
    {
        if (this != &other) {
            m_name = std::move(other.m_name);
        }

        return *this;
    }

    bool Object::operator==(const Object& other) { return this == &other; }
    bool Object::operator!=(const Object& other) { return this != &other; }
    const std::string& Object::name() const { return m_name; }
    void Object::name(const std::string& name) { m_name = name; }
    std::string Object::to_string() const { return name(); }
}
