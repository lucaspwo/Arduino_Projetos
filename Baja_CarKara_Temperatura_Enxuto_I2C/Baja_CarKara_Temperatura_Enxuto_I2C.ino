#include <OneWire.h>
#include <Wire.h>

OneWire  ds(10);

float celsius;

void setup() {
  Wire.begin(5);
  Wire.onRequest(i2c_request);
}

void loop() {
  temp();
  delay(200);
}

void temp(){
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  
  delay(800);
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;
    else if (cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  celsius = (float)raw / 16.0;
}

void i2c_request(void){
  Wire.write((byte)celsius);
}
