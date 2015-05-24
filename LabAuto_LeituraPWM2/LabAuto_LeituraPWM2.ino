int pin = 7;
int media = 0;
unsigned long duration;

void setup()
{
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop()
{
  for(int i = 0; i<1024; i++){
    duration = pulseIn(pin, LOW, 2500);
    media = media + duration;
  }
  media = media/1024;
  Serial.println(media);
  delay(1000);
}
