#define IV A0

float val = 0;
float dist = 0;
float voltagem = 0;
float media = 0;
int i = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
    for(i=1; i<6; i++){
        val = analogRead(IV);
        Serial.print("Leitura: ");
        Serial.print(val);
        Serial.print(" ");      
        voltagem = (val * 5) / 1023;
        Serial.print("Voltagem: ");
        Serial.print(voltagem);
        Serial.print(" ");
        dist = 57.157 * (1 / pow(voltagem, 1.119));
        media = media + dist;
    }
    
    media = media / 5;

    Serial.print("Distancia: ");
    Serial.print(media);
    Serial.print("cm");
    Serial.println();
    
    delay(3000);
}
