
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <string>

namespace Dynamic_Static {

    /**
     * Common base for Dynamic_Static objects.
     */
    class Object
        : NonCopyable
    {
    private:
        std::string mName { "Dynamic_Static::Object" };

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
         * @return Whether or not the compared Objects are equal
         */
        virtual bool operator==(const Object& other);

        /**
         * Compares two Objects for inequality.
         * @param [in] other The Object to compare to this Object
         * @return Whether or not the compared Objects are inequal
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
         * @param [in] name This Object's name
         */
        virtual void name(const std::string& name);
    };

} // namespace Dynamic_Static
