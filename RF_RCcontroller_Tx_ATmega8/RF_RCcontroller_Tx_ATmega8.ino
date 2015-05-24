#include <GPSXClass.h>
#include <Wire.h>

int RX, RY, LX, LY, CH5 = 50, CH6 = 130, _CH5, _CH6, _RY, _LY;
byte vetor[6];

void setup(){
  Wire.begin(4);
  Wire.onRequest(i2c_request);
  //Serial.begin(9600);
  PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_LOCK);
  PSX.updateState(PSX_PAD1);
}

void loop(){
  PSX.updateState(PSX_PAD1);
  RX = ANALOG_RIGHT_X(PSX_PAD1);
  RY = ANALOG_RIGHT_Y(PSX_PAD1);
  LX = ANALOG_LEFT_X(PSX_PAD1);
  LY = ANALOG_LEFT_Y(PSX_PAD1);
  if (PRESSED_CIRCLE(PSX_PAD1)) {
    CH5 = 100;
  }
  if (PRESSED_SQUARE(PSX_PAD1)) {
    CH5 = 140;
  }
  if (PRESSED_CROSS(PSX_PAD1)) {
    CH5 = 50;
  }
  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    CH5 = 120;
  }
  if (PRESSED_START(PSX_PAD1)) {
    CH6 = 250;
  }
  if (RELEASED_START(PSX_PAD1)) {
    CH6 = 130;
  }
  _RY = map(RY, 255, 0, 0, 255);
  _LY = map(LY, 255, 0, 0, 255);
  vetor[0] = (byte)RX;
  vetor[1] = (byte)_RY;
  vetor[2] = (byte)LX;
  vetor[3] = (byte)_LY;
  vetor[4] = (byte)CH5;
  vetor[5] = (byte)CH6;
  /*Serial.println("Byte:");
  for(int i=0; i<6; i++){
    Serial.println(vetor[i]);
  }
  Serial.println();
  delay(1000);*/
}

void i2c_request(void){
  Wire.write(vetor, 6);
}
