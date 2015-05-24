void apita(){
  if(toca == false){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bom dia, flor do");
    lcd.setCursor(0,1);
    lcd.print("    dia!  =)    ");
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
    }
    for(;;){
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
    }
    imprimeTela();
    return;
  }
}
