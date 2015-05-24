#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"

#define ledOn   6
#define ledVerd 7
#define ledVerm 5
#define pushButton 9
#define ch1     A0
#define ch2     A1
#define switch1 4
#define switch2 A3
#define switch3 3

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A1LL;

byte array[4];

long int pB,s1,s2,s3;
long int cH1,cH2;

void radioReceive(void);

void setup(){
  pinMode(ledVerd, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  pinMode(ledOn, OUTPUT);
  pinMode(pushButton, INPUT);
  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
  pinMode(ch1, INPUT);
  pinMode(ch2, INPUT);
  digitalWrite(ledOn, HIGH);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  radio.setPayloadSize(14);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openWritingPipe(pipe);
  attachInterrupt(0, radioReceive, FALLING);
}

void loop(){
  cH1 = analogRead(ch1);
  cH2 = analogRead(ch2);
  pB = digitalRead(pushButton);
  s1 = digitalRead(switch1);
  //s2 = digitalRead(switch2);
  s2 = analogRead(switch2);
  s3 = digitalRead(switch3);
  
  array[0] = map(cH1, 0, 1023, 0, 255);
  array[1] = map(cH2, 0, 1023, 0, 255);
  
  if(pB == HIGH){
    array[2] = 250;
  }
  if(pB == LOW){
    array[2] = 130;
  }
  if(s1 == HIGH){
    array[3] = 50;
  }
  //if(s2 == HIGH)
    //array[3] = 100;
  if(s2 >=20){
    array[3] = 100;  
  }
  if(s3 == HIGH){
    array[3] = 120;
  }

  Serial.println(array[0]);
  Serial.println(array[1]);
  Serial.println(array[2]);
  Serial.println(array[3]);
  Serial.println();
  
  radio.startWrite(&array, sizeof(array));
  delay(100);
}

void radioReceive(void){
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(tx){
    digitalWrite(ledVerm, LOW);
    digitalWrite(ledVerd, HIGH);
  }
  if(fail){
    digitalWrite(ledVerd, LOW);
    digitalWrite(ledVerm, HIGH);
  }
}
