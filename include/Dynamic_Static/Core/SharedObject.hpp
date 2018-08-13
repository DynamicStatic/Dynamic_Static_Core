
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <memory>

namespace Dynamic_Static {

    /*
    * Provides an inheritable interface for std::enable_shared_from_this.
    */
    template <typename CRTP>
    class SharedObject
        : public std::enable_shared_from_this<CRTP>
    {
    public:
        /*
        * Gets a std::shared_ptr<> to this SharedObject.
        * @return An std::shared_ptr<> to this SharedObject
        */
        inline std::shared_ptr<CRTP> get_shared_ptr()
        {
            return shared_from_this();
        }

        /*
        * Gets a std::shared_ptr<const> to this SharedObject.
        * @return An std::shared_ptr<const> to this SharedObject
        */
        inline std::shared_ptr<const CRTP> get_shared_ptr() const
        {
            return shared_from_this();
        }

        /*
        * Gets a std::weak_ptr<> to this SharedObject.
        * @return An std::weak_ptr<> to this SharedObject
        */
        inline std::weak_ptr<CRTP> get_weak_ptr()
        {
            return weak_from_this();
        }

        /*
        * Gets a std::weak_ptr<const> to this SharedObject.
        * @return An std::weak_ptr<const> to this SharedObject
        */
        inline std::weak_ptr<const CRTP> get_weak_ptr() const
        {
            return weak_from_this();
        }
    };

} // namespace Dynamic_Static
