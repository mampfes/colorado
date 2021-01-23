#pragma once

#include "color/ColorService.hpp"

namespace colorado
{
    namespace color
    {
        class RainbowColorService : public IColorService, public TimeService
        {
        public:
            RainbowColorService(const CHSV& startColor) :
                startColor_{startColor}
            {
            }

            CHSV getColor(MilliSeconds32 now, LedIndex /*ledIndex*/) const override
            {
                CHSV color{startColor_};
                color.hue = startColor_.hue + 256 * (now - startTime()) / cycleTime();
                return color;
            }

        private:
            CHSV startColor_;
        };
    } // namespace color
} // namespace colorado