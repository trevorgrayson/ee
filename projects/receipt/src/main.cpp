/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include <Arduino.h>
#include "Adafruit_Thermal.h"
// #include "adalogo.h"
// #include "adaqrcode.h"

#define LED_PIN 2

#define TX_PIN 1 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 0 // Arduino receive   GREEN WIRE   labeled TX on printer
// #define CTS_PIN 2
#define PrinterSerial Serial

Adafruit_Thermal printer(&PrinterSerial); //, CTS_PIN);     // Pass addr to printer constructor

void header(String s) {
    printer.println("");
    printer.doubleHeightOn();
    printer.println(s);
    printer.doubleHeightOff();
    printer.println("");
}

void grocery(void) {
    header("Grocery");
    printer.println("Berries");
    printer.println("Yogurt");
    printer.println("Waffles");
    printer.println("Milk");
    printer.println("Oat Milk");
    printer.println("Num num Snacks");
}

void heartIzzy(void) {
    printer.println("");
    printer.setSize('M');
    printer.justify('C');
    printer.println("I <3 Isaac");
    printer.setSize('S');
    printer.justify('L');
}

void footer(void) {
    heartIzzy();
    printer.feed(2);
}

void setup() {
    PrinterSerial.begin(9600);
    pinMode(LED_PIN, OUTPUT);

    printer.begin();
    printer.setFont('B');

    header("TODO");

    printer.println("dishwasher");
    printer.println("Clean DOB Kit");
    printer.println("HoneyDo Print Button");
    printer.println("HoneyDo Wifi Client");
    printer.println("ATMega Wrapper Blinky");

    printer.println("Wire hole in desk");
    printer.println("fix yoga");
    footer();

    printer.sleep();      // Tell printer to sleep
    delay(3000L);         // Sleep for 3 seconds
    printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults
}

void loop() {
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
}
