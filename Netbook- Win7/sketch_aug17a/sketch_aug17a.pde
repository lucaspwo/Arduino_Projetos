int sensor = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  
  sensor = analogRead(0);
  Serial.println(sensor);
  delay(500);
}
