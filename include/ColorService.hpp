#pragma once

#include "Ratio.hpp"
#include "Time.hpp"

#include "hsv2rgb.h"

namespace colorado
{
    class IColorService
    {
    public:
        virtual CHSV getColor(MilliSeconds32 now, LedIndex ledIndex) const = 0;

        // convenient function if LED position doesn't care
        CHSV getColor(MilliSeconds32 now) const
        {
            return getColor(now, LedIndex{1, 1});
        }
    };

    class FixColorService : public IColorService
    {
    public:
        FixColorService(const CHSV& hsv) :
            hsv_{hsv}
        {
        }

        CHSV getColor(MilliSeconds32 /*now*/, LedIndex /*ledIndex*/) const override
        {
            return hsv_;
        }

    private:
        CHSV hsv_;
    };

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

} // namespace colorado