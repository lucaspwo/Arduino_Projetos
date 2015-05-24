#include <Servo.h>

Servo myservo;

byte x, media;  // X and Y in-plane sensing
int pos = 0, i = 0;

void setup()
{
  Serial.begin(9600);      // sets the serial port to 9600
  myservo.attach(9);
}

void loop()
{
  for(i=0; i < 30; i++){
    x = analogRead(0);       // read analog input pin 0
    media = media + x;
  }
  media = media /30;
  if(x <= 255){
    x = x - 200;
  }
  Serial.print("x: ");
  Serial.println(x);    // print the rotational rate in the X axis
  pos = x;
  myservo.write(pos);
  delay(100);              // wait 100ms for next reading
}
