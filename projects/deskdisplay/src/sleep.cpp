//
// Created by Trevor Grayson on 10/3/22.
//

#include <Arduino.h>
#include "../include/sleep.h"
#include "esp_sleep.h"
#include "epd_highlevel.h"

/**
 * Upper most button on side of device. Used to setup as wakeup source to start from deepsleep.
 * Pinout here https://ae01.alicdn.com/kf/H133488d889bd4dd4942fbc1415e0deb1j.jpg
 */
gpio_num_t FIRST_BTN_PIN = GPIO_NUM_39;

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


/**
 * That's maximum 30 seconds of runtime in microseconds
 */
int64_t maxTimeRunning1 = 30000000;

void consider_sleeping() {
    if (esp_timer_get_time() > maxTimeRunning1) {
        Serial.println("Max runtime of 30s reached. Forcing deepsleep now to save energy");
        // display_center_message("Sleeping now.\nWake me up from deepsleep again\nwith the first button on my side");
        delay(1500);

        start_deep_sleep_with_wakeup_sources();
    }
}