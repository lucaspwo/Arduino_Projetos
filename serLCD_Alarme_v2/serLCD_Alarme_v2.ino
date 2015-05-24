#include <SoftwareSerial.h>
#include <serLCD.h>

int pin = 2;
serLCD lcd(pin);

int Hor = 2;
int Min = 0;
int Seg = 5;
int h,m,s = 0;

void setup(){
  pinMode(13, OUTPUT);
  lcd.clear();
  Serial.begin(9600);
}

void loop(){
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

void buzz(){
  lcd.clear();
  lcd.print("ACORDE!!!");
  //play tone
  tone(13,2999,800);// esta linha de código é usada especialmente para o buzzer
  //O seu funcionamento é : o pino, a frequência e o tempo de duração em milissegundos
  //delay (ms)
  delay(1000);
}
