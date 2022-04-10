#include <Arduino.h>
#include "constants.h"

const int BUZZER = GPIO3;


void setup(){
  Serial.begin(9600);
  Serial.println("+");

  pinMode(BUZZER, OUTPUT);
  tone(BUZZER, 1040);
  delay(250);
  tone(BUZZER, 987);
  delay(250);
  tone(BUZZER, 880);
  delay(250);
  noTone(BUZZER);
}

void loop(){
  while (!isOnline()) {
      Serial.println("offline");
      starwars(BUZZER);
      delay(500);
  }
  noTone(BUZZER);
  Serial.print(".");
  delay(1000);
}
