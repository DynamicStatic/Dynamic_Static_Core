
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

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/IPrintable.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <string>

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    class Object
        : public IPrintable
        , NonCopyable {
    protected:
        std::string m_name { "Dynamic_Static::Object" };

    public:
        /**
         * Constructs an instance of Object.
         */
        Object() = default;

        /**
         * Moves an instance of Object.
         * @param [in] other The Object to move from
         */
        Object(Object&& other);

        /**
         * Destroys this Object.
         */
        virtual ~Object() = 0;

        /**
         * Moves an instance of Object.
         * @param [in] other The Object to move from
         */
        Object& operator=(Object&& other);

        /**
         * Compares two Objects for equality.
         * @param [in] other The Object to compare to this Object
         * @return Whether or not the copmared Objects are equal
         */
        virtual bool operator==(const Object& other);

        /**
         * Compares two Objects for inequality.
         * @param [in] other The Object to compare to this Object
         * @return Whether or not the copmared Objects are inequal
         */
        virtual bool operator!=(const Object& other);

    public:
        /**
         * Gets this Object's name.
         * @return This Object's name
         */
        virtual const std::string& name() const;

        /**
         * Sets this Object's name.
         * @param [in] This Object's name
         */
        virtual void name(const std::string& name);

        /**
         * Gets this Object's std::string representation.
         * @return This Object's std::string representation
         */
        virtual std::string to_string() const;
    };
}
