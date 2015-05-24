#include <Wire.h>

const int pingPin = 7;
long duration, cm;

void setup(){
  Wire.begin(2);
  Wire.onRequest(i2c_request);
  Serial.begin(9600);
}

void loop(){
  ping();
  delay(100);
}

void ping(){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  cm = microsecondsToCentimeters(duration);
  Serial.println(cm);
}

long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}

void i2c_request(void){
  Wire.write(cm);
}
