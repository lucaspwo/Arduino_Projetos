void confData(){
  Wire.beginTransmission(RTC);
  Wire.write((byte)0x00); 
  Wire.endTransmission();
  Wire.requestFrom(RTC, 7);
  segundo = bcdToDec(Wire.read() & 0x7f);
  minuto = bcdToDec(Wire.read());          
  hora = bcdToDec(Wire.read() & 0x3f);   
  diaDaSemana = bcdToDec(Wire.read());    
  diaDoMes = bcdToDec(Wire.read());       
  mes = bcdToDec(Wire.read());            
  ano = bcdToDec(Wire.read());
  
  boolean segData = false, minData = false, horData = false, ddSemanaData = false, ddMesData = false, mesData = false, anoData = false;
  int Hora = hora, Min = minuto, Seg = segundo, ddSemana = diaDaSemana, ddMes = diaDoMes, Mes = mes, Ano = ano;
  
  analogWrite(PWR, 255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Config. data");
  delay(2000);
  
  while(horData == false){
    lcd.clear();
    lcd.print("Hora: ");
    lcd.print(Hora);
    if(digitalRead(PCI) == false){
      if(Hora == 23){
        Hora = 0;
      }
      else{
        Hora++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Hora == 0){
        Hora = 23;
      }
      else{
        Hora--;
      }
    }
    if(digitalRead(ENT) == false){
      horData = true;
    }
    delay(200);
  }
  
  while(minData == false){
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
      minData = true;
    }
    delay(200);
  }
  
  while(segData == false){
    lcd.clear();
    lcd.print("Segundo: ");
    lcd.print(Seg);
    if(digitalRead(PCI) == false){
      if(Seg == 59){
        Seg = 0;
      }
      else{
        Seg++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Seg == 0){
        Seg = 59;
      }
      else{
        Seg--;
      }
    }
    if(digitalRead(ENT) == false){
      segData = true;
    }
    delay(200);
  }
  
  while(ddSemanaData == false){
    lcd.clear();
    lcd.print("Dia da semana: ");
    lcd.setCursor(0,1);
    switch(ddSemana){
      case 0:lcd.print("DOM"); break;   
      case 1:lcd.print("SEG"); break;
      case 2:lcd.print("TER"); break; 
      case 3:lcd.print("QUA"); break; 
      case 4:lcd.print("QUI"); break;  
      case 5:lcd.print("SEX"); break;   
      case 6:lcd.print("SAB"); break; 
    }
    if(digitalRead(PCI) == false){
      if(ddSemana == 6){
        ddSemana = 0;
      }
      else{
        ddSemana++;
      }
    }
    if(digitalRead(PBA) == false){
      if(ddSemana == 0){
        ddSemana = 6;
      }
      else{
        ddSemana--;
      }
    }
    if(digitalRead(ENT) == false){
      ddSemanaData = true;
    }
    delay(200);
  }
  
  while(ddMesData == false){
    lcd.clear();
    lcd.print("Dia do mes: ");
    lcd.print(ddMes);
    if(digitalRead(PCI) == false){
      if(ddMes == 31){
        ddMes = 1;
      }
      else{
        ddMes++;
      }
    }
    if(digitalRead(PBA) == false){
      if(ddMes == 1){
        ddMes = 31;
      }
      else{
        ddMes--;
      }
    }
    if(digitalRead(ENT) == false){
      ddMesData = true;
    }
    delay(200);
  }
  
  while(mesData == false){
    lcd.clear();
    lcd.print("Mes: ");
    lcd.print(Mes);
    if(digitalRead(PCI) == false){
      if(Mes == 12){
        Mes = 1;
      }
      else{
        Mes++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Mes == 1){
        Mes = 12;
      }
      else{
        Mes--;
      }
    }
    if(digitalRead(ENT) == false){
      mesData = true;
    }
    delay(200);
  }
  
  while(anoData == false){
    lcd.clear();
    lcd.print("Ano: ");
    lcd.print(Ano);
    if(digitalRead(PCI) == false){
      if(Ano == 99){
        Ano = 0;
      }
      else{
        Ano++;
      }
    }
    if(digitalRead(PBA) == false){
      if(Ano == 0){
        Ano = 99;
      }
      else{
        Ano--;
      }
    }
    if(digitalRead(ENT) == false){
      anoData = true;
    }
    delay(200);
  }
  
  Wire.beginTransmission(RTC); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00);   //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.write(decToBcd((byte)Seg));      //convertendo os segundos.
  Wire.write(decToBcd((byte)Min));       //convertendo os minutos.
  Wire.write(decToBcd((byte)Hora));         //convertendo as horas.
  Wire.write(decToBcd((byte)ddSemana));  //dia da semana, onde o domingo começa com "0".
  Wire.write(decToBcd((byte)ddMes));     //convertendo o dia do mês.
  Wire.write(decToBcd((byte)Mes));          //convertendo o mês.
  Wire.write(decToBcd((byte)Ano));          //convertendo o ano.
  Wire.endTransmission();             //finalizando o modo de gravação.
  lcd.clear();
  lcd.print("Data definida");
  delay(2000);
  analogWrite(PWR, 100);
  imprimeTela();
}
