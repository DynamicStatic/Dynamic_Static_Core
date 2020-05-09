
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <limits>
#include <random>
#include <type_traits>

namespace dst {

/**
Provides high level control over random number generation
*/
template <typename EngineType = std::mt19937>
class RandomNumberGenerator final
{
public:
    /**
    Constructs an instance of RandomNumberGenerator<>
    */
    inline RandomNumberGenerator()
        : RandomNumberGenerator(std::random_device()())
    {
    }

    /**
    Constructs an instance of RandomNumberGenerator<>
    TODO : Documentation
    */
    inline RandomNumberGenerator(uint32_t seed)
    {
        set_seed(seed);
    }

    /**
    TODO : Documentation
    */
    inline uint32_t get_seed() const
    {
        return mSeed;
    }

    /**
    TODO : Documentation
    */
    inline void set_seed(uint32_t seed)
    {
        mSeed = seed;
        reset();
    }

    /**
    TODO : Documentation
    */
    inline void reset()
    {
        mEngine.seed(mSeed);
        mRealDistribution.reset();
        mIntDistribution.reset();
    }

    /**
    TODO : Documentation
    */
    template <typename T>
    inline typename std::enable_if<std::is_integral<T>::value, T>::type range(T min = 0, T max = 1)
    {
        return static_cast<T>(mIntDistribution(mEngine) % (max - min) + min);
    }

    /**
    TODO : Documentation
    */
    template <typename T>
    inline typename std::enable_if<std::is_floating_point<T>::value, T>::type range(T min = 0, T max = 1)
    {
        return static_cast<T>(mRealDistribution(mEngine) * static_cast<double>((max - min) + min));
    }

    /**
    TODO : Documentation
    */
    template <typename FloatingPointType>
    inline bool probability(
        FloatingPointType value,
        typename std::enable_if<std::is_floating_point<FloatingPointType>::value, FloatingPointType>::type* = nullptr
    )
    {
        return value >= range<FloatingPointType>(std::numeric_limits<FloatingPointType>::epsilon(), static_cast<FloatingPointType>(1.0) );
    }

    /**
    TODO : Documentation
    */
    template <typename T>
    inline T value()
    {
        return range<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    /**
    TODO : Documentation
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

private:
    uint32_t mSeed { };
    EngineType mEngine;
    std::uniform_real_distribution<double> mRealDistribution { 0.0, 1.0 };
    std::uniform_int_distribution<uint64_t> mIntDistribution { 0, std::numeric_limits<uint64_t>::max() };
};

} // namespace dst
