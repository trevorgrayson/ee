//
// Created by trevor on 6/9/24.
//
#include <TM1637.h>
#include "pins.h"

TM1637 lax(LAX1, LAX2);
TM1637 dia(DIA1, DIA2); // inverted
TM1637 nyc(NYC1, NYC2); // <=|

void setuptm3();
void tm3alert();
void tm3display();