
/*
=====================================================================================

    The MIT License(MIT)

    Copyright(c) 2016 to this->moment()->next() Dynamic_Static

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

=====================================================================================
*/

#include "catch.hpp"

#include "Dynamic_Static/Core/VectorUtilities.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include <set>

namespace Dynamic_Static {
    namespace Tests {
        static const size_t gTestCount = 128;

        class Animal {
        private:
            std::string mName;
        public:
            Animal(const std::string& name) : mName { name } { }
            const std::string& name() const { return mName; }
        };

        class Dog final : public Animal { using Animal::Animal; };
        class Cat final : public Animal { using Animal::Animal; };

        std::string create_random_name()
        {
            std::string name = "name";
            for (size_t i = 0; i < name.size(); ++i) {
                name[i] = Random.range(32, 126);
            }

            return name;
        }

        TEST_CASE("convert() works correctly", "[VectorUtilitites]")
        {
            std::vector<Dog> dogs;
            for (size_t i = 0; i < gTestCount; ++i) {
                dogs.push_back(Dog(create_random_name()));
            }

            auto cats = convert<Dog, Cat>(dogs, [](const Dog& dog) { return Cat(dog.name()); });

            bool success = true;
            for (size_t i = 0; i < dogs.size(); ++i) {
                if (dogs[i].name() != cats[i].name()) {
                    success = false;
                    break;
                }
            }

            REQUIRE(success);
        }

        TEST_CASE("remove_duplicates() works correctly", "[VectorUtilities]")
        {
            std::vector<int> integers;
            integers.reserve(gTestCount);
            for (size_t i = 0; i < gTestCount; ++i) {
                integers.push_back(Random.range(-1024, 1024));
            }

            for (auto& i : integers) {
                if (Random.probability(0.5f)) {
                    i = integers[Random.index(integers.size())];
                }
            }

            remove_duplicates(integers);

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

        TEST_CASE("take_ownership() works correctly", "[VectorUtilities]")
        {
            std::vector<std::unique_ptr<Dog>> dogs;
            for (size_t i = 0; i < gTestCount; ++i) {
                dogs.push_back(std::make_unique<Dog>(create_random_name()));
            }

            const std::unique_ptr<Dog>& target = dogs[Random.index(dogs.size())];
            Dog* dogPtr = target.get();
            REQUIRE(dogPtr != nullptr);
            std::unique_ptr<Dog> takenDogUPtr = take_ownership(target, dogs);
            REQUIRE(takenDogUPtr.get() == dogPtr);
            REQUIRE(std::find(dogs.begin(), dogs.end(), takenDogUPtr) == dogs.end());
            REQUIRE(take_ownership(takenDogUPtr, dogs) == nullptr);
        }
    } // namespace Tests
} // namespace Dynamic_Static
