#include <Wire.h>

int val;

void setup(){
  Wire.begin(3);
  Wire.onRequest(i2c_request);
}

void loop(){
  val = analogRead(0);
  delay(150);
}

void i2c_request(void){
  Wire.write(val);
}
