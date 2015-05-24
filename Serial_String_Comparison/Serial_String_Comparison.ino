String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
// initialize serial:
Serial.begin(9600);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {

       if (inputString.equals("test")) {
       Serial.print("THEY ARE EQUAL"); 
    }

    Serial.print(inputString); 
    // clear the string:
    inputString = "";
    stringComplete = false;
    }

   }

void serialEvent() {
  while (Serial.available()) {
  // get the new byte:
  char inChar = (char)Serial.read(); 
  // add it to the inputString:
  delay(100);
  inputString += inChar;
  stringComplete = true;

  }
}
