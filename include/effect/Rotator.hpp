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
        class Rotator : public TimeService
        {
        public:
            Rotator(color::IColorService& colorService) :
                colorService_{&colorService}
            {
            }

            void update(MilliSeconds32 now);

            const RGBPixel& get(unsigned index) const { return pixel_[index]; }

        private:
            static const int LED_COUNT = 16;

            RGBPixel pixel_[LED_COUNT];

            color::IColorService* colorService_{nullptr};
            Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
        };
    } // namespace effect
} // namespace colorado