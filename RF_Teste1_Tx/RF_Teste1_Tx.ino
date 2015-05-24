#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0xE8E8F0F0E1LL, 0xE8E8F0F0A3LL};

char hello = 'A';

boolean sucesso = false;

void setup(){
  Serial.begin(57600);
  printf_begin();
  radio.begin();
  radio.setChannel(50);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPayloadSize(16);
  radio.openReadingPipe(1,pipes[1]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();
  radio.printDetails();
}

void loop(){
  radio.stopListening();
  sucesso = radio.write(&hello, sizeof(char));
  if(sucesso == true){
    Serial.println("Enviado com sucesso!");
  } else{
    Serial.println("Falha no envio.");
  }
  radio.startListening();
  delay(1000);
}
