#include <SoftwareSerial.h>
//#include <serLCD.h>

#define txPin 2

//int pin = 2;

//serLCD visor(pin);

SoftwareSerial lcd = SoftwareSerial(0, txPin);
// since the LCD does not send data back to the Arduino, we should only define the txPin
const int LCDdelay=10;  // conservative, 2 actually works

// wbp: goto with row & column
void goTo(int row, int col) {
  lcd.write(0xFE);   //command flag
  lcd.write(col + row*64 + 128);    //position 
  delay(LCDdelay);
}
void clearLCD(){
  lcd.write(0xFE);   //command flag
  lcd.write(0x01);   //clear command.
  delay(LCDdelay);
}
void backlightOn() {  //turns on the backlight
  lcd.write(0x7C);   //command flag for backlight stuff
  lcd.write(157);    //light level.
  delay(LCDdelay);
}
void backlightOff(){  //turns off the backlight
  lcd.write(0x7C);   //command flag for backlight stuff
  lcd.write(128);     //light level for off.
  delay(LCDdelay);
}
void cursorOn(){
  lcd.write(0xFE);
  lcd.write(0x0D);
  delay(LCDdelay);
}
void cursorOff(){
  lcd.write(0xFE);
  lcd.write(0x0C);
  delay(LCDdelay);
}
void lcdWide(){
  lcd.write(0x7C);
  lcd.write(0x04);
}
void lcdLines(){
  lcd.write(0x7C);
  lcd.write(0x06);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  Serial.write(0xFE);
}

void setup()
{
  pinMode(txPin, OUTPUT);
  lcd.begin(9600);
  clearLCD();
  goTo(0,0);
  //cursorOff();
  //goTo(1,1);
  lcd.print("Mrs Janet Long!!!");
}

void loop()
{
  /*visor.clear();
  visor.print("1234567890123456");
  while(1);*/
}
