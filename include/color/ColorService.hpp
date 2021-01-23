#pragma once

#include "Ratio.hpp"
#include "Time.hpp"

#include "hsv2rgb.h"

namespace colorado
{
    namespace color
    {
        class IColorService
        {
        public:
            virtual CHSV getColor(MilliSeconds32 now, LedIndex ledIndex) const = 0;

            // convenient function if LED position doesn't care
            CHSV getColor(MilliSeconds32 now) const
            {
                return getColor(now, LedIndex{1, 1});
            }
        };

    } // namespace color
} // namespace colorado
