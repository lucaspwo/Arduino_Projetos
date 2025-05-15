// Programa: Controle de velocidade e direção de um motor Dc utilizando o módulo L298D

// Define os pinos de controle do motor ligados ao Arduino
#define PINO_IN11 5  // Pino responsável pelo controle no sentido horário
#define PINO_IN12 6  // Pino responsável pelo controle no sentido anti-horário

#define PINO_IN21 9  // Pino responsável pelo controle no sentido horário
#define PINO_IN22 10  // Pino responsável pelo controle no sentido anti-horário

#define DELAY_MOTOR 20

void setup(){ 
  // Configura os pinos de controle como saída
  pinMode(PINO_IN11, OUTPUT);  // Define o pino IN1 como saída
  pinMode(PINO_IN12, OUTPUT);  // Define o pino IN2 como saída
  pinMode(PINO_IN21, OUTPUT);  // Define o pino IN1 como saída
  pinMode(PINO_IN22, OUTPUT);  // Define o pino IN2 como saída
  Serial.begin(9600);
}
  
void loop() {   
  int valor_pwm = 0;  // Variável para armazenar o valor PWM (0-255)

  // Aumenta a velocidade gradualmente de 0% a 100% no sentido horário
  for (valor_pwm = 0; valor_pwm < 128; valor_pwm++) {
    analogWrite(PINO_IN11, valor_pwm);  // Aplica o valor PWM no pino IN1
    // analogWrite(PINO_IN21, valor_pwm);  // Aplica o valor PWM no pino IN1
    Serial.print("1: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido horário
  for (valor_pwm = 127; valor_pwm >= 0; valor_pwm--) {
    analogWrite(PINO_IN11, valor_pwm);  // Reduz o valor PWM no pino IN1
    // analogWrite(PINO_IN21, valor_pwm);  // Aplica o valor PWM no pino IN1
    Serial.print("1: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de diminuir mais a velocidade
  }

  // Aumenta a velocidade gradualmente de 0% a 100% no sentido anti-horário
  for (valor_pwm = 0; valor_pwm < 128; valor_pwm++) {
    analogWrite(PINO_IN12, valor_pwm);  // Aplica o valor PWM no pino IN2
    // analogWrite(PINO_IN22, valor_pwm);  // Aplica o valor PWM no pino IN2
    Serial.print("2: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido anti-horário
  for (valor_pwm = 127; valor_pwm >= 0; valor_pwm--) {
    analogWrite(PINO_IN12, valor_pwm);  // Reduz o valor PWM no pino IN2
    // analogWrite(PINO_IN22, valor_pwm);  // Aplica o valor PWM no pino IN2
    Serial.print("2: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de diminuir mais a velocidade
  } 
  //////////////////////////////////////////////////////////////////////////////////////////////
  // Aumenta a velocidade gradualmente de 0% a 100% no sentido horário
  for (valor_pwm = 0; valor_pwm < 128; valor_pwm++) {
    // analogWrite(PINO_IN11, valor_pwm);  // Aplica o valor PWM no pino IN1
    analogWrite(PINO_IN21, valor_pwm);  // Aplica o valor PWM no pino IN1
    Serial.print("1: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido horário
  for (valor_pwm = 127; valor_pwm >= 0; valor_pwm--) {
    // analogWrite(PINO_IN11, valor_pwm);  // Reduz o valor PWM no pino IN1
    analogWrite(PINO_IN21, valor_pwm);  // Aplica o valor PWM no pino IN1
    Serial.print("1: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de diminuir mais a velocidade
  }

  // Aumenta a velocidade gradualmente de 0% a 100% no sentido anti-horário
  for (valor_pwm = 0; valor_pwm < 128; valor_pwm++) {
    // analogWrite(PINO_IN12, valor_pwm);  // Aplica o valor PWM no pino IN2
    analogWrite(PINO_IN22, valor_pwm);  // Aplica o valor PWM no pino IN2
    Serial.print("2: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de aumentar a velocidade
  }
 
  // Diminui a velocidade gradualmente de 100% a 0% no sentido anti-horário
  for (valor_pwm = 127; valor_pwm >= 0; valor_pwm--) {
    // analogWrite(PINO_IN12, valor_pwm);  // Reduz o valor PWM no pino IN2
    analogWrite(PINO_IN22, valor_pwm);  // Aplica o valor PWM no pino IN2
    Serial.print("2: ");
    Serial.println(valor_pwm);
    delay(DELAY_MOTOR);  // Espera 100 ms antes de diminuir mais a velocidade
  } 
}