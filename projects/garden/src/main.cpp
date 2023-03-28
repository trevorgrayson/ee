#include<Arduino.h>
//#include "Napper.h"
#include "water.h"

#define ONE_DAY 86400000 // 24 * 60 * 60 * 1000

int PUMP1 = 8;
int PUMP2 = 9;
int PUMP3 = 10;
int PUMP4 = 11;

int Pin1 = 14; //A0;
int Pin2 = 14; //A1;
int Pin3 = 14; //A2;
int Pin4 = 14; //A3;

int RUN_BTN = 15;

float value1 = 0;
float value2 = 0;
float value3 = 0;
float value4 = 0;


void setup() {
  Serial.begin(9600);
  // initNapper();

  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(PUMP3, OUTPUT);
  pinMode(PUMP4, OUTPUT);
  
  pinMode(Pin1, INPUT);
  pinMode(Pin2, INPUT);
  pinMode(Pin3, INPUT);
  pinMode(Pin4, INPUT);
  pinMode(RUN_BTN, INPUT);
  
  digitalWrite(PUMP1, HIGH);
  digitalWrite(PUMP2, HIGH);
  digitalWrite(PUMP3, HIGH);
  digitalWrite(PUMP4, HIGH);
  delay(500);
}

void loop() {
  water(PUMP1);
  water(PUMP2);
  water(PUMP3);
  water(PUMP4);
    
  delay(ONE_DAY);
}
