#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
//#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0x78787878A3LL, 0xF0F0F0F0E1LL};

char hello = 'A';
char temp[6];
char hum[6];
char pres[6];

float t = 27.34, h = 88.75;
double p0 = 1004.15;
char buffer[12];

boolean sucesso = false;

void setup(){
  Serial.begin(57600);
  //printf_begin();
  radio.begin();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPayloadSize(16);
  radio.openReadingPipe(1,pipes[1]);
  radio.openWritingPipe(pipes[0]);
  radio.startListening();
  //radio.printDetails();
}

void loop(){
  int t_ = t*100;
  int h_ = h*100;
  int p0_ = p0*100;

  itoa(t_,buffer,10);
  itoa(h_,buffer,10);
  itoa(p0_,buffer,10);

  temp = 't' + t_ + '0';
  hum = 'h' + h_ + '0';
  pres = 'p' + t_ + '0';




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
