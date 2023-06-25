//
// Created by trevor on 6/25/2023.
//
#include <Arduino.h>
#include "ThermalPrinter.h"

#include "Adafruit_Thermal.h"
// #include "adalogo.h"
// #include "adaqrcode.h"

#define TX_PIN 1 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 0 // Arduino receive   GREEN WIRE   labeled TX on printer
// #define CTS_PIN 2
#define PrinterSerial Serial

Adafruit_Thermal printer(&PrinterSerial); //, CTS_PIN);     // Pass addr to printer constructor


void setupThermalPrinter(void) {
    PrinterSerial.begin(9600);

    printer.begin();
    printer.setFont('B');

}

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

void todo(void) {
    header("TODO");

    printer.println("Clean DOB Kit");
    printer.println("working out desk");
    printer.println("book flight");
    printer.println("digital clock");
    printer.println("HoneyDo Wifi Client");
    printer.println("HoneyDo Print Button");
    printer.println("Wire hole in desk");
    printer.println("one dave review");
    printer.println("sunday.py");
    printer.println("fix yoga");

}

void footer(void) {
    heartIzzy();
    printer.feed(2);

    printer.sleep();      // Tell printer to sleep
    delay(3000L);         // Sleep for 3 seconds
    printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults
}
