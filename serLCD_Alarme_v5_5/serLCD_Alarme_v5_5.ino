#include <SoftwareSerial.h>
#include <serLCD.h>

#define up 10
#define dn 9
#define ctr 11

int pin = 2;
serLCD lcd(pin);

int Hor = 0, Min = 0;
int Hor2 = 0, Min2 = 0, Seg2 = 0;
int h,m,s = 0;

boolean alarme = false, hora = false;
boolean H = false, M = false, S = false;
boolean H2 = false, M2 = false, S2 = false;

void setup(){
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  lcd.clear();
  Serial.begin(9600);
}

void loop(){
  if(hora == false)
    iniciar0();
  
  if(alarme == false)
    iniciar();
  
  if(alarme == true && hora == true){
    //Serial.println("Comecou");
    lcd.clear();
    lcd.print("Alarme ligado:  ");
    if(Hor < 10){
      lcd.print("0");
      lcd.print(Hor);
    }else{
      lcd.print(Hor);
    }
    lcd.print("h");
    if(Min < 10){
      lcd.print("0");
      lcd.print(Min);
    }else{
      lcd.print(Min);
    }
    contador();
  }
}

void contador(){
  for(h = Hor2; ; h++){
        if(h == 24){
          Hor2 = 0;
          h = 0;
        }
    for(m = Min2; ; m++){
        if(m == 60){
          Min2 = 0;
          break;
        }
      for(s = Seg2; ; s++){
        if(s == 60){
          Seg2 = 0;
          break;
        }
        Serial.print(h);
        Serial.print(":");
        Serial.print(m);
        Serial.print(":");
        Serial.print(s);
        Serial.println();
        if(h == Hor && m == Min){
          buzz();
          reseta();
          return;
        }
        delay(1000);
      }
    }
  }
}

void reseta(){
  alarme = false;
  hora = false;
  H = false;
  M = false;
  S = false;
  H2 = false;
  M2 = false;
  S2 = false;
  return;
}

void buzz(){
  lcd.clear();
  lcd.print("ACORDE!!!");
  //play tone
  //tone(13,2999,800);// esta linha de código é usada especialmente para o buzzer
  //O seu funcionamento é : o pino, a frequência e o tempo de duração em milissegundos
  //delay (ms)
  for(int j = 0; j < 10; j++){
    tone(13,2999,80);
    if(digitalRead(up) == false || digitalRead(dn) == false || digitalRead(ctr) == false){
      return;
    }
    delay(120);
    tone(13,2999,80);
    if(digitalRead(up) == false || digitalRead(dn) == false || digitalRead(ctr) == false){
      return;
    }
    delay(120);
    tone(13,2999,80);
    if(digitalRead(up) == false || digitalRead(dn) == false || digitalRead(ctr) == false){
      return;
    }
    delay(120);
    tone(13,2999,80);
    if(digitalRead(up) == false || digitalRead(dn) == false || digitalRead(ctr) == false){
      return;
    }
    delay(1000);
  }
  for(int j = 0; j < 15; j++){
    tone(13,2999,500);
    if(digitalRead(up) == false || digitalRead(dn) == false || digitalRead(ctr) == false){
      return;
    }
    delay(1000);
  }
  return;
}

void iniciar0(){
  //Serial.println("Entrei em iniciar0");
  while(H2 == false){
    lcd.clear();
    lcd.print("Que hora e?     ");
    lcd.print("Hora: ");
    lcd.print(Hor2);
    if(digitalRead(up) == false){
      if(Hor2 == 23){
        Hor2 = 0;
      }
      else{
        Hor2++;
      }
    }
    if(digitalRead(dn) == false){
      if(Hor2 == 0){
        Hor2 = 23;
      }
      else{
        Hor2--;
      }
    }
    if(digitalRead(ctr) == false){
      H2 = true;
      //Serial.println("Setei a hora");
    }
    delay(150);
  }
  while(M2 == false){
    lcd.clear();
    lcd.print("Que hora e?     ");
    lcd.print("Minuto: ");
    lcd.print(Min2);
    if(digitalRead(up) == false){
      if(Min2 == 59){
        Min2 = 0;
      }
      else{
        Min2++;
      }
    }
    if(digitalRead(dn) == false){
      if(Min2 == 0){
        Min2 = 59;
      }
      else{
        Min2--;
      }
    }
    if(digitalRead(ctr) == false){
      M2 = true;
      //Serial.println("Setei o minuto");
    }
    delay(150);
  }
  while(S2 == false){
    lcd.clear();
    lcd.print("Que hora e?     ");
    lcd.print("Segundo: ");
    lcd.print(Seg2);
    if(digitalRead(up) == false){
      if(Seg2 == 59){
        Seg2 = 0;
      }
      else{
        Seg2++;
      }
    }
    if(digitalRead(dn) == false){
      if(Seg2 == 0){
        Seg2 = 59;
      }
      else{
        Seg2--;
      }
    }
    if(digitalRead(ctr) == false){
      S2 = true;
      //Serial.println("Setei o segundo");
    }
    delay(150);
  }
  hora = true;
  return;
}

void iniciar(){
  //Serial.println("Entrei em iniciar");
  while(H == false){
    lcd.clear();
    lcd.print("Alarme:         ");
    lcd.print("Hora: ");
    lcd.print(Hor);
    if(digitalRead(up) == false){
      if(Hor == 23){
        Hor = 0;
      }
      else{
        Hor++;
      }
    }
    if(digitalRead(dn) == false){
      if(Hor == 0){
        Hor = 23;
      }
      else{
        Hor--;
      }
    }
    if(digitalRead(ctr) == false){
      H = true;
      //Serial.println("Setei a hora");
    }
    delay(150);
  }
  while(M == false){
    lcd.clear();
    lcd.print("Alarme:         ");
    lcd.print("Minuto: ");
    lcd.print(Min);
    if(digitalRead(up) == false){
      if(Min == 59){
        Min = 0;
      }
      else{
        Min++;
      }
    }
    if(digitalRead(dn) == false){
      if(Min == 0){
        Min = 59;
      }
      else{
        Min--;
      }
    }
    if(digitalRead(ctr) == false){
      M = true;
      //Serial.println("Setei o minuto");
    }
    delay(150);
  }
  alarme = true;
  return;
}
