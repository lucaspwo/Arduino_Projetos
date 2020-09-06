// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
//--------------------------------------------------------------------

#include <Joystick.h>

#define L1        0
#define L2        1
#define DpadLeft  2
#define DpadUp    3
#define DpadRight 4
#define DpadDown  5
#define R2        7
#define B         16
#define Y         14
#define A         15
#define X         20
#define R1        21
#define LY        A7
#define LX        A8
#define STSL      A9
#define L3R3      A10
#define RY        A0
#define RX        A1

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  16, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,     // Rx, Ry, but no Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(DpadLeft, INPUT);
  pinMode(DpadUp, INPUT);
  pinMode(DpadRight, INPUT);
  pinMode(DpadDown, INPUT);
  pinMode(R2, INPUT);
  pinMode(B, INPUT);
  pinMode(Y, INPUT);
  pinMode(A, INPUT);
  pinMode(X, INPUT);
  pinMode(R1, INPUT);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(1023, 0);
  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
}

int stsl = 0, l3r3 = 0;

void loop() {

  stsl = analogRead(STSL);
  if(stsl == 0){
    Joystick.setButton(15,false);
    Joystick.setButton(14,false);
  } else if(stsl < 1000 && stsl > 10){
    Joystick.setButton(15,true);
    Joystick.setButton(14,false);
  } else if(stsl > 1000 && stsl < 1015){
    Joystick.setButton(14,true);
    Joystick.setButton(15,false);
  } else if(stsl == 1015){
    Joystick.setButton(15,true);
    Joystick.setButton(14,true);
  }

  l3r3 = analogRead(L3R3);
  if(l3r3 > 900){
    Joystick.setButton(13,false);
    Joystick.setButton(12,false);
  } else if(l3r3 < 10 && l3r3 > 7){
    Joystick.setButton(13,true);
    Joystick.setButton(12,false);
  } else if(l3r3 < 100 && l3r3 > 10){
    Joystick.setButton(12,true);
    Joystick.setButton(13,false);
  } else if(l3r3 == 7){
    Joystick.setButton(13,true);
    Joystick.setButton(12,true);
  }
  
  Joystick.setXAxis(analogRead(LY));
  Joystick.setYAxis(analogRead(LX));
  Joystick.setRxAxis(analogRead(RY));
  Joystick.setRyAxis(analogRead(RX));

  if(digitalRead(L1)){
    Joystick.setButton(0,true);
  }else{
    Joystick.setButton(0,false);
  }
  if(digitalRead(L2)){
    Joystick.setButton(1,true);
  }else{
    Joystick.setButton(1,false);
  }
  if(digitalRead(DpadLeft)){
    Joystick.setButton(2,true);
  }else{
    Joystick.setButton(2,false);
  }
  if(digitalRead(DpadUp)){
    Joystick.setButton(3,true);
  }else{
    Joystick.setButton(3,false);
  }
  if(digitalRead(DpadRight)){
    Joystick.setButton(4,true);
  }else{
    Joystick.setButton(4,false);
  }
  if(digitalRead(DpadDown)){
    Joystick.setButton(5,true);
  }else{
    Joystick.setButton(5,false);
  }
  if(digitalRead(R2)){
    Joystick.setButton(6,true);
  }else{
    Joystick.setButton(6,false);
  }
  if(digitalRead(B)){
    Joystick.setButton(7,true);
  }else{
    Joystick.setButton(7,false);
  }
  if(digitalRead(Y)){
    Joystick.setButton(8,true);
  }else{
    Joystick.setButton(8,false);
  }
  if(digitalRead(A)){
    Joystick.setButton(9,true);
  }else{
    Joystick.setButton(9,false);
  }
  if(digitalRead(X)){
    Joystick.setButton(10,true);
  }else{
    Joystick.setButton(10,false);
  }
  if(digitalRead(R1)){
    Joystick.setButton(11,true);
  }else{
    Joystick.setButton(11,false);
  }
  delay(10);
}
