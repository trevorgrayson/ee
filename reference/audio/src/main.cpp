#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 10
#define SPEAKER_PIN 9

TMRpcm tmrpcm;

void setup()
{
    tmrpcm.speakerPin = SPEAKER_PIN;
    Serial.begin(9600);
    if(!SD.begin(SD_ChipSelectPin))
    {
        Serial.println("SD fail");
        return;
    }
    tmrpcm.setVolume(6);
    tmrpcm.play("test.wav");
}

void loop() {
    // put your main code here, to run repeatedly:
}
