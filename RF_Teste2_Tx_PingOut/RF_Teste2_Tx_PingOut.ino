#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0x78787878A3LL, 0x78787878E1LL};

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
  radio.openReadingPipe(1,pipes[0]);
  radio.openWritingPipe(pipes[1]);
  radio.startListening();
  radio.printDetails();
}

void loop(){
  radio.stopListening();
  sucesso = radio.write(&hello, sizeof(char));
  if(sucesso == true){
    Serial.print("Enviado com sucesso!");
  } else{
    Serial.print("Falha no envio.");
  }
  radio.startListening();
  
  unsigned long esperando = millis();
  boolean timeout = false;
  while(!radio.available() && !timeout){
    if(millis() - esperando > 250){
      timeout = true;
    }
  }
  if(timeout){
    Serial.println(" Falha no retorno.");
  } else{
    Serial.println(" Sucesso no retorno!");
    char peguei;
    radio.read(&peguei, sizeof(char));
    Serial.println(peguei);
  }
  
  delay(1000);
}
