#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include <esp_task_wdt.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "epd_driver.h"
#include "firasans.h"
#include "esp_adc_cal.h"
#include <Wire.h>
#include <time.h>                       // time() ctime()
#ifdef ESP8266
#include <sys/time.h>                   // struct timeval
#endif
#include "CronAlarms.h"
#include "state.h"

// 3.4767h
// #define uS_TO_S_FACTOR 12516352000  /* Conversion factor for micro seconds to seconds */
#define uS_TO_S_FACTOR 3600000000 // 1 hour
// #define TIME_TO_SLEEP  6 * 60 * 60

#define BATT_PIN           36
#define SD_MISO            12
#define SD_MOSI            13
#define SD_SCLK            14
#define SD_CS              15

#define BUTTON1            34
#define BUTTON2            35
#define BUTTON3            39

#define TODO_COUNT  5
#define CALENDAR_COUNT 10

uint8_t *framebuffer;
int vref = 1100;

// buttons - GPIO0, GPIO34, GPIO35, GPIO39 // 11, 12, 13
struct State state;


void initState(struct State *state) {
  state->count = 0;
  state->temp = 0;
  state->humidity = 0;

  state->todos[0] = 0;
  state->calendar[0] = 0;
  state->error[0] = 0;
}


void btn3() {

}

void btn2() {
  state.count += 1;
  Serial.println(state.count); 
}

void btn1() {
  Serial.println("btn 1");
  splashScreen();
}

void setup()
{
  Serial.begin(9600);
  overhead();
  epd_init();

  initState();
  // splashScreen();
  setupClient();
  buttonSetup();
  setupWX();

  attachInterrupt(BUTTON1, btn1, HIGH);
  attachInterrupt(BUTTON2, btn2, HIGH);
  attachInterrupt(BUTTON3, btn3, HIGH);
  //epd_poweroff_all();
  esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR); // 3.4767h
}

void Tick() {
  request(&state);
  tickWX(&state);
  // renderCount(state);
  render(state);
}

void loop()
{
  Tick();
  // esp_wifi_stop();
  esp_deep_sleep_start();
}
