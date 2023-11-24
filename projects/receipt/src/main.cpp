/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.
  ------------------------------------------------------------------------*/

#include <Arduino.h>
#include "../lib/ThermalPrinter/src/ThermalPrinter.h"
#include "txtings.h"
#include "PrintServer.h"
#include "Blinker.h"
//#include "WiFiConn.h"

#define GPIO0 0
#define TODO_BTN 2


struct State state;

void printTodo()
{
    request(&state);
    delay(3000);
    header("TODO");
    for (unsigned int x=0; x < sizeof(state.todos)/sizeof(state.todos[0]); x++) {
        receiptPrint(state.todos[x]);
    }
    footer();
}

int shouldPrintTodo()
{
    int todobtn = digitalRead(TODO_BTN);
    return todobtn == LOW;
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    };
    pinMode(GPIO0, INPUT);
    pinMode(TODO_BTN, INPUT);
    blinkerSetup();
    setupWifi();
    waitForWifi();

    setupThermalPrinter();
    delay(3000);
}

void loop() {
    if (shouldPrintTodo()) {
        blink(500);
        printTodo();
        // kill wifi here?
        // restart server?
        //serverSetup();
    }
    //serverTick();
    //blink(1000, 1);
}
