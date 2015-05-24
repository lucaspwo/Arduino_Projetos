#include <SPI.h>
#include <Servo.h>
#include "RF24.h"
#include "nRF24L01.h"

RF24 radio(9,10); //(7,53)

const uint64_t pipe = 0x78787878A1LL;

Servo ch1, ch2, ch7, ch8;

byte array[4];
byte CH1, CH2, CH7, CH8;
long int  _CH1, _CH2, _CH7, _CH8;
void radioReceive(void);

void setup(){
  ch1.attach(3);
  ch2.attach(5);
  ch7.attach(10);
  ch8.attach(11);
  //pinMode(53, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  radio.setPayloadSize(14);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  attachInterrupt(0, radioReceive, FALLING);
}

void loop(){
  //Serial.println(4 * sizeof(byte));
  //delay(100);
}

void radioReceive(void){
  Serial.println("Chegou");
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);
  if(tx){
    Serial.println("Sucesso");
    radio.read(&array, sizeof(array));
    CH1 = array[0];
    CH2 = array[1];
    CH7 = array[2];
    CH8 = array[3];
    _CH1 = map(CH1, 0, 255, 900, 2000);
    _CH2 = map(CH2, 0, 255, 900, 2000);
    _CH7 = map(CH7, 50, 190, 900, 2000);
    _CH8 = map(CH8, 130, 250, 900, 2000);
    Serial.println(_CH1);
    Serial.println(_CH2);
    Serial.println(_CH7);
    Serial.println(_CH8);
    ch1.writeMicroseconds(_CH1);
    ch2.writeMicroseconds(_CH2);
    ch7.writeMicroseconds(_CH7);
    ch8.writeMicroseconds(_CH8);
  }
  Serial.println("Saiu");
}
