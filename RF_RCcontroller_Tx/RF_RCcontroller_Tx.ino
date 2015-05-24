#include <SPI.h>
#include "RF24.h"
#include "nRF24L01.h"
#include <GPSXClass.h>

RF24 radio(9,10);

const uint64_t pipe = 0x78787878A3LL;

unsigned int vetor[6];
int RX, RY, LX, LY, CH5 = 615, CH6 = 1140;

void setup(){
  PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_LOCK);
  PSX.updateState(PSX_PAD1);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(50);
  //radio.setRetries(15,15);
  radio.setPayloadSize(14);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  //radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_8);
  radio.openWritingPipe(pipe);
}

void loop(){
  PSX.updateState(PSX_PAD1);
  RX = ANALOG_RIGHT_X(PSX_PAD1);
  //RX = map(RX, 0, 255, 1140, 1985);
  RY = ANALOG_RIGHT_Y(PSX_PAD1);
  //RY = map(RY, 0, 255, 1985, 1140);
  LX = ANALOG_LEFT_X(PSX_PAD1);
  //LX = map(LX, 0, 255, 1140, 1985);
  LY = ANALOG_LEFT_Y(PSX_PAD1);
  //LY = map(LY, 0, 255, 1985, 1140);
  if (PRESSED_CIRCLE(PSX_PAD1)) {
    CH5 = 1295;
  }
  if (PRESSED_SQUARE(PSX_PAD1)) {
    CH5 = 1555;
  }
  if (PRESSED_CROSS(PSX_PAD1)) {
    CH5 = 615;
  }
  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    CH5 = 1425;
  }
  if (PRESSED_START(PSX_PAD1)) {
    CH6 = 1700;
  }
  if (RELEASED_START(PSX_PAD1)) {
    CH6 = 1140;
  }
  vetor[0] = RX;
  vetor[1] = RY;
  vetor[2] = LX;
  vetor[3] = LY;
  vetor[4] = CH5;
  vetor[5] = CH6;
  Serial.println(sizeof(vetor));
  radio.startWrite(&vetor, sizeof(vetor));
  delay(100);
}
