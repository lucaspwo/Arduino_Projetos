#include <OneWire.h>
/*#include <SoftwareSerial.h>

const int rxpin = 2;           // pin used to receive
const int txpin = 3;           // pin used to send to
SoftwareSerial Serial_2(rxpin, txpin);  // new serial port on given pins*/

// DS18S20 Temperature chip i/o
OneWire ds(9);  // on pin 10
float temp = 0;

void setup(void) {
  // initialize inputs/outputs
  // start serial port
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop(void) {
  int HighByte, LowByte, TReading, SignBit, Tc_100;
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      ds.reset_search();
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);         // start conversion, with parasite power on at the end

  delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  LowByte = data[0];
  HighByte = data[1];
  TReading = (HighByte << 8) + LowByte;
  SignBit = TReading & 0x8000;  // test most sig bit
  Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

  temp = float(Tc_100)/100;
  Serial.println(temp);
  Serial3.print(temp);
}
