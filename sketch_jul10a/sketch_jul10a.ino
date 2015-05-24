void setup(){
  pinMode(19, INPUT);
  pinMode(18, INPUT);
  Serial.begin(9600);
}

void loop(){
  if(digitalRead(19) == HIGH){
    Serial.println("P_19: 1");
  }
  if(digitalRead(19) == LOW){
    Serial.println("P_19: 0");
  }
  if(digitalRead(18) == HIGH){
    Serial.println("P_18: 1");
  }
  if(digitalRead(18) == LOW){
    Serial.println("P_18: 0");
  }
}
