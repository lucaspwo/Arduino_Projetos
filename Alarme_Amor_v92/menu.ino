void menu(){
  boolean alarme_menu = false, data_menu = false, set = false;
  int cont_menu = 1;
  analogWrite(PWR, 255);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write((uint8_t)1);
  lcd.write("Config. alarme?");
  lcd.setCursor(0,1);
  lcd.write(" Config. data?");
  alarme_menu = true;
  data_menu = false;
  while(set == false){
    if(cont_menu == 25){
      analogWrite(PWR, 100);
      imprimeTela();
      return;
    }
    if(digitalRead(PCI) == false || digitalRead(PBA) == false){
      muda(&alarme_menu, &data_menu);
      cont_menu = 1;
    }
    if(digitalRead(ENT) == false){
      set = true;
    }
    cont_menu++;
    delay(200);
  }
  if(alarme_menu == true && data_menu == false){
    confAlarme();
  }
  if(alarme_menu == false && data_menu == true){
    confData();
  }
}

void muda(boolean *alarme, boolean *data){
  if(*alarme == true && *data == false){
    *alarme = false;
    *data = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.write(" Config. alarme?");
    lcd.setCursor(0,1);
    lcd.write((uint8_t)1);
    lcd.write("Config. data?");
    return;
  }
  if(*alarme == false && *data == true){
    *alarme = true;
    *data = false;
    lcd.clear();
    lcd.setCursor(0,0);    
    lcd.write((uint8_t)1);
    lcd.write("Config. alarme?");
    lcd.setCursor(0,1);
    lcd.write(" Config. data?");
    return;
  }
}
