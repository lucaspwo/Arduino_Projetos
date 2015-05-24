#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
//#include "printf.h"

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A3LL;
static uint32_t mensagens = 0;
//int cont = 0;
char c1/*, c2, c3*/;

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
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  //radio.printDetails();
  attachInterrupt(0, radioRead, FALLING);
}

void loop(){
  Serial.print("c1: ");
  Serial.println(c1);
  //Serial.print("c2: ");
  //Serial.println(c2);
  //Serial.print("c3: ");
  //Serial.println(c3);
  delay(2000);
}

void radioRead(){
  /*if(cont == 3){
    cont = 0;
  }*/
  char c;
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  /*if(tx){
    Serial.println("Ack Payload: Sent");
  }*/
  /*if(fail){
    Serial.println("Ack Payload: Failed");
  }*/
  if(rx){
    radio.read(&c, sizeof(char));
    //Serial.println(c);
    radio.writeAckPayload(1,&mensagens, sizeof(mensagens));
    ++mensagens;
  }
  /*if(cont == 0){*/
    c1 = c;/*
  } else if(cont == 1){
    c2 = c;
  } else if(cont == 2){
    c3 = c;
  }
  cont++;*/
  //delay(50);
}
