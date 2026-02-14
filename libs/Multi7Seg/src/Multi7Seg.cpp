#include "Multi7Seg.h"

Multi7Seg::Multi7Seg(uint8_t count)
        : _count(count)
{
    _displays = new Adafruit_7segment[_count];
}

bool Multi7Seg::begin(const uint8_t *addresses)
{
    Wire.begin();

    for (uint8_t i = 0; i < _count; i++) {
        if (!_displays[i].begin(addresses[i])) {
            return false;
        }
    }

    return true;
}

void Multi7Seg::print(uint8_t index, int value)
{
    if (index >= _count) return;

    _displays[index].print(value);
    _displays[index].writeDisplay();
}

void Multi7Seg::clear(uint8_t index)
{
    if (index >= _count) return;

    _displays[index].clear();
    _displays[index].writeDisplay();
}

void Multi7Seg::clearAll()
{
    for (uint8_t i = 0; i < _count; i++) {
        clear(i);
    }
}

void Multi7Seg::setBrightness(uint8_t brightness)
{
    for (uint8_t i = 0; i < _count; i++) {
        _displays[i].setBrightness(brightness);
    }
}
