
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
#include "Dynamic_Static/Core/TypeUtilities.hpp"

#include "gsl/span"

#include <algorithm>
#include <memory>
#include <tuple>
#include <vector>

namespace Dynamic_Static {

    /**
     * Encapsulates std::weak_ptr access to groups of objects managed by std::shared_ptrs.
     * @param <ObjectTypes> The types of shared objects to maintain std:weak_ptrs to
     */
    template <typename ...ObjectTypes>
    class SharedObjectFactory
        : NonCopyable
    {
    private:
        // TODO : MultiTypeContainer...ala http://stackoverflow.com/a/20703174/3453616
        mutable std::tuple<std::vector<std::weak_ptr<ObjectTypes>>...> mSharedObjects;

    public:
        /**
         * Constructs an instance of SharedObjectFactory.
         */
        SharedObjectFactory() = default;

        /**
         * Moves an instance of SharedObjectFactory.
         * @param [in] other The SharedObjectFactory to move from
         */
        SharedObjectFactory(SharedObjectFactory&& other) = default;

        /**
         * Moves an instance of SharedObjectFactory.
         * @param [in] other The SharedObjectFactory to move from
         */
        SharedObjectFactory& operator=(SharedObjectFactory&& other) = default;

    public:
        /**
         * Gets this SharedObjectFactory's shared objects of a given type.
         * @param <T> The type of shared objects to get
         * @return This SharedObjectFactory's shared objects of the given type
         */
        template <typename T>
        const gsl::span<std::weak_ptr<T>> objects() const
        {
            return validated_objects<T>();
        }

        /**
         * Creates a shared object of a given type.
         * @param <T>    The type of shared object to create
         * @param <Args> Arguments to the shared object's constructor
         * @return The newly created shared object
         */
        template <typename T, typename ...Args>
        std::shared_ptr<T> make_shared(Args&&... args)
        {
            // TODO : Accept an allocator and use std::allocate_shared().
            auto sharedObject = std::make_shared<T>(std::forward<Args>(args)...);
            validated_objects<T>().push_back(sharedObject);
            return sharedObject;
        }

        /**
         * Creates a shared object of a given type.
         * @param <T>         The type of shared object to create
         * @param [in] object A pointer to the object to make shared
         * @return The newly created shared object
         */
        template <typename T>
        std::shared_ptr<T> make_shared(T* object)
        {
            auto sharedObject = std::shared_ptr<T>(object);
            validated_objects<T>().push_back(sharedObject);
            return sharedObject;
        }

    private:
        template <typename T>
        std::vector<std::weak_ptr<T>>& validated_objects() const
        {
            // TODO : Why isn't std::get<>() by type working?
            //        http://en.cppreference.com/w/cpp/utility/tuple/get
            constexpr size_t index = dst::type_index<T, ObjectTypes...>();
            auto& objects = std::get<index>(mSharedObjects);
            objects.erase(
                std::remove_if(
                    objects.begin(),
                    objects.end(),
                    [](std::weak_ptr<T> object)
                    {
                        return object.expired();
                    }
                ),
                objects.end()
            );

            return objects;
        }
    };

} // namespace dynamic_static
