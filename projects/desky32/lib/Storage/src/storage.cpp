//
// Created by trevor on 1/5/2024.
//

#include "storage.h"
#include "EEPROM.h"

#define EEPROM_SIZE 8

void setupStorage()
{
    EEPROM.begin(EEPROM_SIZE);
}

void store(int address, double value)
{
    // double = 8 bytes
    EEPROM.put(address, value);
}

int recall(int address)
{
    double result;
    EEPROM.get(address, result);

    return result;
}
