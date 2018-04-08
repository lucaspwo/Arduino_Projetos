/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;
int SW = 12;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH);
  //Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  //Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  //Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    //Serial.println(results.value);
    if(results.value == 3536){
      //Serial.println("Deu certo!");
      pinMode(SW, OUTPUT);
      digitalWrite(SW, LOW);
      delay(100);
      pinMode(SW, INPUT);
      digitalWrite(SW, HIGH);
      delay(100);
    }
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
