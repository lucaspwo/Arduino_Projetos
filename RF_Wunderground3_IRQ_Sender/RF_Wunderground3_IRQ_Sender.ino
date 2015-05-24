#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10);

const uint64_t pipe = 0xF0F0F0F0E1LL;

char req;
char go = 'O';
float array[3];
float p,t,h;
void radioRecieve(void);

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.enableAckPayload();
  radio.setChannel(100);
  radio.setRetries(15,15);
  radio.setPayloadSize(16);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.openWritingPipe(pipe);
  attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
  if(Serial.available() > 0){
    req = Serial.read();
    if(req == '1')
      radio.startWrite(&go, sizeof(char));
  }
}

void radioRecieve(){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(rx){
    radio.read(&array, sizeof(array));
    p = array[0];
    t = array[1];
    h = array[2];
    serialPrint();
  }  
}

void serialPrint(){
  Serial.print("Press = ");
  Serial.print(p);
  Serial.print("\t");
  Serial.print("Temp = ");
  Serial.print(t);
  Serial.print("\t");
  Serial.print("Hum = ");
  Serial.println(h);
}
