#include <Wire.h>
#define address 0x50

const int val = 26;
byte data;

void setup()
{ 
 Wire.begin();
 Serial.begin(9600);
 delay(1000); 

 //WRITE!!!!*******************************
 Serial.println("Writing to EEPROM:");
 Wire.beginTransmission(address);
 Wire.write(0x00);
 Wire.write(0x00);

 for(byte i=0; i<val; i++)      //Write 26 data bytes
 {
   Wire.write(i+65);    
   Serial.write(i+65);
   Serial.println();
 }
 delay(10);
 Serial.println();

 Wire.endTransmission();
 delay(10);

 //READ!!!!*********************************
 Serial.println("Reading from EEPROM:");
 Wire.beginTransmission(address);
 Wire.write(0x00);
 Wire.write(0x00);
 Wire.endTransmission();
 delay(10);

 Wire.requestFrom(address, val);
 delay(10);

 for(byte i=0; i<val; i++)      //Read 26 data bytes
 {
   data = Wire.read();
   Serial.write(data);
   Serial.println();
 }
 delay(10);
}

void loop()
{
}