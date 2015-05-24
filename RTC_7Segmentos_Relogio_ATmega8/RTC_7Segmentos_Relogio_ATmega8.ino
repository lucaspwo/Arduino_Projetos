//We always have to include the library
#include "LedControl.h"
#include <Wire.h>

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=250;

#define enderecoI2C 0x68

byte segundo, minuto, hora;
int Hora, Minuto;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  //Serial.begin(9600);
  Wire.begin();
}

void loop() { 
  //writeArduinoOn7Segment();
  //scrollDigits();
  imprimeDadosModulo();
  Hora = (int)hora;
  Minuto = (int)minuto;
  lc.clearDisplay(0);
  lc.setDigit(0,3,Hora/10,false);
  lc.setDigit(0,2,(Hora-((Hora/10)*10)),false);
  lc.setDigit(0,1,Minuto/10,false);
  lc.setDigit(0,0,(Minuto-((Minuto/10)*10)),false);
  /*Serial.print((int)hora);
  Serial.print(":");
  Serial.println((int)minuto);*/
  delay(delaytime);
}

void imprimeDadosModulo(){
  //String ajustaSegundo;
  //String ajustaMinuto;
  //String ajustaHora;
  //String ajustaDiaDoMes;
  //String ajustaMes;
  
  /* Para ler os dados de hora e data no módulo deve-se realizar os seguintes passos:
        1) Abrir a comunicação I2C em modo de gravação;
        2) Redefinir o ponteiro para o primeiro registro (0x00);
        3) Finalizar o modo de gravação;
        4) Abrir a comunicação I2C em modo de leitura;
        5) Ler os sete bytes de dados.
  */
  Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
  Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
  Wire.endTransmission(); //finalizando o modo de gravação.
  Wire.requestFrom(enderecoI2C, 3);    //Abrindo o modo I2C no modo de leitura.

  //Para ler e posteriormente imprimir os dados lidos do módulo é necessário uma 
  //conversão de Binário para Decimal.
  segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. 
  minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
  hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. Essa máscara define o
                                          //relógio para trabalhar no modo de 24h.
  //diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
  //diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
  //mes = bcdToDec(Wire.read());            //convertendo o mês.
  //ano = bcdToDec(Wire.read());            //convertendo o ano.
  //ajustaHora += ajustaZero(hora);
  //ajustaMinuto += ajustaZero(minuto);
}

byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

/*String ajustaZero(byte dado){
  String dadoAjustado;
  if (dado < 10) 
  {
    dadoAjustado += "0";  //concatena o dígito "0" ao valor da variável.
  }
  dadoAjustado += dado;   //concatena o dígito "0" ao valor do dado.
  
  return dadoAjustado;    //retorna o valor do dado ajustado.
}*/
