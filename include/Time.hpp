#pragma once

#include <chrono>

namespace colorado
{
    // std::chrono::duration in milliseconds with 32 bits (to save memory)
    // covers +- 24.8 days
    using MilliSeconds32 = std::chrono::duration<int32_t, std::milli>;
}