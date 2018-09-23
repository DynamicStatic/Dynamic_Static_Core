
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Component.hpp"
#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <algorithm>
#include <vector>

namespace Dynamic_Static {

    /*!
    */
    class Entity
        : NonCopyable
    {
    private:
        std::vector<Component::Handle> mComponents;

    public:
        /*!
        */
        inline Entity() = default;

        /*!
        */
        inline Entity(Entity&& other)
        {
            *this = std::move(other);
        }

        /*!
        */
        inline Entity& operator=(Entity&& other)
        {
            if (this != &other) {
                mComponents = std::move(other.mComponents);
            }
            return *this;
        }

    public:
        /*!
        */
        template <typename ComponentType>
        ComponentType* add_component(Component::Pool<ComponentType>& pool)
        {
            auto component = pool.check_out();
            if (component) {
                auto typeId = Component::get_type_id<ComponentType>();
                Component::Handle handle(typeId, &pool, component);
                Component::Handle::Comparator comparator;
                auto itr = std::lower_bound(mComponents.begin(), mComponents.end(), handle, comparator);
                mComponents.insert(itr, std::move(handle));
            }
            return (ComponentType*)component;
        }

        /*!
        */
        template <typename ComponentType>
        ComponentType* get_component()
        {
            return const_cast<ComponentType*>(std::as_const(*this).get_component<ComponentType>());
        }

        /*!
        */
        template <typename ComponentType>
        const ComponentType* get_component() const
        {
            auto typeId = Component::get_type_id<ComponentType>();
            Component::Handle::Comparator comparator;
            auto itr = std::lower_bound(mComponents.begin(), mComponents.end(), typeId, comparator);
            return itr != mComponents.end() ? (ComponentType*)itr->get_component() : nullptr;
        }
    };

} // namespace Dynamic_Static
