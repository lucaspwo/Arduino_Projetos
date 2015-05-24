int a;
float b;

void setup(){
  Serial.begin(9600);
}

void loop(){
  a = analogRead(0);
  b = (0.00488*a);
  b = b*100;
  Serial.println(b);
  delay(150);
}
