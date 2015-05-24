// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include <Servo.h>

Servo myservo;

int x;
int pos = 0;

void setup()
{
  myservo.attach(9);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  if(x == 5)
  {
    pos = 177;
    myservo.write(pos);
  }
  if(x == 10)
  {
    pos = 0;
    myservo.write(pos);
  }
  if(x == 15)
  {
    pos = 91;
    myservo.write(pos);
  }
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    //char c = Wire.read(); // receive byte as a character
    x = Wire.read();
  }
  x = Wire.read();    // receive byte as an integer
}
