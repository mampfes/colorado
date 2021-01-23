#pragma once

#include "ColorService.hpp"
#include "Pixel.hpp"
#include "Ratio.hpp"
#include "Time.hpp"
#include <chrono>

namespace colorado
{
    class Rotator
    {
    public:
        Rotator(IColorService& colorService) :
            colorService_{&colorService}
        {
        }

        void setup(MilliSeconds32 startTime);
        void update(MilliSeconds32 now);

        const RGBPixel& get(unsigned index) const { return pixel_[index]; }

    private:
        static const int LED_COUNT = 16;

        RGBPixel pixel_[LED_COUNT];

        // settings
        Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
        MilliSeconds32 cycleTime_{std::chrono::milliseconds{2000}};

        // variables
        IColorService* colorService_{nullptr};
        MilliSeconds32 startTime_{0};
    };

} // namespace colorado