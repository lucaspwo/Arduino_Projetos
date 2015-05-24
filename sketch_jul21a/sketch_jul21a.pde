#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int val = 0;
int a = 1;
int but = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  motor1.setSpeed(84);
  motor2.setSpeed(80);
  
  if(a == 1) {
    delay(2000);
  }
  a == 0;
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
 
  but = analogRead(1);
  val = analogRead(0);
  Serial.println(val);
  
  if (but > 10) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(1000);
    turn90(0);
    delay(250);
  }
  
  if (val > 349) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
    turn90(0);
    delay(250);
  }
  delay(250);
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
