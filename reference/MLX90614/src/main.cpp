//
// Created by trevor on 3/29/24.
//
// https://lastminuteengineers.com/mlx90614-ir-temperature-sensor-arduino-tutorial/
// https://github.com/avishorp/TM1637/blob/master/examples/TM1637Test/TM1637Test.ino
#include <Arduino.h>
#include <TM1637Display.h>
#include <Adafruit_MLX90614.h>

// TM Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
TM1637Display display(CLK, DIO);


void setup() {
    Serial.begin(9600);
    while (!Serial);

    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (1);
    };

    display.setBrightness(0xa0);
}

void loop() {
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    display.showNumberDec(mlx.readObjectTempF(), false);

    Serial.println();
    delay(500);
}
