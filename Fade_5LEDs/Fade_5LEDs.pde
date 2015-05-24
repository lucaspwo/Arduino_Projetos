#define LED1 3
#define LED2 5
#define LED3 6
#define LED4 9
#define LED5 10

int i= 0;

void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void loop(){
  for(i=0; i < 255; i++){
    analogWrite(LED1, i);
    delay(10);
    analogWrite(LED2, i);
    analogWrite(LED3, i);
    delay(10);
    analogWrite(LED4, i);
    analogWrite(LED5, i);
    delay(10);
  }
  
  for(i=255; i > 0; i--){
    analogWrite(LED1, i);
    delay(10);
    analogWrite(LED2, i);
    analogWrite(LED3, i);
    delay(10);
    analogWrite(LED4, i);
    analogWrite(LED5, i);
    delay(10);
  }
}
