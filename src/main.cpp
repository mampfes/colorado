#include <Arduino.h>

#include "color/FixColorService.hpp"
#include "color/RainbowColorService.hpp"

#include "effect/BidirectionalGlider.hpp"
#include "effect/Rotator.hpp"

#include <FastLED.h>

#define LED_PIN 5
#define CLOCK_PIN 4
#define COLOR_ORDER GBR
#define CHIPSET WS2801
#define NUM_LEDS 16

#define BRIGHTNESS 200
#define FRAMES_PER_SECOND 1

bool gReverseDirection = false;

CRGB leds[NUM_LEDS];
colorado::HSVPixelArray pixels{NUM_LEDS};

// Fire2012 with programmable Color Palette
//
// This code is the same fire simulation as the original "Fire2012",
// but each heat cell's temperature is translated to color through a FastLED
// programmable color palette, instead of through the "HeatColor(...)" function.
//
// Four different static color palettes are provided here, plus one dynamic one.
//
// The three static ones are:
//   1. the FastLED built-in HeatColors_p -- this is the default, and it looks
//      pretty much exactly like the original Fire2012.
//
//  To use any of the other palettes below, just "uncomment" the corresponding code.
//
//   2. a gradient from black to red to yellow to white, which is
//      visually similar to the HeatColors_p, and helps to illustrate
//      what the 'heat colors' palette is actually doing,
//   3. a similar gradient, but in blue colors rather than red ones,
//      i.e. from black to blue to aqua to white, which results in
//      an "icy blue" fire effect,
//   4. a simplified three-step gradient, from black to red to white, just to show
//      that these gradients need not have four components; two or
//      three are possible, too, even if they don't look quite as nice for fire.
//
// The dynamic palette shows how you can change the basic 'hue' of the
// color palette every time through the loop, producing "rainbow fire".

CRGBPalette16 gPal;
std::chrono::steady_clock::time_point startTime;
colorado::color::RainbowColorService rainbowColor{CHSV{0, 255, 255}};
colorado::color::FixColorService fixColor{CHSV{0, 255, 255}};
//colorado::effect::BidirectionalGlider glider{fixColor};
colorado::effect::BidirectionalGlider glider{rainbowColor};
colorado::effect::Rotator rotator{rainbowColor};

void setup()
{
    delay(3000); // sanity delay
    FastLED.addLeds<CHIPSET, LED_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    startTime = std::chrono::steady_clock::now();
    //rainbowColor.setup(colorado::TimeOffset{0});
    //glider.setup(colorado::TimeOffset{0});
    //rotator.setup(colorado::TimeOffset{0});

    // This first palette is the basic 'black body radiation' colors,
    // which run from black to red to bright yellow to white.
    gPal = PartyColors_p;

    // These are other ways to set up the color palette for the 'fire'.
    // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
    //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);

    // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
    //   gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);

    // Third, here's a simpler, three-step gradient, from black to red to white
    //   gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);

    Serial.begin(115200);
}

void loop()
{
    //  Serial.println("Hallo");
    colorado::MilliSeconds32 timeOffset{millis()};
#if 0
    glider.update(timeOffset, pixels);
#else
    rotator.update(timeOffset, pixels);
#endif

    // convert from HSV to RGB
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = pixels[i];
    }

    FastLED.show(); // display this frame
                    // FastLED.delay(1000 / FRAMES_PER_SECOND);
    Serial.flush();
}
