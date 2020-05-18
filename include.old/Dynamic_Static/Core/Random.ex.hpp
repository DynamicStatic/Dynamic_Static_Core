#if 0
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <limits>
#include <random>
#include <type_traits>

namespace dst {

    /*!
    Provides high level control over random number generation.
    */
    class RandomNumberGenerator final
    {
    private:
        uint32_t mSeed { 0 };
        std::mt19937_64 mEngine;
        std::uniform_real_distribution<double> mRealDistribution { 0., 1. };
        std::uniform_int_distribution<uint64_t> mIntDistribution { 0, std::numeric_limits<uint64_t>::max() };

    public:
        /*!
        Constructs a new instance of RandomNumberGenerator.
        */
        inline RandomNumberGenerator()
            : RandomNumberGenerator(std::random_device()())
        {
        }

        /*!
        Constructs a new instance of RandomNumberGenerator with a given seed.
        @param [in] seed This RandomNumberGenerator's seed
        */
        inline RandomNumberGenerator(uint32_t seed)
        {
            set_seed(seed);
        }

    public:
        /*!
        Gets this RandomNumberGenerator's seed.
        @return This RandomNumberGenerator's seed
        */
        inline uint32_t get_seed() const
        {
            return mSeed;
        }

        /*!
        Sets this RandomNumberGenerator's seed.
        \n NOTE : Calling this method will reset this RandomNumberGenerator
        @param [in] This RandomNumberGenerator's seed
        */
        inline void set_seed(uint32_t seed)
        {
            mSeed = seed;
            reset();
        }

        /*!
        Resets this RandomNumberGenerator.
        */
        inline void reset()
        {
            mEngine.seed(mSeed);
            mRealDistribution.reset();
            mIntDistribution.reset();
        }

        /*!
        Generates a random in the range of two given values.
        @param <IntegerType> The type of the value
        @param [in] min The lower bound of the range [inclusive]
        @param [in] max The upper bound of the range (exclusive)
        @return The generated value
        */
        template <typename IntegerType>
        typename std::enable_if<std::is_integral<IntegerType>::value, IntegerType>::type
        inline range(IntegerType min, IntegerType max)
        {
            // TODO : Make max [inclusive]
            return static_cast<IntegerType>(mIntDistribution(mEngine) % (max - min) + min);
        }

        /*!
        Generates a random value in the range of two given values.
        @param <IntegerType> The type of the value
        @param [in] min The lower bound of the range [inclusive]
        @param [in] max The upper bound of the range (exclusive)
        @return The generated value
        */
        template <typename FloatingPointType>
        typename std::enable_if<std::is_floating_point<FloatingPointType>::value, FloatingPointType>::type
        inline range(FloatingPointType min, FloatingPointType max)
        {
            // TODO : Make max [inclusive]
            return static_cast<FloatingPointType>(mRealDistribution(mEngine) * (max - min) + min);
        }

        /*!
        Generates a random value in a given type's range.
        @param <T> The type of the value
        @return The generated value
        */
        template <typename T>
        inline T value()
        {
            return range<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        }

        /*!
        Has a chance of returning true based on a given value.
        @param [in] value The value (0 - 100] to test
        @return Whether or not the value passed
        */
        template <typename IntegerType>
        inline bool probability(
            IntegerType value,
            typename std::enable_if<std::is_integral<IntegerType>::value, IntegerType>::type* = nullptr
        )
        {
            return value >= range<IntegerType>(1, 101);
        }

        /*!
        Has a chance of returning true based on a given value.
        @param [in] value The floating point value (0 - 1] to test
        @return Whether or not the value passed
        */
        template <typename FloatingPointType>
        inline bool probability(
            FloatingPointType value,
            typename std::enable_if<std::is_floating_point<FloatingPointType>::value, FloatingPointType>::type* = nullptr
        )
        {
            return value >= range<FloatingPointType>(std::numeric_limits<FloatingPointType>::epsilon(), 1.);
        }

        /*!
        Generates a random index for a collection with a given count.
        @param [in] count The number of elements in the collection
        @return The generated index
        */
        template <typename IntegerType>
        inline IntegerType index(IntegerType count)
        {
            static_assert(
                std::is_integral<IntegerType>::value,
                "dst::RandomNumberGenerator::index() can only be used with integer types"
            );
            return count ? range<IntegerType>(0, count) : 0;
        }

        /*!
        Generates a roll from a die with a given number of sides.
        @param [in] D The number of sides on the die
        @return The result of the die roll
        */
        template <typename IntegerType>
        inline IntegerType die_roll(IntegerType D)
        {
            static_assert(
                std::is_integral<IntegerType>::value,
                "dst::RandomNumberGenerator::die_roll() can only be used with integer types"
            );
            return D >= 1 ? range<IntegerType>(1, D + 1) : 0;
        }
    };

} // namespace dst
#endif