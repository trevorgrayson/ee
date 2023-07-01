//
// Created by trevor on 6/25/2023.
//
#include <Arduino.h>
#include "ThermalPrinter.h"
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
// #include "adalogo.h"
// #include "adaqrcode.h"

#define PRINTER_RX 25
#define PRINTER_TX 26
// #define CTS_PIN 2


SoftwareSerial pSerial(PRINTER_RX, PRINTER_TX);

Adafruit_Thermal printer(&pSerial); //, CTS_PIN);     // Pass addr to printer constructor


void setupThermalPrinter(void) {
    pSerial.begin(9600); // , SERIAL_8N1, PRINTER_RX, PRINTER_TX);

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

void grocery(void) {
    header("Grocery");
    println("Berries");
    println("Yogurt");
    println("Waffles");
    println("Milk");
    println("Oat Milk");
    println("Num num Snacks");
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
