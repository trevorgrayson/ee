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
#define TIME_TO_SLEEP  6 * 60 * 60

#define BATT_PIN           36
#define SD_MISO            12
#define SD_MOSI            13
#define SD_SCLK            14
#define SD_CS              15

#define BUTTON1            0
#define BUTTON2            1
#define BUTTON3            2

#define TODO_COUNT  5
#define CALENDAR_COUNT 10

uint8_t *framebuffer;
int vref = 1100;

// buttons - GPIO0, GPIO34, GPIO35, GPIO39 // 11, 12, 13
struct State state;

void correctRefVoltage() {
  // Correct the ADC reference voltage
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
    Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
    vref = adc_chars.vref;
  }
}

void setupFramebuffer() {
  framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
  if (!framebuffer) {
    Serial.println("alloc memory failed !!!");
    while (1);
  }
  memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
}

void setup()
{
  Serial.begin(115200);
  correctRefVoltage();
  epd_init();
  setupFramebuffer();

  state.count = 0;
  state.temp = 0;
  state.humidity = 0;
  // splashScreen();
  setupClient();
  buttonSetup();
  setupWX();

  //epd_poweroff_all();
  esp_sleep_enable_timer_wakeup(uS_TO_S_FACTOR); // 3.4767h
}

void Tick() {
  request(&state);
  tickWX(&state);
  //renderCount(state);
  render(state);
}

void loop()
{
  if( buttonPressed(BUTTON3) ) { 
    Serial.println(state.count); 
  }
  if( buttonPressed(BUTTON2) ) {
    state.count += 1;
    Serial.println("button 2");
    Tick();
  }
  if( buttonPressed(BUTTON1) ) {
    Serial.println("btn 1");
  }
  Tick();
  
  //esp_wifi_stop();
  esp_deep_sleep_start();
}
