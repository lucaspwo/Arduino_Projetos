String checkHora(){
  String ajustaHora;
  Wire.beginTransmission(RTC);
  Wire.write((byte)0x00); 
  Wire.endTransmission();
  Wire.requestFrom(RTC, 7);
  byte segundo = bcdToDec(Wire.read() & 0x7f);
  byte minuto = bcdToDec(Wire.read());          
  byte hora = bcdToDec(Wire.read() & 0x3f);   
  byte diaDaSemana = bcdToDec(Wire.read());    
  byte diaDoMes = bcdToDec(Wire.read());       
  byte mes = bcdToDec(Wire.read());            
  byte ano = bcdToDec(Wire.read());
  ajustaHora += ajustaZero(hora);
  return(ajustaHora);
}

String checkMinuto(){
  String ajustaMinuto;
  Wire.beginTransmission(RTC);
  Wire.write((byte)0x00); 
  Wire.endTransmission();
  Wire.requestFrom(RTC, 7);
  byte segundo = bcdToDec(Wire.read() & 0x7f);
  byte minuto = bcdToDec(Wire.read());          
  byte hora = bcdToDec(Wire.read() & 0x3f);   
  byte diaDaSemana = bcdToDec(Wire.read());    
  byte diaDoMes = bcdToDec(Wire.read());       
  byte mes = bcdToDec(Wire.read());            
  byte ano = bcdToDec(Wire.read());
  ajustaMinuto += ajustaZero(minuto);
  return(ajustaMinuto);
}
