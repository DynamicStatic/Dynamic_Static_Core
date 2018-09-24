
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
        template <typename ComponentType, typename ...Args>
        inline ComponentType* add_component(
            Component::Pool<ComponentType>& pool,
            Args&&... args
        )
        {
            ComponentType* component = (ComponentType*)pool.check_out();
            if (component) {
                *component = ComponentType(std::forward<Args>(args)...);
                auto typeId = Component::get_type_id<ComponentType>();
                Component::Handle handle(typeId, &pool, component);
                Component::Handle::Comparator comparator;
                auto itr = std::lower_bound(mComponents.begin(), mComponents.end(), handle, comparator);
                mComponents.insert(itr, std::move(handle));
                call_on_add(component);
            }
            return component;
        }

        /*!
        */
        template <typename ComponentType>
        inline ComponentType* add_component(ComponentType* component)
        {
            if (component) {
                // TODO : Need to prevent the same component being added
                //  multiple times.
                auto typeId = Component::get_type_id<ComponentType>();
                Component::Handle handle(typeId, nullptr, component);
                Component::Handle::Comparator comparator;
                auto itr = std::lower_bound(mComponents.begin(), mComponents.end(), handle, comparator);
                mComponents.insert(itr, std::move(handle));
                call_on_add(component);
            }
            return component;
        }

        /*!
        */
        template <typename ComponentType>
        inline ComponentType* get_component()
        {
            return const_cast<ComponentType*>(std::as_const(*this).get_component<ComponentType>());
        }

        /*!
        */
        template <typename ComponentType>
        inline const ComponentType* get_component() const
        {
            auto typeId = Component::get_type_id<ComponentType>();
            Component::Handle::Comparator comparator;
            auto itr = std::lower_bound(mComponents.begin(), mComponents.end(), typeId, comparator);
            return itr != mComponents.end() ? (ComponentType*)itr->get_component() : nullptr;
        }

        /*!
        */
        inline void remove_all_components()
        {
            mComponents.clear();
        }

    private:
        template <typename ComponentType>
        struct has_on_add final
        {
            template <typename T> static std::false_type test(...) { }
            template <typename T> static auto test(int)->decltype(&T::on_add, std::true_type()) { }
            static constexpr bool value { std::is_same<std::true_type, decltype(test<ComponentType>(0))>::value };
        };

        template <typename ComponentType>
        typename std::enable_if<has_on_add<ComponentType>::value>::type
            call_on_add(ComponentType* component)
        {
            component->on_add(*this);
        }

        template <typename ComponentType>
        typename std::enable_if<!has_on_add<ComponentType>::value>::type
            call_on_add(ComponentType*)
        {
        }
    };

} // namespace Dynamic_Static
