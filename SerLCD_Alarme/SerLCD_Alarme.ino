#include <SoftwareSerial.h>
#include <serLCD.h>

#define up 11
#define ctr 12
#define dn 9

int pin = 2;

serLCD lcd(pin);

int Hor = 1;
int Seg = 5;
int Min = 0;
int CTR,CTR2 = 0;
int h,m,s,a = 0;
boolean b = false;

void setup(){
  Serial.begin(9600);
  pinMode(up, INPUT);
  pinMode(ctr, INPUT);
  pinMode(dn, INPUT);
  pinMode(13,OUTPUT);//define o pino 13 do arduino como saida digital
  lcd.clear();
}

void loop(){ 
  while(a == 0){
    Config();
    a++;
  }
  
  for(h = Hor; h > -1; h--){          //Decremento da hora
    Serial.print("h=");
    Serial.println(h);
    for(m = Min; m > -1; m--){        //Decremento dos minutos
      Serial.print("m=");
      Serial.println(m);
      for(s = Seg; s > -1; s--){      //Decremento dos segundos
        Serial.print("s=");
        Serial.println(s);
        
        lcd.clear();
        lcd.print(h);
        lcd.print("H ");
        lcd.print(m);
        lcd.print("M ");
        lcd.print(s);
        lcd.print("S");
        pConfig();
        if(h == 0){
          if(m == 0){
            if(s == 0){
              buzz();
            } /*else{
              if(s == 0){
                m--;
                break;
              }              
            }*/
          } /*else{
            if(m == 0){
              if(s == 0){
                h--;
                b = true;
              } else{
                if(s == 0){
                  m--;
                  break;
                }              
              }
            }
          }*/
        } 
        delay(1000);
      }
      
      /*if((m == 0) && (h != 0)){
        break;
      }*/
      /*if(m != 0) && (h == 0){
      }*/
      Seg = 59;
      if(b == true)
        b = false;
        break;
    }
    
    Min = 59;
  }    
}

void pConfig(){
  if((digitalRead(ctr) == false) && (CTR != 3)){      //Para entrar no modo de ajuste
    CTR = CTR + 1;
  }
  if((digitalRead(ctr) == false) && (CTR == 3)){
    Config();
  }
}

void Config(){
  while(CTR2 == 0){      //Ajustar a hora
      lcd.clear();
      lcd.print(Hor);
      lcd.print("H ");
      lcd.print(Min);
      lcd.print("M ");
      lcd.print(Seg);
      lcd.print("S");
      delay(250);
      lcd.clear();
      lcd.print(" H ");
      lcd.print(Min);
      lcd.print("M ");
      lcd.print(Seg);
      lcd.print("S");
      if(digitalRead(ctr) == false){
        CTR2 = CTR2 + 1;
      }
      if(digitalRead(up) == false){
        Hor = Hor + 1;
      }
      if(digitalRead(dn) == false){
        Hor = Hor - 1;
      }
      delay(250);
    }
    
    while(CTR2 == 1){    //Ajustar os minutos
      lcd.clear();
      lcd.print(Hor);
      lcd.print("H ");
      lcd.print(Min);
      lcd.print("M ");
      lcd.print(Seg);
      lcd.print("S");
      delay(250);
      lcd.clear();
      lcd.print(Hor);
      lcd.print("H ");
      lcd.print(" M ");
      lcd.print(Seg);
      lcd.print("S");
      if(digitalRead(ctr) == false){
        CTR2 = CTR2 + 1;
      }
      if(digitalRead(up) == false){
        Min = Min + 1;
      }
      if(digitalRead(dn) == false){
        Min = Min - 1;
      }
      delay(250);
    }
    
    while(CTR2 == 2){    //Ajustar os segundos
      lcd.clear();
      lcd.print(Hor);
      lcd.print("H ");
      lcd.print(Min);
      lcd.print("M ");
      lcd.print(Seg);
      lcd.print("S");
      delay(250);
      lcd.clear();
      lcd.print(Hor);
      lcd.print("H ");
      lcd.print(Min);
      lcd.print("M ");
      lcd.print(" S");
      if(digitalRead(ctr) == false){
        CTR2 = CTR2 + 1;
        break;
      }
      if(digitalRead(up) == false){
        Seg = Seg + 1;
      }
      if(digitalRead(dn) == false){
        Seg = Seg - 1;
      }
      delay(250);
    }
    
   if(CTR2 == 3){      //Para sair do ajuste
     CTR2 = 0;
     CTR = 0;
   }  
}

void buzz(){
  while(digitalRead(ctr) == true){
    lcd.clear();
    lcd.print("ACORDE!!!");
    //play tone
    tone(13,2999,800);// esta linha de código é usada especialmente para o buzzer
    //O seu funcionamento é : o pino, a frequência e o tempo de duração em milissegundos
    //delay (ms)
    delay(1000);
  }  
  Hor = 12;
  Min = 0;
  Seg = 0;
}
