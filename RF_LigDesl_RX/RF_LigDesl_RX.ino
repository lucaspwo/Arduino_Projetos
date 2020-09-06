#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL }; 

void setup() {
  pinMode(7, OUTPUT);
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[0]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();                 // Start listening
}

void loop() {
  byte pipeNo;
  byte gotByte;                                       // Dump the payloads until we've gotten everything
  while( radio.available(&pipeNo)){
    radio.read( &gotByte, 1 );
    radio.writeAckPayload(pipeNo,&gotByte, 1 );    
    if(gotByte == 1){
      digitalWrite(7, HIGH);
    } else {
      digitalWrite(7, LOW);
    }
 }
}
