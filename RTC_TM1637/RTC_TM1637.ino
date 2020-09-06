#include <TM1637Display.h>
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <DS3232RTC.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

uint8_t tempo[] = {0xff, 0xff, 0xff, 0xff};
bool digit = false;

void setup() {
  Serial.begin(115200);
  
  setSyncProvider(RTC.get);
  Serial.println("Sincronizando com o RTC...");
  if (timeStatus() != timeSet)
    Serial.print(" Falha!");
  Serial.println();

  display.setBrightness(0x0f);
  display.setSegments(tempo);
}

void loop() {
  static time_t tLast;
  time_t t;
  tmElements_t tm;

  //Verifica se foi setado um novo horario
  //Formato: ano, mês, dia, hora, minuto, segundo
  if (Serial.available() >= 12) {
    int y = Serial.parseInt();
    if (y >= 100 && y < 1000)
      Serial.println("Erro: Ano deve ter dois ou quatro digitos!");
    else {
      if (y >= 1000)
        tm.Year = CalendarYrToTm(y);
      else    //(y < 100)
        tm.Year = y2kYearToTm(y);
      tm.Month = Serial.parseInt();
      tm.Day = Serial.parseInt();
      tm.Hour = Serial.parseInt();
      tm.Minute = Serial.parseInt();
      tm.Second = Serial.parseInt();
      t = makeTime(tm);
      RTC.set(t);
      setTime(t);
      Serial.print("Horario modificado para: ");
      printDateTime(t);
      Serial.println();
      while (Serial.available() > 0) Serial.read();
    }
  }
  t = now();
  if (t != tLast) {
    tLast = t;
    if(second(t) % 2){
      mostraHora(t, true);
    } else{
      mostraHora(t, false);
    }
    //Serial.println(weekday(t));
  }
}

void mostraHora(time_t t, bool seg){
  if(hour(t) < 10){
    tempo[0] = display.encodeDigit(0);
    if(seg == true)
      tempo[1] = display.encodeDigit(hour(t)) + 0b10000000;
    else
      tempo[1] = display.encodeDigit(hour(t));
  } else{
    tempo[0] = display.encodeDigit(hour(t) / 10);
    if(seg == true)
      tempo[1] = display.encodeDigit(hour(t) % 10) + 0b10000000;
     else
      tempo[1] = display.encodeDigit(hour(t) % 10);
  }
  if(minute(t) < 10){
    tempo[2] = display.encodeDigit(0);
    tempo[3] = display.encodeDigit(minute(t));
  } else{
    tempo[2] = display.encodeDigit(minute(t) / 10);
    tempo[3] = display.encodeDigit(minute(t) % 10);
  }
  display.setSegments(tempo);
}

//Mostra data e hora na serial
void printDateTime(time_t t){
  printI00(day(t), 0);
  Serial.print(monthShortStr(month(t))); Serial.print(year(t), DEC);
  Serial.print(' ');
  //printTime(t);
  printI00(hour(t), ':');
  printI00(minute(t), ':');
  printI00(second(t), ' ');
}

//Correcao para imprimir "00" ao inves de "0" caso
//o valor seja menor do que 10
void printI00(int val, char delim){
  if (val < 10) Serial.print('0');
  Serial.print(val);
  if (delim > 0) Serial.print(delim);
  return;
}
