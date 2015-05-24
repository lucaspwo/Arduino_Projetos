void setup(){
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  delay(10);
  if(digitalRead(12) == HIGH){  
    digitalWrite(13, HIGH);
    Serial.println("1");
  }
  if(digitalRead(12) == LOW){  
    digitalWrite(13, LOW);
    Serial.println("0");
  }
  delay(10);
}
