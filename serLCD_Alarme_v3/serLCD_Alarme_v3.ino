#include <SoftwareSerial.h>
#include <serLCD.h>

#define up 10
#define dn 9
#define ctr 11

int pin = 2;
serLCD lcd(pin);

int Hor = 0;
int Min = 0;
int Seg = 0;
int h,m,s = 0;

boolean a = false;
boolean H = false, M = false, S = false;

void setup(){
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  lcd.clear();
  //Serial.begin(9600);
}

void loop(){
  if(a == false)
    iniciar();
  
  if(a == true){
    //Serial.println("Comecou");
    for(h = Hor; h > -1; h--){
      for(m = Min; m > -1; m--){
        for(s = Seg; s > -1; s--){
          lcd.clear();
          lcd.print(h);
          lcd.print("h ");
          lcd.print(m);
          lcd.print("m ");
          lcd.print(s);
          lcd.print("s");
          if(h == 0){
            if(m == 0){
              if(s == 0){
                for(;;)
                buzz();
              }
            }
          }
          delay(1000);
        }
        Seg = 59;
      }
      Min = 59;
    }
  }
}

void buzz(){
  lcd.clear();
  lcd.print("ACORDE!!!");
  //play tone
  tone(13,2999,800);// esta linha de código é usada especialmente para o buzzer
  //O seu funcionamento é : o pino, a frequência e o tempo de duração em milissegundos
  //delay (ms)
  delay(1000);
}

void iniciar(){
  //Serial.println("Entrei em a");
  while(H == false){
    lcd.clear();
    lcd.print(Hor);
    lcd.print("h ");
    lcd.print(Min);
    lcd.print("m ");
    lcd.print(Seg);
    lcd.print("s");
    if(digitalRead(up) == false){
      if(Hor == 24){
        Hor = 0;
      }
      else{
        Hor++;
      }
    }
    if(digitalRead(dn) == false){
      if(Hor == 0){
        Hor = 24;
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
    lcd.print(Hor);
    lcd.print("h ");
    lcd.print(Min);
    lcd.print("m ");
    lcd.print(Seg);
    lcd.print("s");
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
  while(S == false){
    lcd.clear();
    lcd.print(Hor);
    lcd.print("h ");
    lcd.print(Min);
    lcd.print("m ");
    lcd.print(Seg);
    lcd.print("s");
    if(digitalRead(up) == false){
      if(Seg == 59){
        Seg = 0;
      }
      else{
        Seg++;
      }
    }
    if(digitalRead(dn) == false){
      if(Seg == 0){
        Seg = 59;
      }
      else{
        Seg--;
      }
    }
    if(digitalRead(ctr) == false){
      S = true;
      //Serial.println("Setei o segundo");
    }
    delay(150);
  }
  a = true;
  return;
}
