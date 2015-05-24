// Example 02: Turn on LED while the button is pressed
//
// Copy and paste this example into an empty Arduino sketch

#define LEDVR 7   // the pin for the LED
#define LEDVD 5
#define CTR 51 // the input pin where the
#define UP 49
#define GND 47   // pushbutton is connected
#define VCC 53

int val1 = 0;     // val will be used to store the state
                 // of the input pin 
int val2 = 0;                 

void setup() {
  pinMode(LEDVR, OUTPUT);   // tell Arduino LED is an output
  pinMode(CTR, INPUT); // and BUTTON is an input
  pinMode(UP, INPUT);
  pinMode(LEDVD, OUTPUT);
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
  pinMode(GND, OUTPUT);
  digitalWrite(GND, LOW);
}

void loop(){
  val1 = digitalRead(CTR); // read input value and store it

  // check whether the input is HIGH (button pressed)
  if (val2 == HIGH){
    if (val1 == LOW) { 
      digitalWrite(LEDVD, HIGH); // turn LED ON
      digitalWrite(LEDVR, LOW);
    } else {
      digitalWrite(LEDVD, LOW);
      digitalWrite(LEDVD, LOW);
    }
  } else
      ;
  
  if(val1 == HIGH){
    val2 = digitalRead(UP);
    
    if (val2 == LOW) {
      digitalWrite(LEDVR, HIGH);
      digitalWrite(LEDVD, LOW);
    } else {
      digitalWrite(LEDVR, LOW);
      digitalWrite(LEDVD, LOW);
    }
  } else
     ;
}
