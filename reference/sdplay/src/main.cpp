//
// Created by trevor on 1/15/2024.
//
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#define SPEAKER_PIN 9

#include <SPI.h>
#include <SD.h>                      // need to include the SD library
#include <TMRpcm.h>           //  also need to include this library...


TMRpcm tmrpcm;   // create an object for use in this sketch


void setup(){
    Serial.begin(9600);

    tone(SPEAKER_PIN, 1000, 1000);
    // pinMode(SPEAKER_PIN, OUTPUT);
    // pinMode(SD_ChipSelectPin, OUTPUT);

    tmrpcm.speakerPin = SPEAKER_PIN; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

    delay(500);
    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
        Serial.println("SD fail");
        return;   // don't do anything more if not
    }
    Serial.println("SD OK!");
    tmrpcm.setVolume(7);
    Serial.println(tmrpcm.isPlaying());
    tmrpcm.play("lazr.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
    Serial.println(tmrpcm.isPlaying());
    Serial.println(tmrpcm.isPlaying());
    delay(4000);
    Serial.println("Done");
    //tone(SPEAKER_PIN, 500, 1000);
}



void loop(){

    if(Serial.available()){
        if(Serial.read() == 'p'){ //send the letter p over the serial monitor to start playback
            tmrpcm.play("buzz.wav");
        }
    }

}