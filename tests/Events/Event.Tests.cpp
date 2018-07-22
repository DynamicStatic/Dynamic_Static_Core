
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

// #include "Dynamic_Static/Core/Events/Event.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    static constexpr int TestCount { 16 };

#if 0
    class Publisher final
    {
    public:
        Event<Publisher, const Publisher&> on_event;

        void fire_event() const
        {
            on_event(*this);
        }
    };

    class Listener final
    {
    private:
        int mInvocationCount { };
        Delegate<const Publisher&> mOnPublisherEvent;

    public:

    };
#endif

    TEST_CASE("Delegates can be assigned and called through Events", "[Event]")
    {

    }

} // namespace Tests
} // namespace Dynamic_Static
