#include <SPI.h>
#include <Wire.h>
#include "RF24.h"
#include "nRF24L01.h"

#define ledVerd 3
#define ledVerm 4

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A3LL;

byte vetor_byte[6];

void radioReceive(void);

void setup(){
  pinMode(ledVerd, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  Wire.begin();
  //Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  //radio.setRetries(15,15);
  radio.setPayloadSize(14);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  //radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openWritingPipe(pipe);
  attachInterrupt(0, radioReceive, FALLING);
}

void loop(){
  Wire.requestFrom(4, 6);
  vetor_byte[0] = Wire.read();
  vetor_byte[1] = Wire.read();
  vetor_byte[2] = Wire.read();
  vetor_byte[3] = Wire.read();
  vetor_byte[4] = Wire.read();
  vetor_byte[5] = Wire.read();
  /*for(int i = 0; i < 6; i++){
    Serial.println(vetor_byte[i]);
  }
  Serial.println();*/
  radio.startWrite(&vetor_byte, sizeof(vetor_byte));
  delay(100);
}

void radioReceive(void){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(tx){
    digitalWrite(ledVerm, LOW);
    digitalWrite(ledVerd, HIGH);
  }
  if(fail){
    digitalWrite(ledVerd, LOW);
    digitalWrite(ledVerm, HIGH);
  }
}
