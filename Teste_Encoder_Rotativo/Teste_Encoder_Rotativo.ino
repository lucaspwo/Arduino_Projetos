#define ENCODER_CLK 2
#define ENCODER_DT 3

volatile int contador = 0;

void setup() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  Serial.begin(9600);
}

void loop() {
  static int lastCLK = HIGH;
  static int lastDT = HIGH;
  static unsigned long ultimaLeitura = 0;

  int currentCLK = digitalRead(ENCODER_CLK);
  int currentDT  = digitalRead(ENCODER_DT);

  if ((millis() - ultimaLeitura) > 5) {
    if (currentCLK != lastCLK) {
      if (currentDT != currentCLK) {
        contador++;
      } else {
        contador--;
      }
      ultimaLeitura = millis();

      // Exibe o valor no Serial Monitor
      Serial.print("Contador: ");
      Serial.println(contador);
    }
  }

  lastCLK = currentCLK;
  lastDT = currentDT;
}
