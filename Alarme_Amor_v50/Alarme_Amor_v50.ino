#include <Wire.h>
#include <LiquidCrystal.h>
#include "defines.h"

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
byte segundo, minuto, _minuto, hora, diaDaSemana, diaDoMes, mes, ano, dado2, dado3;
int cont = 0;
boolean alarme = false, toca = false;

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

void setup(){
  analogReference(EXTERNAL);    //usar como referencia a tensão de entrada
  lcd.createChar(0, grau);      //criacao do caractere grau: º
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


