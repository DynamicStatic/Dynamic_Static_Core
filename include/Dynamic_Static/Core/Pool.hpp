
/*
==========================================
    Licensed under the MIT license
    Copyright (c) 2017 Dynamic_Static
        Patrick Purcell
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Defines.hpp"
#include "Dynamic_Static/Core/NonCopyable.hpp"

#include "gsl/span"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <strstream>
#include <utility>
#include <vector>

namespace Dynamic_Static {

    /**
     * TODO : Documentation.
     */
    template <typename ObjectType>
    class Pool
        : dst::NonCopyable
    {
    protected:
        std::vector<ObjectType> mObjects;
        std::vector<ObjectType*> mCheckedInObjects;

    public:
        /**
         * TODO : Documentation.
         */
        gsl::span<ObjectType> get_objects()
        {
            return mObjects;
        }

        /**
         * TODO : Documentation.
         */
        gsl::span<const ObjectType> get_objects() const
        {
            return mObjects;
        }

        /**
         * TODO : Documentation.
         */
        gsl::span<ObjectType*> get_checked_in_objects()
        {
            return mCheckedInObjects;
        }

        /**
         * TODO : Documentation.
         */
        gsl::span<const ObjectType*> get_checked_in_objects() const
        {
            return mCheckedInObjects;
        }

        /**
         * TODO : Documentation.
         */
        template <typename ...Args>
        Pool(Args&&... args)
        {
            mObjects = std::vector<ObjectType>(std::forward<Args>(args)...);
            mCheckedInObjects.reserve(mObjects.size());
            for (auto& object : mObjects) {
                mCheckedInObjects.push_back(&object);
            }
        }

    public:
        /**
         * TODO : Documentation.
         */
        ObjectType* check_out()
        {
            ObjectType* object = nullptr;
            check_out({ &object, 1 });
            return object;
        }

        /**
         * TODO : Documentation.
         */
        bool check_out(gsl::span<ObjectType*> objects)
        {
            bool success = !objects.empty() && objects.size() <= static_cast<ptrdiff_t>(mCheckedInObjects.size());
            if (success) {
                memcpy(objects.data(), &mCheckedInObjects.back() - objects.size(), objects.size_bytes());
                mCheckedInObjects.resize(mCheckedInObjects.size() - objects.size());
                on_check_out(objects);
            } else {
                memset(objects.data(), 0, objects.size_bytes());
            }

            return success;
        }

        /**
         * TODO : Documentation.
         */
        void check_in(ObjectType* object)
        {
            check_in({ &object, 1 });
        }

        /**
         * TODO : Documentation.
         */
        void check_in(gsl::span<ObjectType*> objects)
        {
            for (auto object : objects) {
                if (object < mObjects.front() || mObjects.back() < object) {
                    #if defined DYNAMIC_STATIC_DISABLE_EXCEPTIONS
                    assert(false && "dst::Pool::check_in() : Attempting to check in object that is not owned by this Pool.");
                    #else
                    throw std::logic_error("dst::Pool::check_in() : Attempting to check in object that is not owned by this Pool.");
                    #endif
                }

                // TODO : Check in...
            }

            on_check_in(objects);
        }

        // /**
        //  * TODO : Documentation.
        //  */
        // void check_in_all()
        // {
        //     mCheckedInObjects.resize(mObjects.size());
        //     for (size_t i = 0; i < mObjects.size(); ++i) {
        //         mCheckedInObjects[i] = *mObjects[i];
        //     }
        // }

    private:
        inline void on_check_out(...) { }
        template <typename T>
        inline auto on_check_out(gsl::span<T*> objects) -> decltype(objects[0]->on_check_out())
        {
            for (auto object : objects) {
                object->on_check_out();
            }
        }

        inline void on_check_in(...) { }
        template <typename T>
        inline auto on_check_in(gsl::span<T*> objects) -> decltype(objects[0]->on_check_in())
        {
            for (auto object : objects) {
                object->on_check_in();
            }
        }
    };

} // namespace Dynamic_Static
