
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Events/Delegate.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    static constexpr int TestCount { 16 };

    static void set_target_value(int value, int& target)
    {
        target = value;
    }

    class Obj final
    {
    public:
        void set_target_value(int value, int& target)
        {
            target = value;
        }
    };

    static Obj gObj;

    static std::vector<Delegate<int, int&>> create_delegates()
    {
        using namespace std::placeholders;
        std::vector<Delegate<int, int&>> delegates;
        delegates.push_back(Action<int, int&>(std::bind(&Obj::set_target_value, &gObj, _1, _2)));
        delegates.push_back(Action<int, int&>(set_target_value));
        delegates.push_back(
            Action<int, int&>(
                [](int value, int& target)
                {
                    target = value;
                }
            )
        );
        return delegates;
    }

    static bool validate_delegate_call(const Delegate<int, int&>& delegate)
    {
        RandomNumberGenerator rng;
        int value = rng.range<int>(0, 64);
        int target = 0;
        delegate(value, target);
        return value == target;
    }

#if 0
    TEST_CASE("Actions can be assigned and called through Delegates", "[Delegate]")
    {
        auto delegates = create_delegates();
        for (auto& delegate : delegates) {
            REQUIRE(validate_delegate_call(delegate));
        }
    }

    TEST_CASE("Actions can be removed from Delegates", "[Delegate]")
    {
        auto delegates = create_delegates();
        for (auto& delegate : delegates) {
            delegate = nullptr;
        }

        for (auto& delegate : delegates) {
            REQUIRE(static_cast<bool>(delegate) == false);
        }
    }

    TEST_CASE("Delegates are moveable", "[Delegate]")
    {
        auto moveFrom = create_delegates();
        std::vector<Delegate<int, int&>> moveTo;
        for (auto& delegate : moveFrom) {
            moveTo.push_back(std::move(delegate));
        }

        for (auto& delegate : moveFrom) {
            REQUIRE(static_cast<bool>(delegate) == false);
        }

        for (auto& delegate : moveTo) {
            REQUIRE(validate_delegate_call(delegate));
        }
    }
#endif

} // namespace Tests
} // namespace Dynamic_Static
