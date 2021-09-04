#include "calculator.h"


void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  char key = getKey();
  if(key) {
    calcPress(key);
    Serial.print("reg0: ");
    Serial.println(reg0);
    Serial.print("reg1: ");
    Serial.println(reg1);
    Serial.print("display: ");
    Serial.println(calcDisplay(key));  
  }
}
