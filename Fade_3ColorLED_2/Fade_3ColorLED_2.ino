// Example 04: Fade an LED in and out like on 
// a sleeping Apple computer 
//
// Copy and paste this example into an empty Arduino sketch

#define VD   12 // the pin for the LED
#define AZ   11
#define A    10
#define K     9
int i = 0;      // We’ll use this to count up and down

void setup() { 
  pinMode(VD, OUTPUT); // tell Arduino LED is an output 
  pinMode(AZ, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(K, OUTPUT);
} 

void loop(){ 
  
  digitalWrite(K, LOW);
  digitalWrite(VD, HIGH);
  digitalWrite(AZ, HIGH);
  
  for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
    analogWrite(A, i);      // set the LED brightness
    
    delay(10); // Wait 10ms because analogWrite
               // is instantaneous and we would
               // not see any change
  }

  for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)

    analogWrite(A, i); // set the LED brightness
    delay(10);           // Wait 10ms
  }
  
  delay(100);
  
  digitalWrite(K, HIGH);
  digitalWrite(VD, LOW);
  digitalWrite(AZ, HIGH);

  for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
    analogWrite(A, i);      // set the LED brightness
    
    delay(10); // Wait 10ms because analogWrite
               // is instantaneous and we would
               // not see any change
  }

  for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)

    analogWrite(A, i); // set the LED brightness
    delay(10);           // Wait 10ms
  }
  
  delay(100);
  
  digitalWrite(K, HIGH);
  digitalWrite(VD, HIGH);
  digitalWrite(AZ, LOW);

  for (i = 0; i < 255; i++) { // loop from 0 to 254 (fade in)
    analogWrite(A, i);      // set the LED brightness
    
    delay(10); // Wait 10ms because analogWrite
               // is instantaneous and we would
               // not see any change
  }

  for (i = 255; i > 0; i--) { // loop from 255 to 1 (fade out)

    analogWrite(A, i); // set the LED brightness
    delay(10);           // Wait 10ms
  }
  
  delay(100);
} 
