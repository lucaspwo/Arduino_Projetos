// Car MP3 IR receiver code translator
// http://www.bajdi.com
// Bought the Car MP3 IR receiver here: http://arduino-direct.com/sunshop/index.php?l=product_detail&p=153
// Found info and code here: http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
// Copied most of the code from here: http://tronixstuff.wordpress.com/2011/03/30/tutorial-arduino-and-infra-red-control/
 
//#include "Wire.h" // for I2C bus
 
//#include "LiquidCrystal_I2C.h" // for I2C bus LCD module http://bit.ly/eNf7jM
 
//LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
 
#include <IRremote.h> // use the library for IR
 
int receiver = 11; // pin 1 of IR receiver to Arduino digital pin 11
 
IRrecv irrecv(receiver); // create instance of 'irrecv'
 
decode_results results;
 
void setup()
 
{
 
  //Serial.init();          // initialize the lcd
  Serial.begin(9600);
 
  //Serial.backlight(); // turn on LCD backlight
 
  irrecv.enableIRIn(); // Start the receiver
 
}
 
void translateIR() // takes action based on IR code received
 
// describing Car MP3 IR codes on LCD module
 
{
 
  switch(results.value)
 
  {
 
    case 0xFFA25D:  Serial.println(" CH-            "); break;
 
    case 0xFF629D:  Serial.println(" CH             "); break;
 
    case 0xFFE21D:  Serial.println(" CH+            "); break;
 
    case 0xFF22DD:  Serial.println(" PREV           "); break;
 
    case 0xFF02FD:  Serial.println(" NEXT           "); break;
 
    case 0xFFC23D:  Serial.println(" PLAY/PAUSE     "); break;
 
    case 0xFFE01F:  Serial.println(" VOL-           "); break;
 
    case 0xFFA857:  Serial.println(" VOL+           "); break;
 
    case 0xFF906F:  Serial.println(" EQ             "); break;
 
    case 0xFF6897:  Serial.println(" 0              "); break;
 
    case 0xFF9867:  Serial.println(" 100+           "); break;
 
    case 0xFFB04F:  Serial.println(" 200+           "); break;
 
    case 0xFF30CF:  Serial.println(" 1              "); break;
 
    case 0xFF18E7:  Serial.println(" 2              "); break;
 
    case 0xFF7A85:  Serial.println(" 3              "); break;
 
    case 0xFF10EF:  Serial.println(" 4              "); break;
 
    case 0xFF38C7:  Serial.println(" 5              "); break;
 
    case 0xFF5AA5:  Serial.println(" 6              "); break;
 
    case 0xFF42BD:  Serial.println(" 7              "); break;
 
    case 0xFF4AB5:  Serial.println(" 8              "); break;
 
    case 0xFF52AD:  Serial.println(" 9              "); break;
 
    default: Serial.println(" other button   ");
 
  }
 
  delay(500);
 
  //Serial.clear();
 
}
 
void loop()
 
{
 
  if (irrecv.decode(&results)) // have we received an IR signal?
 
  {
 
    translateIR();
 
       irrecv.resume(); // receive the next value
 
  }
 
}
