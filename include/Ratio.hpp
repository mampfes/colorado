#pragma once

#include <cstdint>

namespace colorado
{

template <typename T>
struct Ratio
{
    constexpr Ratio(T numArg, T denomArg) :
    num{numArg},
    denom{denomArg}
    {}

    constexpr Ratio() :
    num{0},
    denom{1}
    {}

    T num;
    T denom;
};

using LedIndex = Ratio<uint16_t>;
using HueRatio = Ratio<uint8_t>;

}