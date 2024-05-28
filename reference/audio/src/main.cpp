//TMRpcm library is needed

#define SD_ChipSelectPin 10
#define SPEAKER_PIN 9

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
    Serial.println("SD OK");
    tmrpcm.setVolume(6);
    tmrpcm.play("test.wav");
    delay(1000);
    Serial.println("done");
}

void loop() {
    // put your main code here, to run repeatedly:
}
