/*
  Blink
 
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 The circuit:
 * LED connected from digital pin 13 to ground.
 
 * Note: On most Arduino boards, there is already an LED on the board
 connected to pin 13, so you don't need any extra components for this example.
 
 
 Created 1 June 2005
 By David Cuartielles
 
 http://arduino.cc/en/Tutorial/Blink
 
 based on an orginal by H. Barragan for the Wiring i/o board
 
 */

int ledPin =  13;    // LED connected to digital pin 13
int ledPin1 = 12;
int ledPin2 = 11;
int ledPin3 = 10;
int ledPin4 = 9;

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pin as an output:
  pinMode(ledPin, OUTPUT);     
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
}

// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()                     
{
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin1, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin2, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin3, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin4, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin1, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin2, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin3, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin4, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin1, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin1, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin2, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin2, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin3, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin3, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin4, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin4, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin4, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin4, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin3, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin3, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin2, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin2, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin1, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin1, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(50);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(50);                  // wait for a second
  digitalWrite(ledPin4, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin3, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin2, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin1, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(100);                  // wait for a second
  digitalWrite(ledPin4, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin3, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin2, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin1, LOW);    // set the LED off
  delay(100);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(100);                  // wait for a second

}
