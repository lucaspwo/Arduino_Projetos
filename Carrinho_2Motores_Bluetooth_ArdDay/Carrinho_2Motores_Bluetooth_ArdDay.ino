#include <SoftwareSerial.h>
#include <AFMotor.h>

#define tx  4
#define rx  2

SoftwareSerial bt(rx, tx);

AF_DCMotor motor1(2, MOTOR12_1KHZ);
AF_DCMotor motor2(3);

void setup(){
  bt.begin(115200);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  Serial.begin(9600);
}

void loop(){
  if(bt.available()){
    char c = (char)bt.read();
    if(c == '8'){
      Serial.println("8");
      motor1.setSpeed(150);
      motor2.setSpeed(150);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    }
    if(c == '0'){
      Serial.println("0");
      motor1.setSpeed(0);
      motor2.setSpeed(0);
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
    if(c == '2'){
      Serial.println("2");
      motor1.setSpeed(150);
      motor2.setSpeed(150);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
    }
    if(c == '4'){
      Serial.println("4");
      motor1.setSpeed(150);
      motor2.setSpeed(150);
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
    }
    if(c == '6'){
      Serial.println("6");
      motor1.setSpeed(150);
      motor2.setSpeed(150);
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
    }
  }
}
