#include <SoftwareSerial.h>

#define txPin 2

SoftwareSerial lcd = SoftwareSerial(0, txPin);

const int LCDdelay=10;

void goTo(int row, int col) {
  lcd.write(0xFE);   //command flag
  lcd.write(col + row*64 + 128);    //position 
  delay(LCDdelay);
}

void boxcursorOn(){
  lcd.write(0xFE);
  lcd.write(0x0D);
  delay(LCDdelay);
}

void boxcursorOff(){
  lcd.write(0xFE);
  lcd.write(0x0C);
  delay(LCDdelay);
}

void underlinecursorOn(){
  lcd.write(0xFE);
  lcd.write(0x0E);
  delay(LCDdelay);
}

void underlinecursorOff(){
  lcd.write(0xFE);
  lcd.write(0x0C);
  delay(LCDdelay);
}

void splashToggle(){
  lcd.write(0x7C);
  lcd.write(0x09);
  delay(LCDdelay);
}

void clearLCD(){
  lcd.write(0xFE);   //command flag
  lcd.write(0x01);   //clear command.
  delay(LCDdelay);
}

void setSplash(){
  lcd.write(0x7C);
  lcd.write(0x0A);
  delay(LCDdelay);
}

void setup()
{
  Serial.begin(9600);
  pinMode(txPin, OUTPUT);
  lcd.begin(9600);
  clearLCD();
  goTo(0,0);
  //lcd.print("teste");
  //underlinecursorOff();
  //boxcursorOn();
  //goTo(1,1);
  //lcd.print("Lucas Oliveira");
  //goTo(1,3);
  //lcd.print("ARDUINAGEM");
  //setSplash();
  //splashToggle();
}

void loop()
{
  if(Serial.available()){
    int i = (int)Serial.read();
    if(i == '1'){
      clearLCD();
      boxcursorOn();
    }
    if(i == '2'){
      boxcursorOff();
      goTo(0,1);
      lcd.print("Lucas Oliveira");
      goTo(1,3);
      lcd.print("ARDUINAGEM");
    }
    if(i == '3'){
      setSplash();
    }
    if(i == '4'){
      splashToggle();
    }
    if(i == '5'){
      clearLCD();
      underlinecursorOn();
    }
  }
}
