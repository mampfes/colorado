#include <algorithm>

#include "Rotator.hpp"

namespace colorado
{
    void Rotator::setup(TimeOffset startTime)
    {
        startOffset_ = startTime;
    }

    void Rotator::update(TimeOffset now)
    {
        // all calculations are done in microseconds relative to the start of the cycle
        int32_t cycleTimeUs = std::chrono::duration_cast<TimeOffset>(cycleTime_).count();
        int32_t ledCyleTimeUs = cycleTimeUs / LED_COUNT;
        int32_t beamWidthTimeUs = cycleTimeUs * beamWidth_.num / beamWidth_.denom;

        int32_t beamStartTimeUs = std::chrono::duration_cast<TimeOffset>(now - startOffset_).count() % cycleTimeUs;
        int32_t beamEndTimeUs = (beamStartTimeUs + beamWidthTimeUs) % cycleTimeUs;

        for (int i = 0; i < LED_COUNT; i++)
        {
            int32_t ledStartTimeUs = cycleTimeUs * i / LED_COUNT;
            int32_t ledEndTimeUs = ledStartTimeUs + ledCyleTimeUs;

            int32_t startTimeUs = 0, endTimeUs = 0;
            if (beamStartTimeUs <= beamEndTimeUs)
            {
                if (beamStartTimeUs < ledEndTimeUs && beamEndTimeUs > ledStartTimeUs)
                {
                    // led is within beam area
                    startTimeUs = std::max(beamStartTimeUs, ledStartTimeUs);
                    endTimeUs = std::min(beamEndTimeUs, ledEndTimeUs);
                }
            }
            else
            {
                // overlapping area -> everything is inverted
                if (beamEndTimeUs > ledStartTimeUs)
                {
                    // range from 0 to beamEndTime
                    startTimeUs = ledStartTimeUs;
                    endTimeUs = std::min(beamEndTimeUs, ledEndTimeUs);
                }
                else if (beamStartTimeUs < ledEndTimeUs)
                {
                    // range from beamStartTime to cycleTime (= end of led range)
                    startTimeUs = std::max(beamStartTimeUs, ledStartTimeUs);
                    endTimeUs = ledEndTimeUs;
                }
            }

            int32_t ledOnTimeUs = endTimeUs - startTimeUs;

            CHSV hsv = colorService_->getColor(now);
            hsv.v = hsv.v * ledOnTimeUs / ledCyleTimeUs; // set brightness
            pixel_[i] = hsv;
        }
    } // namespace colorado

} // namespace colorado