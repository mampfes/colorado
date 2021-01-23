#pragma once

#include <chrono>

namespace colorado
{
    // std::chrono::duration in milliseconds with 32 bits (to save memory)
    // covers +- 24.8 days
    using MilliSeconds32 = std::chrono::duration<int32_t, std::milli>;

    class TimeService
    {
    public:
        void setStartTime(MilliSeconds32 startTime) { startTime_ = startTime; }
        void setCycleTime(MilliSeconds32 cycleTime) { cycleTime_ = cycleTime; }

        MilliSeconds32 startTime() const { return startTime_; }
        MilliSeconds32 cycleTime() const { return cycleTime_; }

        void realign(MilliSeconds32 oldStartTime, MilliSeconds32 newStartTime)
        {
            MilliSeconds32 offset = (newStartTime - oldStartTime) % cycleTime_;
            startTime_ = newStartTime - offset;
        }

    private:
        MilliSeconds32 startTime_{0};
        MilliSeconds32 cycleTime_{2000};
    };
} // namespace colorado