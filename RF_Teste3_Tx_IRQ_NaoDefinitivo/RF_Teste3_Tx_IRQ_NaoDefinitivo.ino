#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
//#include "printf.h"

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A3LL;
static uint32_t mensagens = 0;

char c1 = 'A';
char c2 = 'B';
char c3 = 'C';
boolean sucesso = false;

void setup(){
  Serial.begin(57600);
  //printf_begin();
  radio.begin();
  radio.enableAckPayload();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setPayloadSize(16);
  radio.openWritingPipe(pipe);
  //radio.startListening();
  //radio.printDetails();
  attachInterrupt(0, radioAck, FALLING);
}

void loop(){
  radioWrite(c1);
  //radioWrite(c2);
  //radioWrite(c3);
  delay(5000);
}

void radioWrite(char n){
  Serial.print("Enviando ");
  Serial.println(n);
  radio.startWrite(&n, sizeof(char));
  delay(100);
}

void radioAck(){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(tx){
    Serial.print("Sucesso no envio!");
  }
  if(fail){
    Serial.print("Falha no envio.");
  }
  if(tx || fail){
    radio.powerDown();
  }
  if(rx){
    radio.read(&mensagens, sizeof(mensagens));
    Serial.print(" Ack: ");
    Serial.println(mensagens);
  }
}
