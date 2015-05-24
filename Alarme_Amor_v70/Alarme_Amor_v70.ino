#include <Wire.h>
#include <LiquidCrystal.h>
#include "defines.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte segundo, minuto, _minuto, hora, diaDaSemana, diaDoMes, mes, ano, dado2, dado3;
int cont = 0;
boolean alarme = false, toca = false, nam = false, aniv = false;

byte grau[8] = {      //caractere de grau: º
	0b00000,
	0b00110,
	0b01001,
	0b01001,
	0b00110,
	0b00000,
	0b00000,
	0b00000
};

byte seta[8] = {      //caractere seta: ->
	0b00000,
	0b00100,
	0b00010,
	0b11111,
	0b00010,
	0b00100,
	0b00000,
	0b00000
};

byte cor[8] = {
	0b00000,
	0b00000,
	0b01010,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000
};

byte pres[8] = {
	0b01010,
	0b10101,
	0b01110,
	0b11111,
	0b10101,
	0b11111,
	0b10101,
	0b11111
};

void setup(){
  analogReference(EXTERNAL);    //usar como referencia a tensão de entrada
  lcd.createChar(0, grau);      //criacao do caractere grau: º
  lcd.createChar(1, seta);      //criacao do caractere seta: ->
  lcd.createChar(3, cor);
  lcd.createChar(4, pres);
  pinMode(HOR, INPUT);          //configuracao dos botoes como entrada, em seguida, enviar sinal logico alto
  digitalWrite(HOR, HIGH);
  pinMode(PBA, INPUT);
  digitalWrite(PBA, HIGH);
  pinMode(LDA, INPUT);
  digitalWrite(LDA, HIGH);
  pinMode(CAL, INPUT);
  digitalWrite(CAL, HIGH);
  pinMode(PCI, INPUT);
  digitalWrite(PCI, HIGH);
  pinMode(ENT, INPUT);
  digitalWrite(ENT, HIGH);
  pinMode(PWR, OUTPUT);        //configuracao de saida para backlight do LCD
  analogWrite(PWR, 100);       //backlight em luz baixa (PWM = 100)
  lcd.begin(16, 2);            //inicializacao do LCD (16 colunas por 2 linhas)
  Serial.begin(9600);          //serial para debug
  Wire.begin();                //inicializacao do I2C
}

void loop(){
  imprimeDadosModulo();
}


