void imprimeTela(){                //funcao para imprimir na tela o alarme e a temperatura
  float temp = checkTemp();        //pega a temperatura do sensor
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alarme: ");
  checkAlarm();                    //verifica se o alarme esta ativado
  if(alarme == false){
    lcd.print("DESLIG.");
  }
  if(alarme == true){              //se o alarme esta setado, pega da memoria o valor armazenado do alarme
    Wire.beginTransmission(ROM);
    Wire.write(0x00);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(10);
    Wire.requestFrom(ROM, 3);
    byte dado1 = Wire.read();      //faz leitura em serie de 3 dados. dado1 = lixo, dado2 = hora, dado3 = minuto
    dado2 = Wire.read();
    dado3 = Wire.read();
    delay(10);
    Wire.endTransmission();
    if((int)dado2 < 10)
      lcd.print("0");
    lcd.print((int)dado2);
    lcd.print("h");
    if((int)dado3 < 10)
      lcd.print("0");
    lcd.print((int)dado3);
  }
  lcd.setCursor(0,1);
  lcd.print("Temp.:  ");
  lcd.print(temp,1);
  lcd.write((uint8_t)0);
  lcd.print("C");
}
