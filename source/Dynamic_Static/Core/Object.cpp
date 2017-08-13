
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Object.hpp"

namespace Dynamic_Static {

    Object::Object(Object&& other)
    {
        *this = std::move(other);
    }

    Object::~Object()
    {
    }

    Object& Object::operator=(Object&& other)
    {
        if (this != &other) {
            mName = std::move(other.mName);
        }

        return *this;
    }

    bool Object::operator==(const Object& other)
    {
        return this == &other;
    }

    bool Object::operator!=(const Object& other)
    {
        return !operator==(other);
    }
    const std::string& Object::name() const
    {
        return mName;
    }

    void Object::name(const std::string& name)
    {
        mName = name;
    }

} // namespace Dynamic_Static
