#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int val = 0;
int pval = 0;
int valM1 = 0;
int valM2 = 0;
int a = 1;
int but = 0;

void setup() {
  motor1.setSpeed(84);
  motor2.setSpeed(80);
  Serial.begin(9600);
}

void loop() {
    
  if(a == 1) {
    delay(2000);
  }
  a == 0;
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
 
  but = analogRead(1);
  if (but > 10) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(500);
    turn90(0);
    delay(100);
  }
  
  pval = analogRead(0);
  valM1 = valM1 + pval;
  pval = analogRead(0);
  valM1 = valM1 + pval;
  pval = analogRead(0);
  valM1 = valM1 + pval;
  pval = analogRead(0);
  valM1 = valM1 + pval;
  pval = analogRead(0);
  valM1 = valM1 + pval;
  valM1 = valM1/5;
  
  delay(500);
  
  val = analogRead(0);
  valM2 = valM2 + val;
  val = analogRead(0);
  valM2 = valM2 + val;
  val = analogRead(0);
  valM2 = valM2 + val;
  val = analogRead(0);
  valM2 = valM2 + val;
  val = analogRead(0);
  valM2 = valM2 + val;
  valM2 = valM2/5;
  
//  delay(100);
//  val = analogRead(0);
//  if (a == 1) {
//    pval = val;
//  }
  if (valM1 > valM2+10) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
    turn90(0);
    delay(100);
  }
  Serial.print("ValM1 = ");
  Serial.print(valM1);
  Serial.print("\n");
  Serial.print("ValM2 = ");
  Serial.print(valM2);
  Serial.print("\n");  
  
//  if (val > 349) {
//    motor1.run(RELEASE);
//    motor2.run(RELEASE);
//    delay(250);
//    turn90(0);
//    delay(100);
//  }
  delay(100);
  
  but = analogRead(1);
  if (but > 10) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(250);
    turn90(0);
    delay(100);
  }
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
