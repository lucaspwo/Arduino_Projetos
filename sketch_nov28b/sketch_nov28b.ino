int a0,a1,a2,a3,a4;

#define threshold  400

void setup(){
  Serial.begin(115200);
}

void loop(){
  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);
  
  if(a0 < threshold){
    Serial.println("1");
  }
  if(a1 < threshold){
    Serial.println("2");
  }
  if(a2 < threshold){
    Serial.println("3");
  }
  if(a3 < threshold){
    Serial.println("4");
  }
  if(a4 < threshold){
    Serial.println("5");
  }
  
  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);
}
