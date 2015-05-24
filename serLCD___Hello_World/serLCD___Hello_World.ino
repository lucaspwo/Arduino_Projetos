/*
  serLCD - Hello World Example
*/
#include <SoftwareSerial.h>
#include <serLCD.h>

#define up 9
#define ctr 11
#define lt 12
#define dn 13
#define rt 8

// Set pin to the LCD's rxPin
int pin = 2;

serLCD lcd(pin);

void setup()
{
  pinMode(up, INPUT);
  pinMode(ctr, INPUT);
  pinMode(lt, INPUT);
  pinMode(dn, INPUT);
  pinMode(rt, INPUT);
}

void loop()
{
  if(digitalRead(up) == false)
  {
    lcd.clear();
    lcd.print("To the cima");
  }
  if(digitalRead(ctr) == false)
  {
    lcd.clear();
    lcd.print("To the midou");
  }
  if(digitalRead(lt) == false)
  {
    lcd.clear();
    lcd.print("To the lefiti");
  }
  if(digitalRead(dn) == false)
  {
    lcd.clear();
    lcd.print("To the baixo");
  }
  if(digitalRead(rt) == false)
  {
    lcd.clear();
    lcd.print("To the raite");
  }
}
