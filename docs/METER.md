# METERs

Apparatus for displaying telemetry information.  Using 
meter guages, 7-segment displays, LCD console, and
other non-screen devices.

## Work Streams

## software

milestone | description | date
--------- | ---------- | ----
meters app | new project | now
analog Meter class | takes pin, value setter, sets scaling | 
3x 7-segment ||
Console | LCD Screen |
Rotary  | |

## hardware

milestone | description                                       | date
--------- |---------------------------------------------------| ----
motherboard | hardeness for arduino, and connecting many panels | 
meter panel ||
console | 16x4 + rotary                                     |
7-segment panel | clock, 3x LED, buttons                            |

## targets

- trevor's desk device: 
  - 2-4 meters
  - 2-3 7 segment
  - 4x16 LCD screen (power)
- single meter device (pricing only)

## effort

### software

### hardware

#### pin budget
display    | pins                       | EMT
--- |----------------------------| ---
3x meter | A0, A1, A2                 | PWM, GND
3x 7-segment | 4,5 6,7, 8,9               | I2C 5V, GND
LCD, Console | 2,3                        | I2C 5V, GND
Rotary | 8, 9                       | GND (digital)
TOTAL| 3 analog, 6 digital, 2 I2C | 

```
VCC
GND
A0 - meter0
A1 - meter1
A2 - meter2
```

#### display/presentation

- displays
- harnesses (tst)

##### 3x meter panel (2 square meters + 100%)

**4-pin harness** - jumpers OK. May need transisters for power.

##### 3x 7-segment displays
For 3-timezone clock, alpha character alerts, high-viz display

**harness** test and use existing. 2 pins for all power. 2 pins for each.

##### console + double rotary
- Alert and status details
- double-rotary state selector
