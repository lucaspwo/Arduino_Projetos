#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(7,53);

const uint64_t pipe = 0x78787878A3LL;

byte vetor[6];
byte CH1, CH2, CH3, CH4, CH5, CH6;
void radioRecieve(void);

void setup(){
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  //radio.setRetries(15,15);
  radio.setPayloadSize(14);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  //radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  attachInterrupt(0, radioReceive, FALLING);
}

void loop(){
}

void radioReceive(void){
  //Serial.println("Chegou");
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(rx){
    radio.read(&vetor, sizeof(vetor));
    CH1 = vetor[1];
    CH2 = vetor[0];
    CH3 = vetor[3];
    CH4 = vetor[2];
    CH5 = vetor[4];
    CH6 = vetor[5];
    Serial.println(CH1);
    Serial.println(CH2);
    Serial.println(CH3);
    Serial.println(CH4);
    Serial.println(CH5);
    Serial.println(CH6);
    digitalWrite(3, CH1);
    digitalWrite(5, CH2);
    digitalWrite(6, CH3);
    digitalWrite(9, CH4);
    digitalWrite(10, CH5);
    digitalWrite(11, CH6);
  }
  //Serial.println("Saiu");
}
