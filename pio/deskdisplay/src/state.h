#ifndef EE_STATE_H
#define EE_STATE_H

struct Velocity {
  char track;
  float daily;
  float required;  
};

struct State {
  char *todos[5];
  int aqi;
  int count;
  char aqiStr[3];
  char *metar;
  char *calendar[20];
  char *error[30];
  // WX
  float temp;
  float humidity;

  struct Velocity velocity;
};

#endif