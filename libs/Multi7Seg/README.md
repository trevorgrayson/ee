# README

```cpp
#include <Multi7Seg.h>

uint8_t addresses[] = { 0x70, 0x71, 0x72, 0x73 };

Multi7Seg displays;

void setup() {
    displays.begin(addresses);
    displays.setBrightness(5);
}

void loop() {
    static int counter = 0;

    displays.print(0, counter);
    displays.print(1, counter + 1);
    displays.print(2, counter + 2);
    displays.print(3, counter + 3);

    counter++;

    delay(500);
}

```