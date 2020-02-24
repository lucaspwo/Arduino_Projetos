/***************************************************************
 * Medidor de corrente AC utilizando o ACS712-30A
 * 
 * developed by: Haroldo Amaral - agaelema@gmail.com
 * 2017/09/23 - v 1.0
 ***************************************************************/

//#include <Wire.h>                           // biblioteca wire (I2C)
//#include <Adafruit_GFX.h>                   // biblioteca grafica
//#include <Adafruit_SSD1306.h>               // biblioteca para o display OLED
#include <SoftwareSerial.h>
#include <serLCD.h>

//#define OLED_RESET 4
//Adafruit_SSD1306 display(OLED_RESET);       // cria instancia do display OLED
int pin = 2;
serLCD lcd(pin);


#include "EmonLib.h"                        // inclui a biblioteca
EnergyMonitor emon1;                        // Cria uma instância

#define   SAMPLING_TIME     0.0001668649    // intervalo de amostragem 166,86us
#define   LINE_FREQUENCY    60              // frequencia 60Hz Brasil

#define   VOLTAGE_AC        221.00          // 127 Volts
#define   ACS_MPY           15.41           // ganho/calibracao da corrente

double Irms = 0;

void setup(){  
  emon1.current(1, ACS_MPY);             // Corrente: pino analógico, calibracao.

  lcd.clear();

  /* inicia o display oled no endereço 0x3c - 128x64 */
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  /* limpa o buffer e atualiza o display (vazio) */
//  display.clearDisplay();

  /* fixa texto no display */
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.setCursor(0,0);
//  display.println("ACS712 e Emonlib");
//  display.display();
}

void loop(){
  /* chama função para calculo da corrente */
  Irms = emon1.calcIrms(1996);  // Calculate Irms only

  /* seta parametros do texto */
//  display.setTextSize(1);
//  display.setTextColor(WHITE, BLACK);
//  display.setCursor(0,20);

lcd.clear();
lcd.print("Cor: ");
lcd.print(Irms, 3);
lcd.print(" A");
  /* imprime a corrente no display OLED */
//  display.println("Corrente");
//  display.print("-> ");   display.print(Irms, 3);   display.println(" A  ");

lcd.setCursor(2,1);
lcd.print("Pot: ");
lcd.print(Irms * VOLTAGE_AC * 0.65);
lcd.print(" W");
  /* imprime a potencia aparente no display OLED */
//  display.println();
//  display.println("Pot. Aparente");
//  display.print("-> ");   display.print(Irms * VOLTAGE_AC); display.println(" VA  ");

  /* atualiza a imagem no display */
//  display.display();
}
