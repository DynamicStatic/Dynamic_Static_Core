#if 0
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include <utility>
#include <vector>

namespace dst {

    /*!
    */
    class Component
    {
    public:
        /*!
        */
        class IPool
        {
        public:
            /*!
            */
            virtual size_t total() const = 0;

            /*!
            */
            virtual size_t count() const = 0;

            /*!
            */
            virtual size_t empty() const = 0;

            /*!
            */
            virtual void* check_out() = 0;

            /*!
            */
            virtual void check_in(void*) = 0;
        };

        /*!
        */
        template <typename ComponentType>
        class Pool
            : public IPool
            , NonCopyable
        {
        private:
            std::vector<ComponentType> mComponents;
            std::vector<ComponentType*> mCheckedIn;

        public:
            /*!
            */
            inline Pool() = default;

            /*!
            */
            inline Pool(size_t count)
                : mComponents(count)
                , mCheckedIn(count)
            {
                for (size_t i = 0; i < count; ++i) {
                    mCheckedIn[i] = &mComponents[i];
                }
            }

            /*!
            */
            inline Pool(Pool<ComponentType>&& other)
            {
                *this = std::move(other);
            }

            /*!
            */
            inline Pool& operator=(Pool<ComponentType>&& other)
            {
                if (this != &other) {
                    mComponents = std::move(other.mComponents);
                    mCheckedIn = std::move(other.mCheckedIn);
                }
                return *this;
            }

        public:
            /*!
            */
            inline size_t total() const override
            {
                return mComponents.size();
            }

            /*!
            */
            inline size_t count() const override
            {
                return mCheckedIn.size();
            }

            /*!
            */
            inline size_t empty() const override
            {
                return mCheckedIn.empty();
            }

            /*!
            */
            inline void* check_out() override
            {
                ComponentType* component = nullptr;
                if (!empty()) {
                    component = mCheckedIn.back();
                    mCheckedIn.pop_back();
                }
                return component;
            }

            /*!
            */
            inline void check_in(void* component) override
            {
                assert(&mComponents.front() <= component && component <= &mComponents.back());
                auto itr = std::lower_bound(mCheckedIn.begin(), mCheckedIn.end(), (ComponentType*)component);
                mCheckedIn.insert(itr, (ComponentType*)component);
            }

            /*!
            */
            template <typename ProcessFunctionType>
            inline void process_components(ProcessFunctionType process)
            {
                for (auto& component : mComponents) {
                    process(component);
                }
            }
        };

        /*!
        */
        class Handle final
            : NonCopyable
        {
        public:
            /*!
            */
            struct Comparator final
            {
                /*!
                */
                inline bool operator()(const Handle& lhs, const Handle& rhs)
                {
                    return
                        lhs.mTypeId < rhs.mTypeId ||
                        lhs.mPool < rhs.mPool ||
                        lhs.mComponent < rhs.mComponent;
                }

                /*!
                */
                inline bool operator()(const Handle& lhs, uint64_t rhs)
                {
                    return lhs.mTypeId < rhs;
                }

                /*!
                */
                inline bool operator()(uint64_t lhs, const Handle& rhs)
                {
                    return lhs < rhs.mTypeId;
                }
            };

        private:
            uint64_t mTypeId { 0 };
            IPool* mPool { nullptr };
            void* mComponent { nullptr };

        public:
            /*!
            */
            inline Handle(
                uint64_t typeId,
                IPool* pool,
                void* component
            )
                : mTypeId { typeId }
                , mPool { pool }
                , mComponent { component }
            {
                // TODO : Need to use indices into pool vs pointers...not sure
                //  exactly how to do that when we don't have a pool for some
                //  components...
                // TODO : Need to figure out how to deal with Components adding
                //  themselves mutliple times to the same Entity as their own
                //  base...specifically, how to deal with dtors...it's ok for
                //  now...only ShapeBlaster is using it and ShapeBlaster
                //  Entities never remove Components until they die.
                assert(mTypeId);
                assert(mComponent);
            }

            /*!
            */
            inline Handle() = default;

            /*!
            */
            inline Handle(Handle&& other)
            {
                *this = std::move(other);
            }

            /*!
            */
            inline ~Handle()
            {
                check_in();
            }

            /*!
            */
            inline Handle& operator=(Handle&& other)
            {
                if (this != &other) {
                    check_in();
                    mTypeId = std::move(other.mTypeId);
                    mPool = std::move(other.mPool);
                    mComponent = std::move(other.mComponent);
                    other.mTypeId = 0;
                    other.mPool = nullptr;
                    other.mComponent = nullptr;
                }
                return *this;
            }

        public:
            /*!
            */
            uint64_t get_type_id() const
            {
                return mTypeId;
            }

            /*!
            */
            void* get_component()
            {
                return mComponent;
            }

            /*!
            */
            const void* get_component() const
            {
                return mComponent;
            }

        private:
            void check_in()
            {
                if (mPool && mComponent) {
                    mPool->check_in(mComponent);
                    mTypeId = 0;
                    mPool = nullptr;
                    mComponent = nullptr;
                }
            }
        };

    public:
        /*!
        */
        template <typename ComponentType>
        static inline uint64_t get_type_id()
        {
            static uint8_t sId;
            return (uint64_t)&sId;
        }
    };

} // namespace dst
#endif