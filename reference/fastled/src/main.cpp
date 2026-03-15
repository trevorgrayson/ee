//
// Created by trevor on 2/14/26.
//
#include <FastLED.h>
#define NUM_LEDS 32
#define ROWS 8
CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812, 6>(leds, NUM_LEDS);
}

void loop() {
    leds[0] = CRGB::Red; FastLED.show(); delay(500);
    leds[0] = CRGB::Blue; FastLED.show(); delay(500);
}

/* 32 x 8
 * 64 x 4 =>
 * DMS > Confluent Prod > DBK Write | freshness
 */