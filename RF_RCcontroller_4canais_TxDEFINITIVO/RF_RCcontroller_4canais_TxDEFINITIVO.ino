#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

#define ch1   0  //A0
#define ch2   1  //A1
#define ledOn 6  //D6
#define ledVd 7  //D7
#define ledVm 5  //D5
#define pb    8  //D8
#define sw3   3  //D3
#define sw1   4  //D4
#define sw2   2  //A2

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A3LL;

int array[4];
int CH1,CH2,SW2,CH7,CH8;
long int mCH1,mCH2,mCH7,mCH8;
boolean PB = false, SW1 = false, SW3 = false;

void radioReceive(void);

void setup(){
  pinMode(sw1, INPUT);
  pinMode(sw3, INPUT);
  pinMode(pb, INPUT);
  pinMode(ledVd, OUTPUT);
  pinMode(ledVm, OUTPUT);
  pinMode(ledOn, OUTPUT);
  digitalWrite(ledOn, HIGH);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  radio.setPayloadSize(10);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openWritingPipe(pipe);
  attachInterrupt(0, radioReceive, FALLING);
}

void loop(){
  for(int i = 0; i < 100; i++){
    CH1 = analogRead(ch1);
    mCH1 = mCH1 + CH1;
    CH2 = analogRead(ch2);
    mCH2 = mCH2 + CH2;
    SW1 = digitalRead(sw1);
    SW3 = digitalRead(sw3);
    SW2 = analogRead(sw2);
    PB = !digitalRead(pb);
    
    if(PB == false){
      CH7 = 130;
    }
    if(PB == true){
      CH7 = 250;
    }
    mCH7 = mCH7 + CH7;
    
    if(SW1 == true){
      CH8 = 50;
    }
    if(SW2 > 20){
      CH8 = 100;
    }
    if(SW3 == true){
      CH8 = 120;
    }
    mCH8 = mCH8 + CH8;
  }
  CH1 = mCH1/100;
  CH2 = mCH2/100;
  CH7 = mCH7/100;
  CH8 = mCH8/100;
  
  Serial.print("CH1: ");
  Serial.println(CH1);
  Serial.print("CH2: ");
  Serial.println(CH2);
  Serial.print("CH7: ");
  Serial.println(CH7);
  Serial.print("CH8: ");
  Serial.println(CH8);
  /*Serial.print("SW1: ");
  Serial.println(SW1);
  Serial.print("SW2: ");
  Serial.println(SW2);
  Serial.print("SW3: ");
  Serial.println(SW3);*/
  Serial.println();
  
  array[0] = CH1;
  array[1] = CH2;
  array[2] = CH7;
  array[3] = CH8;
  
  //Serial.println(sizeof(array));
  
  radio.startWrite(&array, sizeof(array));
  //delay(100);
  
  mCH1 = 0;
  mCH2 = 0;
  mCH7 = 0;
  mCH8 = 0;
}

void radioReceive(void){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(tx){
    digitalWrite(ledVm, LOW);
    digitalWrite(ledVd, HIGH);
  }
  if(fail){
    digitalWrite(ledVd, LOW);
    digitalWrite(ledVm, HIGH);
  }
}
