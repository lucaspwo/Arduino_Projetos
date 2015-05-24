void checkAlarm(){                  //verifica se o alarme esta ativo ou nao
  Wire.beginTransmission(ROM);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(ROM, 1);
  delay(10);
  byte data = Wire.read();
  if((int)data == 65)
    alarme = false;
  if((int)data == 66)
    alarme = true;
}
