void confAlarme(){                //configuracao do alarme
  Wire.beginTransmission(ROM);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(ROM, 3);
  byte dado1 = Wire.read();
  dado2 = Wire.read();
  dado3 = Wire.read();
  delay(10);
  Wire.endTransmission();
  
  boolean H = false; boolean M = false;
  int Hor = (int)dado2, Min = (int)dado3;
  analogWrite(PWR, 255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Config. alarme");
  delay(2000);
  
  while(H == false){
    lcd.clear();
    lcd.print("Hora: ");
    lcd.print(Hor);
    if(digitalRead(PCI) == false){
      if(Hor == 23){
        Hor = 0;
      }
      else{
        Hor++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Hor == 0){
        Hor = 23;
      }
      else{
        Hor--;
      }
    }
    if(digitalRead(ENT) == false){
      H = true;
    }
    delay(200);
  }
  while(M == false){
    lcd.clear();
    lcd.print("Minuto: ");
    lcd.print(Min);
    if(digitalRead(PCI) == false){
      if(Min == 59){
        Min = 0;
      }
      else{
        Min++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Min == 0){
        Min = 59;
      }
      else{
        Min--;
      }
    }
    if(digitalRead(ENT) == false){
      M = true;
    }
    delay(200);
  }
  
  Wire.beginTransmission(ROM);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write((byte)66);
  Wire.write((byte)Hor);
  Wire.write((byte)Min);
  delay(10);
  Wire.endTransmission();
  lcd.clear();
  lcd.print("Alarme definido");
  zzz = 0;
  delay(2000);
  analogWrite(PWR, 100);
  imprimeTela();
}
