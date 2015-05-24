#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);

int a = 1;
int bot = 0;
int val = 0;
int valA1 = 0;
int valA2 = 0;
int crsh = 0;
int dntcrsh = 0;
int contE = 1;
int contD = 1;

void setup(){
  motor1.setSpeed(84);
  motor2.setSpeed(80);
  Serial.begin(9600);
}

void loop(){
  
  if(a == 1) {
    delay(2000);
  }
  a = 0;
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
//  delay(100);
  
  bot = analogRead(1);
  if(bot > 10){
    Serial.println("CRASH - bot");
    crash(); 
  }
  
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  valA1 = valA1/5;
  Serial.print("valA1 = ");
  Serial.print(valA1);
  Serial.print("\n");
  
  delay(500);
  
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  valA2 = valA2/5;
  Serial.print("valA2 = ");
  Serial.print(valA2);
  Serial.print("\n");
  
  bot = analogRead(1);
  if(bot > 10){
    Serial.println("CRASH - bot");
    crash();  
  }
  
  val = analogRead(0);
  
  if(val > 349){
    Serial.println("CRASH - val");
    crash();
  }
  
  if(valA1 > valA2+20){
    crsh = crsh + 1;
    
    if(crsh > 4){
      Serial.println("CRASH - valA");
      crash;
      crsh = 0;
    }
    
   }
   
   else{
     dntcrsh = dntcrsh + 1;
     
     if(dntcrsh > 4){
       crsh = 0;
     }
     
   }
  
  bot = analogRead(1);
  if(bot > 10){
    Serial.println("CRASH - bot");
    crash();  
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
    contD = contD + 1;
    contE = 1;
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
    contE = contE + 1;
    contD = 1;
  }
  if(dir == 2){
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(time*2);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  } 
}

void crash(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE); 
  if((contE < 4) && (contD < 4)){ 
    if(random(1, 11) == 5){
      turn90(2);
    }
    else{
      turn90(random(0,2));
    }
  }
  if(contE == 4){
    turn90(0);
    contE = 1;
  }
  if(contD == 4){
    turn90(1);
    contD = 1;
  }
}
