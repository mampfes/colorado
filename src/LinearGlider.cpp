#include <algorithm>

#include "LinearGlider.hpp"

LinearGlider::LinearGlider()
{}

void LinearGlider::setup()
{
    startTime_ = std::chrono::steady_clock::now();
}

void LinearGlider::update()
{
    auto now = std::chrono::steady_clock::now();

    // all calculations are done in microseconds relative to the start of the cycle
    int32_t cycleTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(cycleTime_).count();
    int32_t ledCyleTimeUs = cycleTimeUs / LED_COUNT;

    int32_t beamWidthTimeUs = cycleTimeUs * beamWidth_.num / beamWidth_.denom;
    auto qr = std::div(std::chrono::duration_cast<std::chrono::microseconds>(now - startTime_).count(), (cycleTimeUs-beamWidthTimeUs));
    int32_t beamStartTimeUs = (qr.quot & 1) ? qr.rem : (cycleTimeUs-beamWidthTimeUs-qr.rem);
    int32_t beamEndTimeUs = beamStartTimeUs + cycleTimeUs * beamWidth_.num / beamWidth_.denom;

    //serial.println
    for (int i = 0; i < LED_COUNT; i++)
    {
        int32_t ledStartTimeUs = cycleTimeUs * i / LED_COUNT;
        int32_t ledEndTimeUs = ledStartTimeUs + ledCyleTimeUs;

        if (beamStartTimeUs < ledEndTimeUs && beamEndTimeUs > ledStartTimeUs)
        {
            // beam is within LED area
            int32_t startTimeUs = std::max(beamStartTimeUs, ledStartTimeUs);
            int32_t endTimeUs = std::min(beamEndTimeUs, ledEndTimeUs);

            int32_t ledOnTimeUs = endTimeUs - startTimeUs;

            pixel_[i].r = 255 * ledOnTimeUs / ledCyleTimeUs;
            pixel_[i].g = 0;
            pixel_[i].b = 0;
        }
        else
        {
            pixel_[i].r = 0;
            pixel_[i].g = 0;
            pixel_[i].b = 0;
        }
        
    }
}
