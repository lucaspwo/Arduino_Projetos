// Example 02: Turn on LED while the button is pressed
//
// Copy and paste this example into an empty Arduino sketch

#define LED 13   // the pin for the LED
#define BUTTON 51 // the input pin where the
                 // pushbutton is connected
int val = 0;     // val will be used to store the state
                 // of the input pin 

void setup() {
  pinMode(LED, OUTPUT);   // tell Arduino LED is an output
  pinMode(BUTTON, INPUT); // and BUTTON is an input
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);
  pinMode(47, OUTPUT);
  digitalWrite(47, LOW);
}

void loop(){
  val = digitalRead(BUTTON); // read input value and store it

  // check whether the input is HIGH (button pressed)
  if (val == LOW) { 
    digitalWrite(LED, HIGH); // turn LED ON
  } else {
    digitalWrite(LED, LOW);
  }
}
