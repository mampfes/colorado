#pragma once

#include "Pixel.hpp"
#include "Ratio.hpp"
#include "Time.hpp"
#include "color/ColorService.hpp"
#include <chrono>

namespace colorado
{
    namespace effect
    {
        class BidirectionalGlider
        {
        public:
            BidirectionalGlider(color::IColorService& colorService) :
                colorService_{&colorService}
            {
            }

            void setup(MilliSeconds32 startOffset);
            void update(MilliSeconds32 now);

            const RGBPixel& get(unsigned index) const { return pixel_[index]; }

        private:
            static const int LED_COUNT = 16;

            RGBPixel pixel_[LED_COUNT];

            // settings
            Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
            MilliSeconds32 cycleTime_{std::chrono::milliseconds{2000}};

            // variables
            color::IColorService* colorService_;
            MilliSeconds32 startOffset_;
        };
    } // namespace effect
} // namespace colorado