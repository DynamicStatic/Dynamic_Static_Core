
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

    TEST_CASE("Mouse Button states work correctly", "[Input]")
    {
        static constexpr auto sButtonCount = static_cast<size_t>(Mouse::Button::Count);
        std::array<bool, sButtonCount> previousButtonState;
        std::array<bool, sButtonCount> currentButtonState;
        Input::Manager inputManager;
        auto createRandomInput =
        [&](std::array<bool, sButtonCount>& buttonStates)
        {
            for (size_t i = 0; i < sButtonCount; ++i) {
                auto buttonState =
                    dst::Random.probability(0.5f) ?
                    Mouse::State::Down :
                    Mouse::State::Up;

                inputManager.mouse_state()[i] = buttonStates[i] = buttonState;
            }

            inputManager.update();
        };

        createRandomInput(previousButtonState);
        createRandomInput(currentButtonState);

        bool success = true;
        const auto& input = inputManager.input();
        for (size_t i = 0; i < sButtonCount; ++i) {
            auto button = static_cast<Mouse::Button>(i);
            if (button != Mouse::Button::Unknown) {
                if (currentButtonState[i] == Mouse::State::Up) {
                    REQUIRE(input.mouse().up(button));
                }

                if (currentButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().down(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Up) {
                    REQUIRE(input.mouse().pressed(button));
                }

                if (currentButtonState[i] == Mouse::State::Down &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().held(button));
                }

                if (currentButtonState[i] == Mouse::State::Up &&
                    previousButtonState[i] == Mouse::State::Down) {
                    REQUIRE(input.mouse().released(button));
                }
            }
        }
    }

} // namespace Tests
} // namespace Dynamic_Static
