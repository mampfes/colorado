#pragma once

#include <chrono>
#include "Pixel.hpp"

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

class LinearGlider
{
  public:
  LinearGlider();

  void setup();
  void update();

  const RGBPixel& get(unsigned index) const { return pixel_[index]; }

  private:
  static const int LED_COUNT = 16;


  RGBPixel pixel_[LED_COUNT];
  
  // settings
  Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
  std::chrono::milliseconds cycleTime_{std::chrono::milliseconds{1000}};

  // variables
  std::chrono::steady_clock::time_point startTime_;
};