#include <AFMotor.h>
#include <Servo.h>
//#define SENSORD 0
//#define SENSORE 2
#define BOTAO 7

AF_DCMotor motor(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm

//int valD = 0;
//int valE = 0;
int val = 0;
int cont = 0;
int pos = 93;

Servo mServo;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Motor test!");
  
  pinMode(BOTAO, INPUT);
  mServo.attach(10);
  motor.setSpeed(100);     // set the speed to 200/255
}

void loop() {
  //valE = analogRead(SENSORD);
  val = digitalRead(BOTAO);
  
  mServo.write(pos);  
  motor.run(FORWARD);
  delay(1000);
  
  if(val == HIGH)
  {
    Serial.println(val);
    //motor.setSpeed(0);
    //motor.run(FORWARD);
    motor.run(RELEASE);
    delay(200);
    for(cont = 1; cont < 11; cont++)
    {
      motor.setSpeed(100);
      motor.run(BACKWARD);
      delay(200);
      pos = 93 - cont;
      mServo.write(pos);
      delay(15);
    }
    motor.run(RELEASE);
    for(cont = 10; cont < 0; cont-- )
    {
      motor.setSpeed(100);
      motor.run(BACKWARD);
      delay(200);
      pos = 93 + cont;
      mServo.write(pos);
      delay(15);
    }
    //motor.setSpeed(0);
    //motor.run(FORWARD);
    motor.run(RELEASE);
  }
  
  //---------//
  /*val = analogRead(SENSOR);
  
  Serial.println(val/4);
  
  motor.setSpeed(val/4);
  
  delay(50);
  
  //Serial.print("tick");
  
  motor.run(FORWARD);      // turn it on going forward
  delay(1000);

  /*Serial.print("tock");
  motor.run(BACKWARD);     // the other way
  delay(1000);
  
  Serial.print("tack");
  motor.run(RELEASE);      // stopped
  delay(1000);*/
}
