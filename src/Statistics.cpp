#include "Statistics.hpp"

#include <Arduino.h>

void colorado::Statistics::tick(uint32_t now)
{
    counter_++;

    if (now - lastPrintTime_ > 1000)
    {
        lastPrintTime_ += 1000;
        snprintf(buffer_, sizeof(buffer_), "updates per seconds: %u", counter_);
        Serial.println(buffer_);
        counter_ = 0;
    }
}