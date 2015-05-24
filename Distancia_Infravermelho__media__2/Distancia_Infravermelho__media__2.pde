#define IV 0

float val = 0;
float dist = 0;
float voltagem = 0;
float media = 0;
int i = 0;

const int trigPin = 7;
const int ecoPin = 6;

void setup(){
    Serial.begin(9600);
}

void loop(){
    //PARA O SONAR
    long duration, cm;
    
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    
    pinMode(ecoPin, INPUT);
    duration = pulseIn(ecoPin, HIGH);
    
    cm = microsecondsToCentimeters(duration);
    
    //PARA O INFRAVERMELHO
    for(i=1; i<6; i++){
        val = analogRead(IV);    
        voltagem = (val * 5) / 1023;
        dist = 57.157 * (1 / pow(voltagem, 1.119));
        media = media + dist;
    }
    
    media = media / 5;

    Serial.print("Distancia (IV): ");
    Serial.print(media);
    Serial.print("cm");
    Serial.println();
    Serial.print("Distancia (Sonar): ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    delay(250);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
