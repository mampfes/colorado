#pragma once

#include <cstdint>

namespace colorado
{
    class Statistics
    {
    public:
        void tick(uint32_t now);

    private:
        uint32_t lastPrintTime_ = 0;
        uint32_t counter_ = 0;
        char buffer_[40];
    };
} // namespace colorado