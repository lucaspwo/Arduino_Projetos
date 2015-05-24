#include <AFMotor.h>
#define CIRC 28 //circunferência de giro em centímetros!!!
#define SPD 13 //velocidade em cm/s

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int a=1;
char commands[] = {S, T, S, T, S, T, S, T};
int numDirections = 8; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(a==1){
    motor1.setSpeed(104);
    motor2.setSpeed(100);
    //delay(1000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(4000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(2000);
    //rotate(1,90,80);
    turn90(0);
    delay(1000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(4000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(2000);
    turn90(0);
    delay(1000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(4000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(2000);
    turn90(0);
    delay(1000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(4000);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(2000);
    turn90(0);
  }
  a=0;
}
    
//void rotate(int dir, float angle, int sped){
//  int time = 0;
//  float timer = 0;
//  Serial.print("Circ = ");
//  Serial.print(CIRC);
//  Serial.print("\n");
//  Serial.print("Spd = ");
//  Serial.print(SPD);
//  Serial.print("\n");
//  Serial.print("Angle = ");
//  Serial.print(angle);
//  Serial.print("\n");
//  timer = (CIRC*angle*1000)/(SPD*360);
//  Serial.print("Time R = ");
//  Serial.print(timer);
//  Serial.print("\n");
//  time = (int) timer;
//  //time = 500;
//  Serial.print("Time = ");
//  Serial.print(time);
//  Serial.print("\n");
//  motor1.setSpeed(sped);
//  motor2.setSpeed(sped);
//  if(dir == 0){
//    motor1.run(BACKWARD);
//    motor2.run(FORWARD);
//    delay(time);
//    motor1.run(RELEASE);
//    motor2.run(RELEASE);
//  }
//  if(dir == 1){
//    motor1.run(FORWARD);
//    motor2.run(BACKWARD);
//    delay(time);
//    motor1.run(RELEASE);
//    motor2.run(RELEASE);
//  }
//}

void turn90(int dir){
  int time = 750;
  float timer = 0;
  //timer = (CIRC*angle*1000)/(SPD*360);
  //time = (int) timer;
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
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
}
