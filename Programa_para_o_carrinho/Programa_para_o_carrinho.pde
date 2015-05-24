#define LED1  9                      // Relaciona o LED1 (pino 9) ao ANALOG IN 0
#define LED2  6                      // Relaciona o LED2 (pino 6) ao ANALOG IN 1

int val1 = 0;
int val2 = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
                                      // Nota: Pinos analógicos são marcados automaticamente como INPUTS
}

void loop() {
  val1 = analogRead(0);               // Para ler o valor que vem do sensor no pino 0
  val2 = analogRead(1);               // Para ler o valor que vem do sensor no pino 1
  analogWrite(LED1, val1/4);
  analogWrite(LED2, val2/4);
  delay(10);
}
