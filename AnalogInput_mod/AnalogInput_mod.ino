
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  Serial.println(sensorValue);
  // turn the ledPin on
  if(sensorValue < 400){
    digitalWrite(ledPin, HIGH);  
  }
  // stop the program for <sensorValue> milliseconds:
  //delay(sensorValue);          
  // turn the ledPin off:        
  if(sensorValue > 400){
    digitalWrite(ledPin, LOW);   
  }
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);                  
}
