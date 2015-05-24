#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int a = 1;
int commands[] = {1, 2, 1, 2, 1, 2, 1, 2};
int numCommands = 8; 

void setup() {
  int cont;
  Serial.begin(9600);
}

void loop() {
  if(a == 1){
    for (int cont = 0; cont < numCommands; cont++) {
     switch(commands[cont]) {
       case 1:
         straight(100);
       case 2:
         turn90(0);
         delay(1000);
     }
//     straight(100);
//     turn90(0);
//     delay(1000);
//     straight(100);
//     turn90(0);
//     delay(1000);
//     straight(100);
//     turn90(0);
//     delay(1000);
    }
  }
  a = 0;
}

void straight(int vel){
  motor1.setSpeed(vel+4);
  motor2.setSpeed(vel);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(4000);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(500);
}

void turn90(int dir){
  int time = 750;
  float timer = 0;
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  if(dir == 0){
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(time);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
  if(dir == 1){
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(time);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
}
