#include <algorithm>

#include "effect/BidirectionalGlider.hpp"

namespace colorado
{
    namespace effect
    {
        void BidirectionalGlider::update(MilliSeconds32 now, HSVPixelArray& pixels)
        {
            MilliSeconds32 halfcycleTime = cycleTime() / 2;
            MilliSeconds32 ledCyleTime = halfcycleTime / pixels.size();
            MilliSeconds32 beamWidthDuration = halfcycleTime * beamWidth_.num / beamWidth_.denom;

            auto qr = std::div((now - startTime()).count(), (halfcycleTime - beamWidthDuration).count());
            MilliSeconds32 beamStartTime = (qr.quot & 1) ? MilliSeconds32{qr.rem} : (halfcycleTime - beamWidthDuration - MilliSeconds32{qr.rem});
            MilliSeconds32 beamEndTime = beamStartTime + beamWidthDuration;

            for (unsigned i = 0; i < pixels.size(); i++)
            {
                MilliSeconds32 ledStartTimeUs = halfcycleTime * i / pixels.size();
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
                pixels[i] = hsv;
            }
        }
    } // namespace effect
} // namespace colorado