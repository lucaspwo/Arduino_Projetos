// Example 06A: Blink LED at a rate specified by the 
// value of the analogue input
//
// Copy and paste this example into an empty Arduino sketch

#define LED  13 // the pin for the LED 

int val = 0;   // variable used to store the value
               // coming from the sensor
void setup() {
  pinMode(LED, OUTPUT); // LED is as an OUTPUT

  // Note: Analogue pins are
  // automatically set as inputs
}

void loop() {

  val = analogRead(0); // read the value from
                       // the sensor

  digitalWrite(13, HIGH); // turn the LED on

  delay(val); // stop the program for
              // some time

  digitalWrite(13, LOW); // turn the LED off

  delay(val); // stop the program for
              // some time
}
