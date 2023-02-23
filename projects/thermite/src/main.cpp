#include <Wire.h>
#include "state.h"
#include "wifi.h"
#include "wx.h"


#define DELAY 1000 * 60 * 60


struct State state;


void render(State state) {
  // sprintf(buffer, "%4.1f (%4.1f)", state.temp, state.feelsLike);
  request(state);
  // sprintf(buffer, "%4.1f", state.humidity);
}


void setup() {
  Serial.begin(115200);
  state.temp = 0;
  state.humidity = 0;
  Serial.println("state setup.");
  wifiSetup();
  setupWX();
}

void loop() {
  tickWX(&state);
  Serial.println(state.temp);
  state.iteration++;
  render(state);
  Serial.println("rendered");
  delay(DELAY);
}

