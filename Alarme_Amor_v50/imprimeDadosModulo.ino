void imprimeDadosModulo(){
  String ajustaSegundo;
  String ajustaMinuto;
  String _ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  Wire.beginTransmission(RTC);
  Wire.write((byte)0x00); 
  Wire.endTransmission();
  Wire.requestFrom(RTC, 7);
  segundo = bcdToDec(Wire.read() & 0x7f); 
  _minuto = minuto;
  minuto = bcdToDec(Wire.read());          
  hora = bcdToDec(Wire.read() & 0x3f);   
  diaDaSemana = bcdToDec(Wire.read());    
  diaDoMes = bcdToDec(Wire.read());       
  mes = bcdToDec(Wire.read());            
  ano = bcdToDec(Wire.read());            
  ajustaHora += ajustaZero(hora);
  ajustaMinuto += ajustaZero(minuto);
  if(alarme == true)
    compara(&ajustaHora, &ajustaMinuto);
  ajustaSegundo += ajustaZero(segundo);
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  ajustaMes += ajustaZero(mes);
  if(alarme == true)
    compara(&ajustaHora, &ajustaMinuto);
  if((digitalRead(HOR) == false)){
    printDisplay(&ajustaHora, &ajustaMinuto, &diaDaSemana, &ajustaDiaDoMes, &ajustaMes, &ano);
  }
  if((digitalRead(CAL) == false)){
    confAlarme();
  }
  if((digitalRead(LDA) == false)){
    Wire.beginTransmission(ROM);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(10);
    Wire.requestFrom(ROM, 1);
    delay(10);
    byte data = Wire.read();
    delay(10);
    Wire.endTransmission();
    if((int)data == 65){
      analogWrite(PWR, 255);
      lcd.clear();
      lcd.print("Alarme LIGADO");
      Wire.beginTransmission(ROM);
      Wire.write(0x00);
      Wire.write(0x00);
      Wire.write((byte)66);
      delay(10);
      Wire.endTransmission();
    }
    if((int)data == 66){
      analogWrite(PWR, 255);
      lcd.clear();
      lcd.print("Alarme DESLIGADO");
      Wire.beginTransmission(ROM);
      Wire.write(0x00);
      Wire.write(0x00);
      Wire.write((byte)65);
      delay(10);
      Wire.endTransmission();
    }
    delay(2000);
    analogWrite(PWR, 100);
    imprimeTela();
  }
  if(alarme == true)
    compara(&ajustaHora, &ajustaMinuto);
  if(minuto != _minuto){
    toca = false;
    imprimeTela();
  }
}
