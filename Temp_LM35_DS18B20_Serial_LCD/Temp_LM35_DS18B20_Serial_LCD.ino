#include <SoftwareSerial.h>
#include <serLCD.h>

const int rxpin = 3;           // pin used to receive
const int txpin = 4;           // pin used to send to
SoftwareSerial Serial_2(rxpin, txpin);  // new serial port on given pins

int pin = 2;
serLCD lcd(pin);

int a;
float b;

void setup(){
  Serial_2.begin(9600);
  Serial.begin(9600);
  lcd.clear();
}

void loop(){
  lcd.clear();
  a = analogRead(0);
  b = (0.00488*a);
  b = b*100;
  lcd.print("T: ");
  lcd.print(b);
  lcd.print(" ");
  while(Serial_2.available()){
    char c = (char)Serial_2.read();
    lcd.print(c);
  }
  Serial.println(b);
  delay(900);
}
