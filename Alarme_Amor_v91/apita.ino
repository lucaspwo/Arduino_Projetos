void apita(){
  if(toca == false){
    lcd.clear();
    lcd.setCursor(6,0);
    String hora = checkHora();
    String minuto = checkMinuto();
    lcd.print(hora);
    lcd.print("h");
    lcd.print(minuto);
    lcd.setCursor(0,1);
    lcd.print("Hora de levantar");
    
    for(int j = 0; j < 10; j++){
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      tone(BUZ,2999,80);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      delay(120);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      tone(BUZ,2999,80);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      delay(120);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      tone(BUZ,2999,80);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      delay(120);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      tone(BUZ,2999,80);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      delay(1000);
      
      lcd.clear();
      lcd.setCursor(6,0);
      String hora = checkHora();
      String minuto = checkMinuto();
      lcd.print(hora);
      lcd.print("h");
      lcd.print(minuto);
      lcd.setCursor(0,1);
      lcd.print("Hora de levantar");
    }
    for(int j = 0; j < 30; j++){
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      tone(BUZ,2999,500);
      if(digitalRead(ENT) == false || digitalRead(PCI) == false || digitalRead(PBA) == false || digitalRead(HOR) == false || digitalRead(CAL) == false || digitalRead(LDA) == false){
        toca = true;
        return;
      }
      delay(1000);
      
      lcd.clear();
      lcd.setCursor(6,0);
      String hora = checkHora();
      String minuto = checkMinuto();
      lcd.print(hora);
      lcd.print("h");
      lcd.print(minuto);
      lcd.setCursor(0,1);
      lcd.print("Hora de levantar");
    }
    toca = true;
    return;
  }
}
