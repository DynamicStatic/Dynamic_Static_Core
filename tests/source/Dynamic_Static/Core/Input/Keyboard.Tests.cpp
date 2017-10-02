
/*
==========================================
    Copyright (c) 2016 Dynamic_Static 
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Input.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <array>

namespace Dynamic_Static {
namespace Tests {

    TEST_CASE("Keyboard Key states work correctly", "[Input]")
    {
        static constexpr auto sKeyCount = static_cast<size_t>(Keyboard::Key::Count);
        std::array<bool, sKeyCount> previousKeyState;
        std::array<bool, sKeyCount> currentKeyState;
        Input::Manager inputManager;
        auto createRandomInput =
        [&](std::array<bool, sKeyCount>& keyStates)
        {
            for (size_t i = 0; i < sKeyCount; ++i) {
                auto keyState =
                    dst::Random.probability(0.5f) ?
                    Keyboard::State::Down :
                    Keyboard::State::Up;

                inputManager.keyboard_state()[i] = keyStates[i] = keyState;
            }

            inputManager.update();
        };

        createRandomInput(previousKeyState);
        createRandomInput(currentKeyState);

        bool success = true;
        const auto& input = inputManager.input();
        for (size_t i = 0; i < sKeyCount; ++i) {
            auto key = static_cast<Keyboard::Key>(i);
            if (key != Keyboard::Key::Unknown) {
                if (currentKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(input.keyboard().up(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().down(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Up) {
                    REQUIRE(input.keyboard().pressed(key));
                }

                if (currentKeyState[i] == Keyboard::State::Down &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().held(key));
                }

                if (currentKeyState[i] == Keyboard::State::Up &&
                    previousKeyState[i] == Keyboard::State::Down) {
                    REQUIRE(input.keyboard().released(key));
                }
            }
        }
    }

} // namespace Tests
} // namespace Dynamic_Static
