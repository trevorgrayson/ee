//
// Created by trevor on 8/1/25.
//
#include <stdio.h>
#include "string.h"

string secrets[10];

int main() {
    printf("OK\n");
    secrets[0] = String("OK");

    printf("%s", secrets[0]);
    return 0;
}