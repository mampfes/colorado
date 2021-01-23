#pragma once

#include "Pixel.hpp"
#include "Time.hpp"

namespace colorado
{
    namespace effect
    {
        class IEffect
        {
        public:
            virtual void update(MilliSeconds32 timeOffset, HSVPixelArray& pixels) = 0;
        };

    } // namespace effect
} // namespace colorado