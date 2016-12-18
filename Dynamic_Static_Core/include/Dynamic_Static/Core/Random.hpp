
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

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <random>
#include <limits>
#include <algorithm>

namespace Dynamic_Static {
    /**
     * Provides high level control over random number generation.
     */
    class RandomNumberGenerator final {
    private:
        // TODO : Provide support for std::seed_seq.
        uint32_t m_seed;
        std::mt19937_64 m_engine;
        std::uniform_real_distribution<double> m_real_distribution { 0, 1.0 };
        std::uniform_int_distribution<uint64_t> m_int_distribution { 0, std::numeric_limits<uint64_t>::max() };

    public:
        /**
         * Constructs an instance of RandomNumberGenerator with a device based seed.
         */
        RandomNumberGenerator()
            : RandomNumberGenerator(std::random_device()())
        {
        }

        /**
         * Constructs an instance of RandomNumberGenerator with a specified seed.
         * @param [in] seed The seed to supply to this RandomNumberGenerator's random number engine
         */
        RandomNumberGenerator(uint32_t seed)
        {
            this->seed(seed);
        }

    public:
        /**
         * Gets this RandomNumberGenerator's seed.
         */
        uint32_t seed() const
        {
            return m_seed;
        }

        /**
         * Sets this RandomNumberGenerator's seed.
         * \n NOTE : Calling this method will reset this RandomNumberGenerator's random number engine
         */
        void seed(uint32_t seed)
        {
            m_seed = seed;
            m_engine.seed(m_seed);
            m_real_distribution.reset();
            m_int_distribution.reset();
        }

        /**
         * Gets an integral value in the range of two specified values.
         * @param [in] value_0 The first value [inclusive]
         * @param [in] value_1 The second value [inclusive]
         * @return The random integral value generated
         */
        template <typename T>
        T range(T value_0, T value_1)
        {
            auto values = std::minmax(value_0, value_1);
            T min = values.first;
            T max = values.second + 1;
            return m_int_distribution(m_engine) % (max - min) + min;
        }

        /**
         * Gets a double value in the range of two specified values.
         * @param [in] value_0 The first value [inclusive]
         * @param [in] value_1 The second value [inclusive]
         * @return The random double value generated
         */
        template <>
        double range<double>(double value_0, double value_1)
        {
            auto values = std::minmax(value_0, value_1);
            double min = values.first;
            double max = values.second;
            return m_real_distribution(m_engine) * (max - min) + min;
        }

        /**
         * Gets a float value in the range of two specified values.
         * @param [in] value_0 The first value [inclusive]
         * @param [in] value_1 The second value [inclusive]
         * @return The random float value generated
         */
        template <>
        float range<float>(float value_0, float value_1)
        {
            return static_cast<float>(range<double>(value_0, value_1));
        }

        /**
         * Has a chance [0 - 100] of returning true based on a specified value.
         * @param [in] value The integral value [0-100] to test
         * @return Whether or not the value passed
         */
        template <typename T>
        bool probability(T value)
        {
            return value >= range<T>(0, 100, true);
        }

        /**
         * Has a chance [0 - 1] of returning true based on a specified value.
         * @param [in] value The double value [0 - 1] to test
         * @return Whether or not the value passed
         */
        template <>
        bool probability<double>(double value)
        {
            return value >= range<double>(0, 1);
        }

        /**
         * Has a chance [0 - 1] of returning true based on a specified value.
         * @param [in] value The float value [0 - 1] to test
         * @return Whether or not the value passed
         */
        template <>
        bool probability<float>(float value)
        {
            return value >= range<float>(0, 1);
        }

        /**
         * Gets a random index for a collection with a specified count.
         * @param [in] count The number of elements in the collection
         * @return The index generated
         */
        size_t index(size_t count)
        {
            return count ? range<size_t>(0, count - 1) : 0;
        }

        /**
         * Gets a roll from a die with a specified number of sides.
         * @param [in] D The number of sides on the die
         * @return The result of the die roll
         */
        uint32_t die_roll(uint32_t D)
        {
            return D >= 1 ? range<uint32_t>(1, D) : 0;
        }

        /**
         * Resets this RandomNumberGenerator's random engine with the current seed.
         */
        void reset()
        {
            seed(m_seed);
        }
    };
}

namespace Dynamic_Static {
    /**
     * TODO : Documentation.
     */
    static RandomNumberGenerator Random;
}
