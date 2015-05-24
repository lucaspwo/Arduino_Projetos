#include <Wire.h>
#include <LiquidCrystal.h>

#define ROM  0x50
#define RTC  0x68
#define PWR  5
#define HOR  2

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte segundo, minuto, _minuto, hora, diaDaSemana, diaDoMes, mes, ano;
int cont = 0;
boolean alarme = false;

byte grau[8] = {
	0b00000,
	0b00110,
	0b01001,
	0b01001,
	0b00110,
	0b00000,
	0b00000,
	0b00000
};

void setup(){
  lcd.createChar(0, grau);
  pinMode(HOR, INPUT);
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
  if((digitalRead(HOR) == true)){
    printDisplay(&ajustaHora, &ajustaMinuto, &diaDaSemana, &ajustaDiaDoMes, &ajustaMes, &ano);
  }
  if(minuto != _minuto){
    imprimeTela();
  }
  /*cont++;
  if (cont == 500){
    imprimeSerial(&ajustaHora, &ajustaMinuto, &ajustaSegundo, &diaDaSemana, &ajustaMes, &ajustaDiaDoMes, &ano);
    cont = 0;
  }*/
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

void printDisplay(String *hora, String *minuto, byte *diaDaSemana, String *diaDoMes, String *mes, byte *ano){
  lcd.clear();
  analogWrite(PWR, 255);
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
  delay(5000);
  analogWrite(PWR, 100);
  imprimeTela();
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

void imprimeTela(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Alarme: ");
  checkAlarm();
  if(alarme == false){
    lcd.print("DESLIG.");
  }
  if(alarme == true){
    //lcd.print();
  }
  lcd.setCursor(0,1);
  lcd.print("Temp.:  ");
  float temp = checkTemp();
  lcd.print((int)temp);
  lcd.write((uint8_t)0);
  lcd.print("C");
}

void checkAlarm(){
  Wire.beginTransmission(ROM);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(ROM, 1);
  delay(10);
  byte data = Wire.read();
  if((int)data == 65)
    alarme = false;
  if((int)data == 66)
    alarme = true;
}

float checkTemp(){
  float media=0;
  for(int i=0; i<1000; i++){
    media = media + analogRead(3);
  }
  media = media/1000;
  media = media * 0.48828125;
  return(media);
}
