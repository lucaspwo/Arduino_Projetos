#include <Wire.h>
#include <LiquidCrystal.h>

#define RTC  0x68
#define PWR  5

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte segundo, minuto, _minuto, hora, diaDaSemana, diaDoMes, mes, ano;

void setup(){
  pinMode(PWR, OUTPUT);
  analogWrite(PWR, 100);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Wire.begin();
}

void loop(){
  imprimeDadosModulo();
}

void imprimeDadosModulo(){
  String ajustaSegundo;
  String ajustaMinuto;
  String _ajustaMinuto;
  String ajustaHora;
  String ajustaDiaDoMes;
  String ajustaMes;
  Wire.beginTransmission(RTC);
  Wire.write((byte)0x00); 
  Wire.endTransmission();
  Wire.requestFrom(RTC, 7);
  segundo = bcdToDec(Wire.read() & 0x7f); 
  _minuto = minuto;
  minuto = bcdToDec(Wire.read());          
  hora = bcdToDec(Wire.read() & 0x3f);   
  diaDaSemana = bcdToDec(Wire.read());    
  diaDoMes = bcdToDec(Wire.read());       
  mes = bcdToDec(Wire.read());            
  ano = bcdToDec(Wire.read());            
  ajustaHora += ajustaZero(hora);
  ajustaMinuto += ajustaZero(minuto);
  ajustaSegundo += ajustaZero(segundo);
  ajustaDiaDoMes += ajustaZero(diaDoMes);
  ajustaMes += ajustaZero(mes);
  if(minuto != _minuto){
    printDisplay(&ajustaHora, &ajustaMinuto, &ajustaDiaDoMes, &ajustaMes, &ano);
  }
  //imprimeSerial(&ajustaHora, &ajustaMinuto, &ajustaSegundo, &diaDaSemana, &ajustaMes, &ajustaDiaDoMes, &ano);
}

byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

String ajustaZero(byte dado){
  String dadoAjustado;
  if (dado < 10){
    dadoAjustado += "0";
  }
  dadoAjustado += dado; 
  
  return dadoAjustado; 
}

void printDisplay(String *hora, String *minuto, String *dia, String *mes, byte *ano){
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print(*hora);
  lcd.print(":");
  lcd.print(*minuto);
  lcd.setCursor(4,1);
  lcd.print(*dia);
  lcd.print("/");
  lcd.print(*mes);
  lcd.print("/");
  lcd.print(*ano);
  analogWrite(PWR, 255);
  delay(5000);
  analogWrite(PWR, 100);
}

void imprimeSerial(String *hora, String *minuto, String *segundo, byte *diaDaSemana, String *mes, String *diaDoMes, byte *ano){
  Serial.print("Agora sao: ");  
  Serial.print(*hora); 
  Serial.print(":");
  Serial.print(*minuto);
  Serial.print(":");
  Serial.println(*segundo);
  Serial.print("Dia da semana: ");
  switch(*diaDaSemana){
    case 0:Serial.println("Domingo"); break;   
    case 1:Serial.println("Segunda-feira"); break;
    case 2:Serial.println("Terca-feira"); break; 
    case 3:Serial.println("Quarta-feira"); break; 
    case 4:Serial.println("Quinta-feira"); break;  
    case 5:Serial.println("Sexta-feira"); break;   
    case 6:Serial.println("Sabado"); break; 
  }
  Serial.print("Data: ");
  Serial.print(*diaDoMes);
  Serial.print("/");
  Serial.print(*mes);
  Serial.print("/");
  Serial.println(*ano);
  Serial.println();
}
