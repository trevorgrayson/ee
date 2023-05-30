//
// Created by trevor on 5/28/23.
// https://www.theengineeringprojects.com/2018/10/introduction-to-arduino-duemilanove.html

#ifndef EE_PINS_H
#define EE_PINS_H

// digital
#define ARTICULATE_SWITCH_UP   3 // 2 RX
#define ARTICULATE_SWITCH_DOWN 2 // 3 TX
#define ROD_SELECT 4  // 4

#define VENT_BTN_1 5 // 5
#define VENT_LGT_1 6
#define VENT_BTN_2 7
#define VENT_LGT_2 8
#define VENT_BTN_3 9
#define VENT_LGT_3 10
// 12
// 13 Meh
// 14
// 15
// 16  // 4 pins = 10 combo
// 17  -| Shift Register: 3 pins
// 18  -|
// 19  -/
// 20 GND
// 21 AREF

// analog
#define BATT_SETTING_1 23  // 23 A0
#define BATT_SETTING_2 24  // 24 A1
// 25 A2
// 26 A3
// 27 A4 Wire.h
// 28 A5 Wire.h
#endif //EE_PINS_H
