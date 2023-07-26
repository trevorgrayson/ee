//
// Created by trevor on 6/25/2023.
//
#include <Arduino.h>
#include "ThermalPrinter.h"
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
// #include "adalogo.h"
// #include "adaqrcode.h"

#define PRINTER_RX 16
#define PRINTER_TX 17
// #define CTS_PIN 2


// HardwareSerial printerSerial(2);

Adafruit_Thermal printer(&Serial); //, CTS_PIN);     // Pass addr to printer constructor


void setupThermalPrinter(void) {
    Serial.begin(9600);
//    printerSerial.begin(9600, SERIAL_8N1, PRINTER_RX, PRINTER_TX);
    delay(500);
    printer.begin();
    printer.setFont('B');
}

static void println(String s) {
    printer.println(s);
}

void receiptPrint(String s) {
    println(s);
}

void header(String s) {
    printer.println("");
    printer.doubleHeightOn();
    printer.println(s);
    printer.doubleHeightOff();
    printer.println("");
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

    printer.sleep();      // Tell printer to sleep
    delay(3000L);         // Sleep for 3 seconds
    printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults
}
