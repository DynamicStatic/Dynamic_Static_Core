
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/VectorUtilities.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <set>
#include <string>

namespace Dynamic_Static {
namespace Tests {

    static constexpr size_t TestCount = 128;
    static dst::RandomNumberGenerator sgRng;

    class Animal
    {
    private:
        std::string mName;

    public:
        Animal(const std::string& name) : mName { name } { }
        const std::string& name() const { return mName; }
    };

    class Dog final : public Animal { public: using Animal::Animal; };
    class Cat final : public Animal { public: using Animal::Animal; };

    std::string create_random_name()
    {
        std::string name = "name";
        for (size_t i = 0; i < name.size(); ++i) {
            name[i] = static_cast<char>(sgRng.range(32, 126));
        }
        return name;
    }

    TEST_CASE("convert()", "[VectorUtilitites]")
    {
        std::vector<Dog> dogs;
        for (size_t i = 0; i < TestCount; ++i) {
            dogs.push_back(Dog(create_random_name()));
        }

        auto cats = dst::convert<Dog, Cat>(
            dogs,
            [](const Dog& dog)
            {
                return Cat(dog.name());
            }
        );

        bool success = true;
        for (size_t i = 0; i < dogs.size(); ++i) {
            if (dogs[i].name() != cats[i].name()) {
                success = false;
                break;
            }
        }

        REQUIRE(success);
    }

    TEST_CASE("remove_duplicates()", "[VectorUtilities]")
    {
        std::vector<int> integers;
        integers.reserve(TestCount);
        for (size_t i = 0; i < TestCount; ++i) {
            integers.push_back(sgRng.value<int>());
        }

        for (auto& i : integers) {
            if (sgRng.probability(0.5f)) {
                i = integers[sgRng.index(integers.size())];
            }
        }

        dst::remove_duplicates(integers);

        bool success = true;
        std::set<int> integerSet;
        for (const auto& i : integers) {
            if (integerSet.find(i) != integerSet.end()) {
                success = false;
                break;
            }

            integerSet.insert(i);
        }

        REQUIRE(success);
    }

} // namespace Tests
} // namespace Dynamic_Static
