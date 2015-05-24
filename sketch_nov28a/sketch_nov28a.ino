int a0,a1,a2,a3,a4;

void setup(){
  Serial.begin(115200);
}

void loop(){
  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);
  Serial.print("Laser 1: ");
  Serial.println(a0);
  Serial.print("Laser 2: ");
  Serial.println(a1);
  Serial.print("Laser 3: ");
  Serial.println(a2);
  Serial.print("Laser 4: ");
  Serial.println(a3);
  Serial.print("Laser 5: ");
  Serial.println(a4);
  Serial.println();
  delay(100);
}
