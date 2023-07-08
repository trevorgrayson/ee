//
// Created by Trevor Grayson on 7/6/23.
// https://en.ovcharov.me/2020/02/29/how-to-measure-battery-level-with-esp32-microcontroller/
// https://mansfield-devine.com/speculatrix/2021/08/esp32-room-thermometer-with-18650-battery-level-indicator/
// BAT_ADC_EN

#define R2 100
#define R3 10

#define VOLTAGE_OUT(Vin) (((Vin) * R3) / (R2 + R3))

#define VOLTAGE_MAX 4200
#define VOLTAGE_MIN 3300

#define ADC_REFERENCE 1100
#define VOLTAGE_TO_ADC(in) ((ADC_REFERENCE * (in)) / 4096)
#define BATTERY_MAX_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MAX))
#define BATTERY_MIN_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MIN))


int calc_battery_percentage(int adc)
{
    int battery_percentage = 100 * (adc - BATTERY_MIN_ADC) / (BATTERY_MAX_ADC - BATTERY_MIN_ADC);

    if (battery_percentage < 0)
        battery_percentage = 0;
    if (battery_percentage > 100)
        battery_percentage = 100;

    return battery_percentage;
}