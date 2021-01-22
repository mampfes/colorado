#pragma once

#include <cstdint>
#include "hsv2rgb.h"

namespace colorado
{
    
#if 0
struct RGBPixel {
	union {
		struct {
            union {
                uint8_t r;
                uint8_t red;
            };
            union {
                uint8_t g;
                uint8_t green;
            };
            union {
                uint8_t b;
                uint8_t blue;
            };
        };
		uint8_t raw[3];
	};
};
#else
using RGBPixel = CRGB;
#endif

}