#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10);

const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

char ok = 'O';
float array[3];
float p,t,h;
//void radioRecieve(void);

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  //attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
  if(radio.available()){
    bool concl = false;
    while(!concl){
      concl = radio.read(&array, sizeof(array));
    }
    p = array[0];
    t = array[1];
    h = array[2];
    radio.stopListening();
    radio.write(&ok, sizeof(char));
    radio.startListening();
  }
  
  Serial.print("Press = ");
  Serial.print(p);
  Serial.print("\t");
  Serial.print("Temp = ");
  Serial.print(t);
  Serial.print("\t");
  Serial.print("Hum = ");
  Serial.println(h);
  delay(1000);
}

/*void radioRecieve(){
}*/
