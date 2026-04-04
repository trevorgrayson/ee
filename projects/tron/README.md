# FastLED on ESP32-WROOM (PlatformIO)

This project targets the ESP32-WROOM-32 module using the Arduino framework and FastLED.

## Hardware
- Board: ESP32-WROOM-32 (PlatformIO board id: `esp32dev`)
- LED strip: WS2812/WS2812B (or compatible)
- Data pin: GPIO23 (see `DATA_PIN` in `src/main.cpp`)
- Matrix: 32x8, serpentine by columns (each column is 8 pixels tall)

Wiring notes:
- ESP32 5V -> LED 5V (or external 5V supply)
- ESP32 GND -> LED GND (common ground required)
- ESP32 GPIO23 -> LED DIN (add a 330-470 ohm series resistor recommended)
- If using external power for LEDs, connect grounds.

## Build and Upload

```bash
pio run
pio run -t upload
```

## Monitor

```bash
pio device monitor
```

## Configuration
- `platformio.ini` default environment: `esp32-wroom-32`
- LED settings in `src/main.cpp`:
  - `DATA_PIN`
  - `MATRIX_WIDTH`
  - `MATRIX_HEIGHT`
  - Brightness: `FastLED.setBrightness(84)`

## Notes
- Color order is set to `GRB` in `src/main.cpp`. If your strip uses a different order, update the template in `FastLED.addLeds<...>()`.

## Controls (INPUT_PULLUP)
Player 1 (Red):
- Up: 		GPIO16
- Down: 	GPIO17
- Left: 	GPIO18
- Right: 	GPIO19

Player 2 (Blue):
- Up: 		GPIO21
- Down: 	GPIO22
- Left: 	GPIO25
- Right: 	GPIO26

Buttons are active-low with internal pull-ups enabled. Connect each button between the GPIO pin and GND.
