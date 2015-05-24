#include <Wire.h>

void setup(){
  Wire.begin();
  Serial.begin(9600);
}

void loop(){
  request_2();
  request_3();
  request_4();
  delay(250);  
}

void request_2(){
  long c;
  Wire.requestFrom(2, 1);
  while(Wire.available() > 0){
    c = Wire.read();
  }
  Wire.endTransmission();
  Serial.print("Do slave 2: ");
  Serial.println(c);
  //Serial.println();
}

void request_3(){
  int c;
  Wire.requestFrom(3, 1);
  while(Wire.available() > 0){
    c = Wire.read();
  }
  Serial.print("Do slave 3: ");
  Serial.println(c);
}

void request_4(){
  int c;
  Wire.requestFrom(4, 1);
  while(Wire.available() > 0){
    c = Wire.read();
  }
  Serial.print("Do slave 4: ");
  Serial.println(c);
}
