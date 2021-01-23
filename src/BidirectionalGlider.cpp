#include <algorithm>

#include "BidirectionalGlider.hpp"

namespace colorado
{
    void BidirectionalGlider::setup(MilliSeconds32 startTime)
    {
        startOffset_ = startTime;
    }

    void BidirectionalGlider::update(MilliSeconds32 now)
    {
        MilliSeconds32 cycleTime = cycleTime_ / 2;
        MilliSeconds32 ledCyleTime = cycleTime / LED_COUNT;
        MilliSeconds32 beamWidthDuration = cycleTime * beamWidth_.num / beamWidth_.denom;

        auto qr = std::div((now - startOffset_).count(), (cycleTime - beamWidthDuration).count());
        MilliSeconds32 beamStartTime = (qr.quot & 1) ? MilliSeconds32{qr.rem} : (cycleTime - beamWidthDuration - MilliSeconds32{qr.rem});
        MilliSeconds32 beamEndTime = beamStartTime + beamWidthDuration;

        for (int i = 0; i < LED_COUNT; i++)
        {
            MilliSeconds32 ledStartTimeUs = cycleTime * i / LED_COUNT;
            MilliSeconds32 ledEndTime = ledStartTimeUs + ledCyleTime;

            MilliSeconds32 startTime{0}, endTime{0};
            if (beamStartTime < ledEndTime && beamEndTime > ledStartTimeUs)
            {
                // beam is within LED area
                startTime = std::max(beamStartTime, ledStartTimeUs);
                endTime = std::min(beamEndTime, ledEndTime);
            }

            MilliSeconds32 ledOnTime = endTime - startTime;

            CHSV hsv = colorService_->getColor(now);
            hsv.v = 255 * ledOnTime / ledCyleTime; // set brightness
            pixel_[i] = hsv;
        }
    }

} // namespace colorado