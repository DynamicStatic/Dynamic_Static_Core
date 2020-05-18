
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

namespace dst {
namespace tests {

    static constexpr int TestCount { 16 };

    static void set_target_value(int value, int& target)
    {
        target = value;
    }

    static void increment_target_value(int& target)
    {
        ++target;
    }

    class Obj final
    {
    public:
        void set_target_value(int value, int& target)
        {
            target = value;
        }

        void increment_target_value(int& target)
        {
            ++target;
        }
    };

    static Obj gObj;

    static std::vector<Delegate<int, int&>> create_set_target_delegates()
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

    static std::vector<Delegate<int&>> create_increment_target_delegates()
    {
        using namespace std::placeholders;
        std::vector<Delegate<int&>> delegates;
        delegates.push_back(Action<int&>(std::bind(&Obj::increment_target_value, &gObj, _1)));
        delegates.push_back(Action<int&>(increment_target_value));
        delegates.push_back(
            Action<int&>(
                [](int& target)
                {
                    ++target;
                }
            )
        );
        return delegates;
    }

    static bool validate_set_target_delegate_call(const Delegate<int, int&>& delegate)
    {
        RandomNumberGenerator rng;
        int value = rng.range<int>(0, 64);
        int target = 0;
        delegate(value, target);
        return value == target;
    }

    static bool validate_increment_target_delegate_call(const Delegate<int&>& delegate)
    {
        RandomNumberGenerator rng;
        int target = 0;
        delegate(target);
        return target == delegate.get_subscribers().size();
    }

    TEST_CASE("Actions can be assigned and called through Delegates", "[Delegate]")
    {
        auto delegates = create_set_target_delegates();
        for (auto& delegate : delegates) {
            REQUIRE(validate_set_target_delegate_call(delegate));
        }
    }

    TEST_CASE("Actions can be removed from Delegates", "[Delegate]")
    {
        auto delegates = create_set_target_delegates();
        for (auto& delegate : delegates) {
            delegate = nullptr;
        }
        for (auto& delegate : delegates) {
            REQUIRE(static_cast<bool>(delegate) == false);
        }
    }

    TEST_CASE("Delegates are moveable", "[Delegate]")
    {
        auto moveFrom = create_set_target_delegates();
        std::vector<Delegate<int, int&>> moveTo;
        for (auto& delegate : moveFrom) {
            moveTo.push_back(std::move(delegate));
        }
        for (auto& delegate : moveFrom) {
            REQUIRE(static_cast<bool>(delegate) == false);
        }
        for (auto& delegate : moveTo) {
            REQUIRE(validate_set_target_delegate_call(delegate));
        }
    }

    TEST_CASE("Delegates can multicast", "[Delegate]")
    {
        auto delegates = create_increment_target_delegates();
        Delegate<int&> multicast;
        for (auto& delegate : delegates) {
            multicast += delegate;
        }
        REQUIRE(validate_increment_target_delegate_call(multicast));
    }

    TEST_CASE("Multicast Delegates are moveable", "[Delegate]")
    {
        auto delegates = create_increment_target_delegates();
        Delegate<int&> moveFrom;
        for (auto& delegate : delegates) {
            moveFrom += delegate;
        }
        auto moveTo = std::move(moveFrom);
        REQUIRE(moveFrom.get_subscribers().empty());
        REQUIRE(validate_increment_target_delegate_call(moveTo));
    }

} // namespace tests
} // namespace dst
