/*
 * Use SoftwareSerial to talk to BlueSMiRF module
 * note pairing code is 1234
 */

#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(4);

int bot = 0;

void setup()
{
  motor1.setSpeed(80);
  motor2.setSpeed(84);
  //Serial.begin(9600);
  Serial1.begin(115200);      // initialize the HARDWARE serial port
  //Serial.println("Serial ready");
  //Serial1.println("Bluetooth ready");
}

void loop()
{
  bot = analogRead(4);
  if (bot >= 10)
  {
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(2000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
  if (Serial1.available())
  {
    char c = (char)Serial1.read();
    Serial.write(c);
    if (c == '0')
    {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
    if (c == '8')
    {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
    if (c == '4')
    {
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
    }
    if (c == '6')
    {
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
    }
    if (c == '2')
    {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
    }
  }
  /*if (Serial.available())
  {
    //char c = (char)Serial.read();
    //Serial2.write(c);
  }*/
}
