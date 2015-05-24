#include <AFMotor.h>
#include <Servo.h>
//#define SENSORD 0
//#define SENSORE 2
//#define BOTAO 7

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #1, 64KHz pwm

//int valD = 0;
//int valE = 0;
int val = 0;
int cont = 0;
int pos = 93;

Servo mServo;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Motor test!");
  
  //pinMode(BOTAO, INPUT);
  mServo.attach(10);
  motor1.setSpeed(50);     // set the speed to 200/255
  motor2.setSpeed(50);     // set the speed to 200/255

}

void loop() {
  //valE = analogRead(SENSORD);
  val = analogRead(0);
  
  mServo.write(pos);  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(1000);
  
  Serial.println(val);
  
  if(val > 0)
  {
    Serial.println(val);
    //motor.setSpeed(0);
    //motor.run(FORWARD);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    
    delay(200);
    motor1.setSpeed(50);
    motor2.setSpeed(50);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    delay(200);
    for(cont = 1; cont < 41; cont++)
    {
      motor1.setSpeed(50);
      motor2.setSpeed(25);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(15);
      pos = 93 - cont;
      mServo.write(pos);
      delay(15);
    }
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    for(cont = 1; cont < 41; cont++ )
    {
      motor1.setSpeed(50);
      motor1.run(BACKWARD);
      motor2.setSpeed(50);
      motor2.run(BACKWARD);
      delay(15);
      pos = 53 + cont;
      mServo.write(pos);
      delay(15);
    }
    //motor.setSpeed(0);
    //motor.run(FORWARD);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
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
