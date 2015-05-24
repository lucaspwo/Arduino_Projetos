#include <Wire.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Wire.begin(4);
  Wire.onRequest(i2c_request);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  sensorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);      
  digitalWrite(ledPin, LOW);
  delay(sensorValue);                  
}

void i2c_request(void){
  Wire.write(sensorValue);
}
