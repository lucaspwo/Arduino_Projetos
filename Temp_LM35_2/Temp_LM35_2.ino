float tempC;
int reading;
int tempPin = 0;

void setup(){
  Serial.begin(9600);
  analogReference(INTERNAL);
}

void loop(){
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  Serial.println(tempC,1);
  delay(100);
}
