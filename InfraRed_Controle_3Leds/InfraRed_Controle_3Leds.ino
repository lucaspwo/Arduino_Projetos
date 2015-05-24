// http://www.bajdi.com
// Bought the Car MP3 IR receiver here: http://arduino-direct.com/sunshop/index.php?l=product_detail&p=153
// Found info and some code here: http://www.arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
// Copied most of the code from here: http://tronixstuff.wordpress.com/2011/03/30/tutorial-arduino-and-infra-red-control/
 
#include  <IRremote.h>   // use the library for IR
 
const int receiver = 11; // pin 1 of IR receiver to Arduino digital pin 11
//const int led1 =  3;
const int led2 =  4;
//const int led3 =  5;
 
IRrecv irrecv(receiver); // create instance of 'irrecv'
 
decode_results results;
 
//boolean lightState1 = false;
boolean lightState2 = false;
//boolean lightState3 = false;
//unsigned long last1 = millis();
unsigned long last2 = millis();
//unsigned long last3 = millis();
 
void setup()
 
{
  //pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  //pinMode(led3, OUTPUT);
  irrecv.enableIRIn();
}
 
void loop()
{
  if (irrecv.decode(&results))
  {
    /*if (results.value == 0xFFA25D)
    {
      if (millis() - last1 > 300)
      {
      lightState1 =!lightState1;
      digitalWrite(led1,lightState1);
      last1 = millis();
      }
    }*/
 
    if (results.value == 0xFFA25D)
    {
      if (millis() - last2 > 300)
      {
      lightState2 =!lightState2;
      digitalWrite(led2,lightState2);
      last2 = millis();
      }
    }
    /*if (results.value == 0xFF7A85)
      {
       if (millis() - last3 > 300)
       {
       lightState3 =!lightState3;
       digitalWrite(led3,lightState3);
       last3 = millis();
       }
      }*/
irrecv.resume();
  }
}
