//
// Created by trevor on 2/14/26.
//
// RGB Examples https://fastled.io/docs/d7/d82/struct_c_r_g_b.html
//
#include <FastLED.h>


#define DATA_PIN 23

#define NUM_LEDS 32
#define ROWS 8

#define RED     CRGB::Green
#define GREEN   CRGB::Red
#define BLUE    CRGB::Blue


CRGB leds[NUM_LEDS];

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void setup() {
    FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(84);
}

void loop() {
    leds[0] = RED; FastLED.show(); delay(500);
    leds[1] = GREEN; FastLED.show(); delay(500);
    leds[2] = BLUE; FastLED.show(); delay(500);

    static uint8_t hue = 0;
    Serial.print("x");
    // First slide the led in one direction
    for(int i = 0; i < NUM_LEDS; i++) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(10);
    }
    Serial.print("x");

    // Now go in the other direction.
    for(int i = (NUM_LEDS)-1; i >= 0; i--) {
        // Set the i'th led to red
        leds[i] = CHSV(hue++, 255, 255);
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // leds[i] = CRGB::Black;
        fadeall();
        // Wait a little bit before we loop around and do it again
        delay(10);
    }
}
/* 32 x 8
 * 64 x 4 =>
 * DMS > Confluent Prod > DBK Write | freshness
 */