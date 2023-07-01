/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include <Arduino.h>
#include "ThermalPrinter.h"
#include "txtings.h"

#define LED_PIN 2

struct State state;

void blink(unsigned int time, unsigned int count) {
    for (unsigned int x=0; x < count; x++) {
        digitalWrite(LED_PIN, LOW);
        delay(time);
        digitalWrite(LED_PIN, HIGH);
        delay(time);
    }
}

void blink(unsigned int time) {
    blink( time, 2);
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    delay(20);
    blink(500, 5);

    setupThermalPrinter();

    blink(500, 3);
    delay(1000);
    blink(500, 1);


    setupTxtings();
    blink(500, 2);

    request(&state);
    blink(100, 4);

    header("TODO");

    for (unsigned int x=0; x < sizeof(state.todos)/sizeof(state.todos[0]); x++) {
        receiptPrint(state.todos[x]);
    }

    footer();
}

void loop() {
    blink(1000, 1);
}
