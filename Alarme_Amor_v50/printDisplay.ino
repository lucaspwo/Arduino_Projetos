void printDisplay(String *hora, String *minuto, byte *diaDaSemana, String *diaDoMes, String *mes, byte *ano){      //funcao para exibir a data na tela
  lcd.clear();
  analogWrite(PWR, 255);      //mudanca do PWM para luz máxima
  lcd.setCursor(0,0);
  switch(*diaDaSemana){
    case 0:lcd.print("DOM, "); break;   
    case 1:lcd.print("SEG, "); break;
    case 2:lcd.print("TER, "); break; 
    case 3:lcd.print("QUA, "); break; 
    case 4:lcd.print("QUI, "); break;  
    case 5:lcd.print("SEX, "); break;   
    case 6:lcd.print("SAB, "); break; 
  }
  lcd.print(*diaDoMes);
  lcd.print(" ");
  if(*mes == "01"){
    lcd.print("JAN ");
  }
  if(*mes == "02"){
    lcd.print("FEV ");
  }
  if(*mes == "03"){
    lcd.print("MAR ");
  }
  if(*mes == "04"){
    lcd.print("ABR ");
  }
  if(*mes == "05"){
    lcd.print("MAI ");
  }
  if(*mes == "06"){
    lcd.print("JUN ");
  }
  if(*mes == "07"){
    lcd.print("JUL ");
  }
  if(*mes == "08"){
    lcd.print("AGO ");
  }
  if(*mes == "09"){
    lcd.print("SET ");
  }
  if(*mes == "10"){
    lcd.print("OUT ");
  }
  if(*mes == "11"){
    lcd.print("NOV ");
  }
  if(*mes == "12"){
    lcd.print("DEZ ");
  }
  lcd.print("20");
  lcd.print(*ano);
  lcd.setCursor(6,1);
  lcd.print(*hora);
  lcd.print(":");
  lcd.print(*minuto);
  delay(5000);              //espera 5 segundos
  analogWrite(PWR, 100);    //seta de volta a luz da tela para 100
  imprimeTela();            //chama a funcao para imprimir o status do alarme e a temperatura
}
