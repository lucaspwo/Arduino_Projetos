#include <SPI.h>
#include <Servo.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(7,53);

const uint64_t pipe = 0x78787878A3LL;

Servo ch1, ch2, ch3, ch4, ch5, ch6;

byte vetor[6];
byte CH1, CH2, CH3, CH4, CH5, CH6;
long int  _CH1, _CH2, _CH3, _CH4, _CH5, _CH6;
void radioReceive(void);

void setup(){
  ch1.attach(3);
  ch2.attach(5);
  ch3.attach(6);
  ch4.attach(9);
  ch5.attach(10);
  ch6.attach(11);
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
    CH1 = vetor[0];
    CH2 = vetor[1];
    CH3 = vetor[3];
    CH4 = vetor[2];
    CH5 = vetor[4];
    CH6 = vetor[5];
    _CH1 = map(CH1, 0, 255, 900, 2000);
    _CH2 = map(CH2, 0, 255, 900, 2000);
    _CH3 = map(CH3, 0, 255, 900, 2000);
    _CH4 = map(CH4, 0, 255, 900, 2000);
    _CH5 = map(CH5, 50, 190, 900, 2000);
    _CH6 = map(CH6, 130, 250, 900, 2000);
    Serial.println(_CH1);
    Serial.println(_CH2);
    Serial.println(_CH3);
    Serial.println(_CH4);
    Serial.println(_CH5);
    Serial.println(_CH6);
    Serial.println();
    ch1.writeMicroseconds(_CH1);
    ch2.writeMicroseconds(_CH2);
    ch3.writeMicroseconds(_CH3);
    ch4.writeMicroseconds(_CH4);
    ch5.writeMicroseconds(_CH5);
    ch6.writeMicroseconds(2000);
  }
  //Serial.println("Saiu");
}
