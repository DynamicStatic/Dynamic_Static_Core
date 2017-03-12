
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

namespace Dynamic_Static {
    namespace Tests {
        class Activator final
            : public MoveNotifier<Activator> {
        };

        class Listener final {
        private:
            bool mEventRaised { false };
            Delegate<Activator&> mDelegate;

        public:
            Listener(Activator& activator)
            {
                using namespace std::placeholders;
                mDelegate = std::bind(&Listener::on_activator_moved, this, _1);
                activator.OnMoved += mDelegate;
            }

        public:
            bool event_raised() const { return mEventRaised; }

        private:
            void on_activator_moved(const Activator&)
            {
                mEventRaised = true;
            }
        };

        TEST_CASE("MoveNotifier raises Event on move", "[MoveNotifier]")
        {
            Activator activator;
            Listener listener(activator);
            auto move_to = std::move(activator);
            REQUIRE(listener.event_raised());
        }
    } // namespace Tests
} // namespace Dynamic_Static
