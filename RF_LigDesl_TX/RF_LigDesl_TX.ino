#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(9,10);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL }; 

// A single byte to keep track of the data being sent back and forth
byte counter = 1;

void setup() {
  Serial.begin(115200);
  printf_begin();
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[0]);
}

void loop() {

  if ( Serial.available() ){
    char c = toupper(Serial.read());
    if(c == 'L'){
      counter = 1;
    } else{
      counter = 0;
    }
    
    printf("Now sending %d as payload. ",counter);
    byte gotByte;  
    unsigned long time = micros();                          // Take the time, and send it.  This will block until complete   
                                                            //Called when STANDBY-I mode is engaged (User is finished sending)
    if (!radio.write( &counter, 1 )){
      Serial.println(F("failed."));      
    }else{
    
      if(!radio.available()){ 
        Serial.println(F("Blank Payload Received.")); 
      }else{
        while(radio.available() ){
          unsigned long tim = micros();
          radio.read( &gotByte, 1 );
          printf("Got response %d, round-trip delay: %lu microseconds\n\r",gotByte,tim-time);
          counter++;
        }
      }
    
    }
  }
  // Try again later
//  delay(1000);
}
