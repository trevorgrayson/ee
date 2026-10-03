#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "firasans.h"
#include "esp_adc_cal.h"
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "logo.h"

#if CONFIG_IDF_TARGET_ESP32S3
#include "pcf8563.h"
#include <Wire.h>
#endif

#if CONFIG_IDF_TARGET_ESP32
#define BATT_PIN            36
#elif CONFIG_IDF_TARGET_ESP32S3
#define BATT_PIN            14
#else
#error "Platform not supported"
#endif

#if defined(CONFIG_IDF_TARGET_ESP32)
#define SD_MISO             12
#define SD_MOSI             13
#define SD_SCLK             14
#define SD_CS               15
#elif defined(CONFIG_IDF_TARGET_ESP32S3)
#define SD_MISO             16
#define SD_MOSI             15
#define SD_SCLK             11
#define SD_CS               42
#else
#error "Platform not supported"
#endif

#if defined(CONFIG_IDF_TARGET_ESP32S3)
PCF8563_Class rtc;
#define TOUCH_SCL   17
#define TOUCH_SDA   18
#endif

int vref = 1100;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    char buf[128];

    // Correct the ADC reference voltage
    esp_adc_cal_characteristics_t adc_chars;
#ifdef CONFIG_IDF_TARGET_ESP32
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
#else
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_2, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
#endif
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
        vref = adc_chars.vref;
    }

#if defined(CONFIG_IDF_TARGET_ESP32S3)
    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    rtc.begin();
    rtc.setDateTime(2022, 6, 30, 0, 0, 0);
#endif

    epd_init();

    Rect_t area = {
        .x = 230,
        .y = 20,
        .width = logo_width,
        .height = logo_height,
    };

    epd_poweron();
    epd_clear();
    epd_draw_grayscale_image(area, (uint8_t *)logo_data);
    epd_draw_image(area, (uint8_t *)logo_data, BLACK_ON_WHITE);
    epd_poweroff();


    int cursor_x = 200;
    int cursor_y = 250;

    const char* messages[] = {
            "Sat 10AM: Swimming\n",
            "Sat  - Family Dinner.\n",
            "Sun - NO Soccer. Call Joe.\n",
            "Sun - Shop for the Week.\n"
    };

    epd_poweron();

    for(int ii=0; ii<4; ii++) {
        snprintf(buf, 128, messages[ii]);
        writeln((GFXfont * ) & FiraSans, buf, &cursor_x, &cursor_y, NULL);
        delay(500);
        cursor_x = 200;
        cursor_y += 50;
    }

    epd_poweroff();
}

void loop()
{
    // When reading the battery voltage, POWER_EN must be turned on
//    epd_poweron();
//    delay(10); // Make adc measurement more accurate
//    uint16_t v = analogRead(BATT_PIN);
//    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
//    String voltage = "➸ Voltage: " + String(battery_voltage) + "V";
//#if defined(CONFIG_IDF_TARGET_ESP32S3) //    voltage = voltage + String(" (") + rtc.formatDateTime(PCF_TIMEFORMAT_YYYY_MM_DD_H_M_S) + String(")");
//#endif
//    Serial.println(voltage);
//
//    Rect_t area = {
//        .x = 200,
//        .y = 460,
//#if defined(CONFIG_IDF_TARGET_ESP32S3)
//        .width = 700,
//#else
//        .width = 320,
//#endif
//        .height = 50,
//    };
//
//    int cursor_x = 200;
//    int cursor_y = 500;
//    epd_clear_area(area);
//    writeln((GFXfont *)&FiraSans, (char *)voltage.c_str(), &cursor_x, &cursor_y, NULL);
//
//
//    /**
//     * There are two ways to close
//     * It will turn off the power of the ink screen, but cannot turn off the blue LED light.
//     */
//    // epd_poweroff();
//
//    /**
//     * It will turn off the power of the entire
//     * POWER_EN control and also turn off the blue LED light
//     */
//    epd_poweroff_all();
//
    delay(5000);
}
