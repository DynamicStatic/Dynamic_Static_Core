
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

#include "Dynamic_Static/Core/MoveNotifier.hpp"
#include "Dynamic_Static/Core/MoveableHandle.hpp"

namespace Dynamic_Static {
    namespace Tests {
        class Dependency final
            : public MoveNotifier<Dependency> {
        };

        class Obj final {
        private:
            MoveableHandle<Dependency> m_dependency;

        public:
            Obj() = default;
            Obj(Dependency& dependency)
                : m_dependency { &dependency }
            {
            }

        public:
            const Dependency& dependency() const { return *m_dependency; }
        };

        TEST_CASE("MoveableHandle maintains handle when target moves", "[MoveableHandle]")
        {
            Obj obj;
            Dependency move_to;
            Dependency* move_to_address = nullptr;

            {
                Dependency dependency;
                obj = Obj(dependency);
                Dependency* move_from_address = &dependency;
                REQUIRE(&obj.dependency() == move_from_address);
                move_to = std::move(dependency);
                move_to_address = &move_to;
                REQUIRE(move_to_address != move_from_address);
            }

            REQUIRE(&obj.dependency() == move_to_address);
        }

        TEST_CASE("MoveableHandle maintains handle when it moves", "[MoveableHandle]")
        {
            Obj move_to;
            Dependency dependency;

            {
                Obj obj(dependency);
                move_to = std::move(obj);
            }

            REQUIRE(&move_to.dependency() == &dependency);
        }

        TEST_CASE("MoveableHandle maintains handle when it and target move", "[MoveableHandle]")
        {
            Obj obj_move_to;
            Dependency dependency_move_to;

            {
                Dependency dependency;
                Obj obj(dependency);
                obj_move_to = std::move(obj);
                dependency_move_to = std::move(dependency);
            }

            REQUIRE(&obj_move_to.dependency() == &dependency_move_to);
        }
    }
}
