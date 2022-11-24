////
//// Created by trevor on 10/13/2022.
////

#include "../include/epd_n2h.h"

#include <Arduino.h>

#include "epd_driver.h"
#include "esp_sleep.h"


/**
 * Upper most button on side of device. Used to setup as wakeup source to start from deepsleep.
 * Pinout here https://ae01.alicdn.com/kf/H133488d889bd4dd4942fbc1415e0deb1j.jpg
 */
gpio_num_t FIRST_BTN_PIN = GPIO_NUM_39;

///**
// * Function that prints the reason by which ESP32 has been awaken from sleep
// */
//void print_wakeup_reason(){
//    esp_sleep_wakeup_cause_t wakeup_reason;
//    wakeup_reason = esp_sleep_get_wakeup_cause();
//    switch(wakeup_reason){
//        case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
//        case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
//        case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
//        case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
//        case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
//        default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
//    }
//}


/**
 * Powers off everything into deepsleep so device and display.
 */
void start_deep_sleep_with_wakeup_sources()
{
    epd_poweroff();
    delay(400);
    esp_sleep_enable_ext0_wakeup(FIRST_BTN_PIN, 0);

    Serial.println("Sending device to deepsleep");
    esp_deep_sleep_start();
}