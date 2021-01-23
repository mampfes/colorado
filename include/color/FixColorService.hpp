#pragma once

#include "color/ColorService.hpp"

namespace colorado
{
    namespace color
    {
        class FixColorService : public IColorService
        {
        public:
            FixColorService(const CHSV& hsv) :
                hsv_{hsv}
            {
            }

            CHSV getColor(MilliSeconds32 /*now*/, LedIndex /*ledIndex*/) const override
            {
                return hsv_;
            }

        private:
            CHSV hsv_;
        };

    } // namespace color
} // namespace colorado