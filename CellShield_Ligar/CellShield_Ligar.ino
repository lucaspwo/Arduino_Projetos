// Example 26.2

#include <SoftwareSerial.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 10, 9, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 8, 4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

SoftwareSerial cell(2,3); 

void setup(){ 
  Serial.begin(9600);
  cell.begin(9600);
  delay(20000); // give the GSM module time to initialise, locate network etc.
  // this delay time varies. Use example 26.1 sketch to measure the amount
  // of time from board reset to SIND: 4, then add five seconds just in case
}
void loop()
{

  char key = keypad.getKey();
  
  if (key == '*'){
    cell.print("ATD");
    Serial.print("ATD");
  }
  if (key == '#'){
    cell.println();
    Serial.println();
    delay(10000);
    cell.println("ATH");
    Serial.println("ATH");
  } else{
    cell.print(key);
    Serial.print(key);
  }

  //cell.println("ATD08499213787"); // dial the phone number xxxxxxxxx
  // change xxxxxxx to your desired phone number (with area code)
  //delay(10000); // wait 10 seconds.
  //cell.println("ATH"); // end call
  //do // remove this loop at your peril
  //{    
  //  delay(1);  
  //}
  //while (1>0);
}

