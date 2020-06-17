#include <SPI.h> //optional
#include <SD.h>
#include <TMRpcm.h>

//char mychar[] = ".wav";
const int CS_PIN = 10;
TMRpcm aud;


void setup() {
  //pinMode(9,OUTPUT);
  aud.speakerPin = 9;
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing Card");
  pinMode(CS_PIN, OUTPUT);
  if(!SD.begin(CS_PIN)) {
    Serial.println("Card Failure");
    return;
  }
  Serial.println("Card Ready");
  //tmrpcm.setVolume(2);
  aud.volume(7);
  aud.play("wel2.wav");
  Serial.println("played");
}

void loop() {
  
}

