#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);

int val = 0;
int cont = 0;

void setup() {
  Serial.begin(9600); 
  motor1.setSpeed(100);
  motor2.setSpeed(100);
}

void loop() {
  val = analogRead(0);
  Serial.println(val);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(250);
  
  if(val > 0)
  {
    Serial.println(val);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(15);
    
    for(cont = 0; cont < 2; cont++)
    {
      Serial.println("Entrei no primeiro FOR");     
      motor1.setSpeed(50);
      motor2.setSpeed(100);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(250);
    }
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(15);
    
    for(cont = 0; cont < 2; cont++)
    {
      Serial.println("Entrei no segundo FOR");
      motor1.setSpeed(100);
      motor2.setSpeed(100);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(500);
    }
    
    
    for(cont = 0; cont < 2; cont++)
    {
      Serial.println("Entrei no terceiro FOR");
      motor1.setSpeed(100);
      motor2.setSpeed(50);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      delay(250);
    }
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor1.setSpeed(100);
    motor2.setSpeed(100);
    delay(15);
  }
}
