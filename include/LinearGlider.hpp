#pragma once

#include "ColorService.hpp"
#include "Pixel.hpp"
#include "Ratio.hpp"
#include "Time.hpp"
#include <chrono>

namespace colorado
{
    class LinearGlider
    {
    public:
        LinearGlider(IColorService& colorService) :
            colorService_{&colorService}
        {
        }

        void setup(TimeOffset startOffset);
        void update(TimeOffset now);

        const RGBPixel& get(unsigned index) const { return pixel_[index]; }

    private:
        static const int LED_COUNT = 16;

        RGBPixel pixel_[LED_COUNT];

        // settings
        Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
        TimeOffset cycleTime_{std::chrono::milliseconds{1000}};

        // variables
        IColorService* colorService_;
        TimeOffset startOffset_;
    };

} // namespace colorado