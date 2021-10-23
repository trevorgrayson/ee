#include "DHT.h"

#define DHTPIN 12 // 13     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);


void setupWX() {
  dht.begin();
}

void tickWX(State *state) {
  // Wait a few seconds between measurements.

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  state->humidity = dht.readHumidity();
  state->temp = dht.readTemperature(); // Celsius
  //state->tempuratureF = dht.readTemperature(true); // Fahrenheit 

  // Check if any reads failed and exit early (to try again).
  // if (isnan(h) || isnan(t) || isnan(f))

  // Compute heat index in Fahrenheit (the default)
  //  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //  float hic = dht.computeHeatIndex(t, h, false);
}
