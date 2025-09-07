//
// Created by trevor on 8/1/25.
//

#include "vault.h"

#define SECRET_COUNT 100

String secrets[SECRET_COUNT];
int offset = 0;

void setSecret(String secret)
{
    secrets[offset] = secret;
    offset++;
}

String getSecret(String key)
{
    return String("OK");
}
