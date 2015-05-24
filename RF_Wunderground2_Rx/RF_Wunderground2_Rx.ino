#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10);

const uint64_t pipe = 0xF0F0F0F0E1LL;

static uint32_t count = 0;
bool sender = true;
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
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_16);
  //radio.openWritingPipe(pipes[1]);
  //radio.openReadingPipe(1,pipe);
  attachInterrupt(0, radioRecieve, FALLING);
}

void loop(){
  if(Serial.available() > 0){
    req = Serial.read();
    if(req == '1'){
      radio.openWritingPipe(pipe);
      radio.startWrite(&go, sizeof(char));
      delay(250);
    }
  }
  /*
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
  delay(1000);*/
}

void radioRecieve(){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(sender == false){
    if(rx){
      radio.read(&array, sizeof(array));
      p = array[0];
      t = array[1];
      h = array[2];
      radio.writeAckPayload(1, &count, sizeof(count));
      ++count;
      serialPrint();
      radio.stopListening();
      radio.openWritingPipe(pipe);
      return;
    }
  }
  if(sender == true){
    if(rx){
      radio.read(&count, sizeof(count));
      radio.openReadingPipe(1,pipe);
      radio.startListening();
      sender = false;
    }
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
  sender = true;
}