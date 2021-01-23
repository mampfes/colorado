#pragma once

#include "color/ColorService.hpp"

namespace colorado
{
    namespace color
    {
        class RainbowColorService : public IColorService
        {
        public:
            RainbowColorService(const CHSV& startColor, MilliSeconds32 cycleTime) :
                startColor_{startColor},
                cycleTime_{cycleTime}
            {
            }

            void setup(MilliSeconds32 startTime)
            {
                startTime_ = startTime;
            }

            CHSV getColor(MilliSeconds32 now, LedIndex /*ledIndex*/) const override
            {
                CHSV color{startColor_};
                color.hue = startColor_.hue + 256 * (now - startTime_) / cycleTime_;
                return color;
            }

        private:
            CHSV startColor_;
            MilliSeconds32 startTime_{0};
            MilliSeconds32 cycleTime_{std::chrono::milliseconds{2000}};
        };
    } // namespace color
} // namespace colorado