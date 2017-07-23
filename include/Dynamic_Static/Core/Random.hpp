
/*
================================================================================

  MIT License

  Copyright (c) 2016 Dynamic_Static

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

================================================================================
*/

#pragma once

#include "Dynamic_Static/Core/Algorithm.hpp"
#include "Dynamic_Static/Core/Defines.hpp"

#include <algorithm>
#include <limits>
#include <random>

namespace Dynamic_Static {

    /**
     * Provides high level control over random number generation.
     */
    class RandomNumberGenerator final
    {
    private:
        // TODO : Provide support for std::seed_seq.
        uint32_t mSeed;
        std::mt19937_64 mEngine;
        std::uniform_real_distribution<double> mRealDistribution { 0, 1 };
        std::uniform_int_distribution<uint64_t> mIntDistribution { 0 , std::numeric_limits<uint64_t>::max() };

    public:
        /**
         * Constructs an instance of RandomNumberGenerator.
         */
        inline RandomNumberGenerator()
            : RandomNumberGenerator(std::random_device()())
        {
        }

        /**
         * Constructs an instance of RandomNumberGenerator with a given seed.
         * @param [in] seed This RandomNumberGenerator's seed
         */
        inline RandomNumberGenerator(uint32_t seed)
        {
            this->seed(seed);
        }

    public:
        /**
         * Gets this RandomNumberGenerator's seed.
         * @return This RandomNumberGenerator's seed
         */
        inline uint32_t seed() const
        {
            return mSeed;
        }

        /**
         * Sets this RandomNumberGenerator's seed.
         * \n NOTE : Calling this method will reset this RandomNumberGenerator.
         * @param [in] seed This RandomNumberGenerator's seed 
         */
        inline void seed(uint32_t seed)
        {
            mSeed = seed;
            reset();
        }

        /**
         * Resets this RandomNumberGenerator.
         */
        inline void reset()
        {
            mEngine.seed(mSeed);
            mRealDistribution.reset();
            mIntDistribution.reset();
        }

        /**
         * Gets a random integral value in the range of two specified values.
         * @param <T>         The integral type of the value
         * @param [in] value0 The first value [inclusive]
         * @param [in] value1 The second value [inclusive]
         * @return The random integral value generated
         */
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, T>::type
            range(T value0, T value1)
        {
            auto values = std::minmax(value0, value1);
            T min = values.first;
            T max = values.second + 1;
            return static_cast<T>(
                mIntDistribution(mEngine) % (max - min) + min
            );
        }

        /**
         * Gets a random floating point value in the range of two specified values.
         * @param <T>         The floating point type of the value
         * @param [in] value0 The first value [inclusive]
         * @param [in] value1 The second value [inclusive]
         * @return The random floating point value generated
         */
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value, T>::type
            range(T value0, T value1)
        {
            auto values = std::minmax(value0, value1);
            T min = values.first;
            T max = values.second;
            return static_cast<T>(
                mRealDistribution(mEngine) * (max - min) + min
            );
        }

        /**
         * Has a chance of returning true based on a given value.
         * @param [in] value The integral value [0-100] to test
         * @return Whether or not the value passed
         */
        template <typename T>
        inline typename std::enable_if<std::is_integral<T>::value, T>::type
            probability(T value)
        {
            return value >= range<T>(0, 100);
        }

        /**
         * Has a chance of returning true based on a given value.
         * @param [in] value The floating point value [0 - 1] to test
         * @return Whether or not the value passed
         */
        template <typename T>
        inline typename std::enable_if<std::is_floating_point<T>::value, T>::type
            probability(T value)
        {
            return value >= range<T>(0, 1);
        }

        /**
         * Gets a random value in a specified type's range.
         * @param <T> The type of the value
         * @return The random value generated
         */
        template <typename T>
        inline T value()
        {
            // HACK : We subtract 1 from max because our integral version of range()
            //        adds 1 to the max and we don't want to overflow.  We need to
            //        have a uniform distribution for each type and select the proper
            //        distribution based on the template parameter.
            return range<T>(
                std::numeric_limits<T>::min(),
                std::numeric_limits<T>::max() - 1
            );
        }

        /**
         * Gets a random index for a collection with a given count.
         * @param [in] count The number of elements in the collection
         * @return The index generated
         */
        inline size_t index(size_t count)
        {
            return count ? range<size_t>(0, count - 1) : 0;
        }

        /**
         * Gets a roll from a die with a given number of sides.
         * @param [in] D The number of sides on the die
         * @return The result of the die roll
         */
        inline uint32_t die_roll(uint32_t D)
        {
            return D >= 1 ? range<uint32_t>(1, D) : 0;
        }
    };

} // namespace Dynamic_Static

namespace Dynamic_Static {

    /**
     * Provides high level control over random number generation.
     */
    static RandomNumberGenerator Random;

} // namespace Dynamic_Static
