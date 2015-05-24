#include <SoftwareSerial.h>
#include <serLCD.h>

const int rxpin = 2;           // pin used to receive
const int txpin = 3;           // pin used to send to
SoftwareSerial bluetooth(rxpin, txpin);  // new serial port on given pins

int pin = 4;
int cont = 0;
char str[16];
char str2[34];

serLCD lcd(pin);

void setup()
{
  bluetooth.begin(115200);  // initialize the software serial port
  bluetooth.println("Bluetooth ready");
  lcd.clear();
}

void loop()
{
  if (bluetooth.available())
  {
    char c = (char)bluetooth.read();
    cont++;
    /*if (int(c) == 0x0A)  // Tratamento para pular de linha (ENTER)
    {
      if (cont < 16)
      {
        lcd.selectLine(2);
        cont = 16;
      }
    }*/
    /*str2[cont] = c;      // Tratamento para apagar o último envio  
    if (int(c) == 0x09)
    {
      lcd.clear();
      for(int i=1;i<cont-1;i++)
      {
        lcd.print(str2[i-1]);
      }
      cont = cont - 2;
    }*/
    if(cont > 16 && cont <= 32){
      str[cont-17] = c;
    }
    if (cont > 32)
    {
      lcd.clear();
      for(int i = 0;i<16;i++)
      {
        lcd.print(str[i]);
      }
      cont = 17;
      str[0] = c;
    }
    if (c == '$'){
      lcd.clear();
      cont = 0;
    }
    else{
      lcd.print(c);
    }
  }
}
