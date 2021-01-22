#pragma once

#include "Ratio.hpp"
#include "Time.hpp"

#include "hsv2rgb.h"

namespace colorado
{
    class IColorService
    {
    public:
        virtual CHSV getColor(TimeOffset timeOffset, LedIndex ledIndex) const = 0;
        CHSV getColor(TimeOffset timeOffset) const
        {
            return getColor(timeOffset, LedIndex{1, 1});
        }
    };

    class FixColorService : public IColorService
    {
    public:
        FixColorService(const CHSV& hsv) :
            hsv_{hsv}
        {
        }

        CHSV getColor(TimeOffset /*timeOffset*/, LedIndex /*ledIndex*/) const override
        {
            return hsv_;
        }

    private:
        CHSV hsv_;
    };

    class RainbowColorService : public IColorService
    {
    public:
        RainbowColorService(const CHSV& startColor, TimeOffset cycleTime) :
            startColor_{startColor},
            cycleTime_{cycleTime}
        {
        }

        void setup(TimeOffset startTime)
        {
            startTime_ = startTime;
        }

        CHSV getColor(TimeOffset now, LedIndex /*ledIndex*/) const override
        {
            CHSV color{startColor_};
            color.hue = startColor_.hue + 256 * std::chrono::duration_cast<TimeOffset>(now - startTime_).count() / cycleTime_.count();
            return color;
        }

    private:
        CHSV startColor_;
        TimeOffset startTime_;
        TimeOffset cycleTime_{std::chrono::milliseconds{1000}};
    };

} // namespace colorado