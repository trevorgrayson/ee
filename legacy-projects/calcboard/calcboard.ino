#include "calculator.h"
#include "view.h"

char buffer[50];

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  viewSetup();
  print("OK", 0);
}

void loop() {
  char key = getKey();
  if(key) {
    calcPress(key);

    clear();
    sprintf(buffer, "%4.2f", reg1);
    print(buffer, 0);
    sprintf(buffer, "%4.2f", reg0);
    print(buffer, 1);
    sprintf(buffer, "%4.2f", calcDisplay(key));
    print(buffer, 2);
    Serial.print("reg0: ");
    Serial.println(reg0);
    Serial.print("reg1: ");
    Serial.println(reg1);
    Serial.print("display: ");
    Serial.println(calcDisplay(key));  
  }
}
