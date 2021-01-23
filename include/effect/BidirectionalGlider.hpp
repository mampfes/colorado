#pragma once

#include "Pixel.hpp"
#include "Ratio.hpp"
#include "Time.hpp"
#include "color/ColorService.hpp"
#include "effect/EffectBase.hpp"
#include <chrono>

namespace colorado
{
    namespace effect
    {
        class BidirectionalGlider : public TimeService, public IEffect
        {
        public:
            BidirectionalGlider(color::IColorService& colorService) :
                colorService_{&colorService}
            {
            }

            void update(MilliSeconds32 now, HSVPixelArray& pixels) override;

        private:
            color::IColorService* colorService_{nullptr};
            Ratio<uint16_t> beamWidth_ = Ratio<uint16_t>{20, 100};
        };
    } // namespace effect
} // namespace colorado