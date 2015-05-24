#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10);

const uint64_t pipes[] = {0x78787878A3LL, 0x78787878E1LL};

int vai = 10;
int veio[2];

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.enableAckPayload();
  radio.setChannel(25);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_16);
  //radio.openReadingPipe(1, pipe);
  //radio.startListening();
  attachInterrupt(0, radioReceive, FALLING);
  //pinMode(3, OUTPUT);
  //digitalWrite(3, LOW);
}

void loop(){
  if(Serial.available() > 0){
    char c = Serial.read();
    if(c == a){
      radio.openWritingPipe(pipes[2]);
      radio.startWrite(&vai, sizeof(vai));
    }
    if(c == b){
      radio.openWritingPipe(pipes[1]);
      radio.startWrite(&vai, sizeof(vai));
    }
  }
}

void radioReceive(){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(rx){
    Serial.println("Chegou");
    radio.read(&veio, sizeof(veio));
    if(veio[1] == 1){
      Serial.print("Chegou de 1: ");
      Serial.println(array[2]);
    }
    if(veio[1] == 2){
      Serial.print("Chegou de 2: ");
      Serial.println(array[2]);
    }
    /*if(go == '1'){
      Serial.println("1");
      digitalWrite(3, HIGH);
    }
    if(go == '2'){
      Serial.println("2");
      digitalWrite(3, LOW);
    }*/
  }
}