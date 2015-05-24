/*
This example demonstrates all features of the library.

- The controller starts up in ANALOG mode, and is locked
  (user cannot switch modes using the ANALOG button)
  
- CROSS shows the readings from all four analog axis

- Pin mapping:  (controller pin 1)DATA*       -> Arduino pin 7
                (controller pin 2)COMMAND     -> Arduino pin 6
                (controller pin 6)ATTENTION*  -> Arduino pin 5
                (controller pin 7)CLOCK       -> Arduino pin 4
                (controller pin 9)ACK         -> Arduino pin 3
                *1K ohm pull-up resistor
*/

#include <GPSXClass.h>

int RX, RY, LX, LY;

void setup()
{
  Serial.begin(38400);
  PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_LOCK);
  
  //PSX.motorEnable(PSX_PAD1, MOTOR1_ENABLE, MOTOR2_ENABLE);
  
  // Poll current state once.
  PSX.updateState(PSX_PAD1);
}

void loop()
{
  PSX.updateState(PSX_PAD1);
  
  //(ANALOG_RIGHT_X(PSX_PAD1) == 50) {
    RX = ANALOG_RIGHT_X(PSX_PAD1);
    //Serial.print("analog right x = ");
    //Serial.println(RX);
  //}
  
  //if (ANALOG_RIGHT_Y(PSX_PAD1) == 50) {
    RY = ANALOG_RIGHT_Y(PSX_PAD1);
    //Serial.print("analog right y = ");
    //Serial.println(RY);
  //}
  
  //if (ANALOG_LEFT_X(PSX_PAD1) == 50) {
    LX = ANALOG_LEFT_X(PSX_PAD1);
    //Serial.print("analog left x = ");
    //Serial.println(LX);
  //}
  
  //if (ANALOG_LEFT_Y(PSX_PAD1) == 50) {
    LY = ANALOG_LEFT_Y(PSX_PAD1);
    //Serial.print("analog left y = ");
    //Serial.println(LY);
  //}

  if (PRESSED_CIRCLE(PSX_PAD1)) {
    Serial.println("Pressed circle");
    //PSX.motor(PSX_PAD1, MOTOR1_ON, 0x00);
  }

  if (RELEASED_CIRCLE(PSX_PAD1)) {
    Serial.println("Released circle");
    //PSX.motor(PSX_PAD1, MOTOR1_OFF, 0x00);
  }    

  if (PRESSED_SQUARE(PSX_PAD1)) {
    Serial.println("Pressed square");
    //PSX.mode(PSX_PAD1, MODE_DIGITAL, MODE_UNLOCK);
  }

  if (RELEASED_SQUARE(PSX_PAD1)) {
    Serial.println("Released square");
  }

  if (PRESSED_CROSS(PSX_PAD1)) {
    Serial.println("Pressed cross");
    
    Serial.print("analog right x = ");
    Serial.println(RX);
    
    Serial.print("analog right y = ");
    Serial.println(RY);
    
    Serial.print("analog left x = ");
    Serial.println(LX);
    
    Serial.print("analog left y = ");
    Serial.println(LY);
    //PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_UNLOCK);
    //PSX.motorEnable(PSX_PAD1, MOTOR1_ENABLE, MOTOR2_ENABLE);
  }

  if (RELEASED_CROSS(PSX_PAD1)) {
    Serial.println("Released cross");
  }

  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    //PSX.motor(PSX_PAD1, MOTOR1_OFF, ANALOG_LEFT_X(PSX_PAD1));
  }

  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    Serial.println("Pressed triangle");
  }

  if (RELEASED_TRIANGLE(PSX_PAD1)) {
    Serial.println("Released triangle");
    //PSX.motor(PSX_PAD1, MOTOR1_OFF, 0x00);
  }
  
  if (PRESSED_LEFT(PSX_PAD1)) {
    Serial.println("Pressed left");
  }
  
  if (PRESSED_RIGHT(PSX_PAD1)) {
    Serial.println("Pressed right");
  }
  
  if (PRESSED_DOWN(PSX_PAD1)) {
    Serial.println("Pressed down");
  }
  
  if (PRESSED_UP(PSX_PAD1)) {
    Serial.println("Pressed up");
  }
  
  if (PRESSED_START(PSX_PAD1)) {
    Serial.println("Pressed start");
  }
  
  if (PRESSED_STICK_RIGHT(PSX_PAD1)) {
    Serial.println("Pressed r3");
  }
  
  if (PRESSED_STICK_LEFT(PSX_PAD1)) {
    Serial.println("Pressed l3");
  }
  
  if (PRESSED_SELECT(PSX_PAD1)) {
    Serial.println("Pressed select");
  }
  
  if (PRESSED_L1(PSX_PAD1)) {
    Serial.println("Pressed l1");
  }
  
  if (PRESSED_L2(PSX_PAD1)) {
    Serial.println("Pressed l2");
  }
  
  if (PRESSED_R1(PSX_PAD1)) {
    Serial.println("Pressed r1");
  }
  
  if (PRESSED_R2(PSX_PAD1)) {
    Serial.println("Pressed r2");
  }
  
  if (RELEASED_LEFT(PSX_PAD1)) {
    Serial.println("Released left");
  }
  
  if (RELEASED_RIGHT(PSX_PAD1)) {
    Serial.println("Released right");
  }
  
  if (RELEASED_DOWN(PSX_PAD1)) {
    Serial.println("Released down");
  }
  
  if (RELEASED_UP(PSX_PAD1)) {
    Serial.println("Released up");
  }
  
  if (RELEASED_START(PSX_PAD1)) {
    Serial.println("Released start");
  }
  
  if (RELEASED_STICK_RIGHT(PSX_PAD1)) {
    Serial.println("Released r3");
  }
  
  if (RELEASED_STICK_LEFT(PSX_PAD1)) {
    Serial.println("Released l3");
  }
  
  if (RELEASED_SELECT(PSX_PAD1)) {
    Serial.println("Released select");
  }
  
  if (RELEASED_L1(PSX_PAD1)) {
    Serial.println("Released l1");
  }
  
  if (RELEASED_L2(PSX_PAD1)) {
    Serial.println("Released l2");
  }
  
  if (RELEASED_R1(PSX_PAD1)) {
    Serial.println("Released r1");
  }
  
  if (RELEASED_R2(PSX_PAD1)) {
    Serial.println("Released r2");
  }
}
