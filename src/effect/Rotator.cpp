#include <algorithm>

#include "effect/Rotator.hpp"

namespace colorado
{
    namespace effect
    {
        void Rotator::update(MilliSeconds32 now)
        {
            MilliSeconds32 ledCyleTime = cycleTime() / LED_COUNT;
            MilliSeconds32 beamWidthDuration = cycleTime() * beamWidth_.num / beamWidth_.denom;

            MilliSeconds32 beamStartTime = (now - startTime()) % cycleTime();
            MilliSeconds32 beamEndTime = (beamStartTime + beamWidthDuration) % cycleTime();

            for (int i = 0; i < LED_COUNT; i++)
            {
                MilliSeconds32 ledStartTime = cycleTime() * i / LED_COUNT;
                MilliSeconds32 ledEndTime = ledStartTime + ledCyleTime;

                MilliSeconds32 startTime{0}, endTime{0};
                if (beamStartTime <= beamEndTime)
                {
                    if (beamStartTime < ledEndTime && beamEndTime > ledStartTime)
                    {
                        // led is within beam area
                        startTime = std::max(beamStartTime, ledStartTime);
                        endTime = std::min(beamEndTime, ledEndTime);
                    }
                }
                else
                {
                    // overlapping area -> beamEndTime is smaller than beamStartTime
                    if (beamEndTime > ledStartTime)
                    {
                        // range from 0 to beamEndTime (which is smaller than beamStartTime)
                        startTime = ledStartTime;
                        endTime = std::min(beamEndTime, ledEndTime);
                    }
                    else if (beamStartTime < ledEndTime)
                    {
                        // range from beamStartTime to cycleTime (= end of led range)
                        startTime = std::max(beamStartTime, ledStartTime);
                        endTime = ledEndTime;
                    }
                }

                MilliSeconds32 ledOnTime = endTime - startTime;

                CHSV hsv = colorService_->getColor(now);
                hsv.v = hsv.v * ledOnTime / ledCyleTime; // set brightness
                pixel_[i] = hsv;
            }
        }
    } // namespace effect
} // namespace colorado