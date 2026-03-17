#include <SoftwareSerial.h>

#define PINO_IN11 5  // Pino responsável pelo controle no sentido horário - motor 1
#define PINO_IN12 6  // Pino responsável pelo controle no sentido anti-horário - motor 1

#define PINO_IN21 9   // Pino responsável pelo controle no sentido horário - motor 2
#define PINO_IN22 10  // Pino responsável pelo controle no sentido anti-horário - motor 2

#define PINO_LED_LIGADO 7     // Pino para exibir que a placa está ligada
#define PINO_LED_STATUS_BT 8  // Pino para exibir o estado do Bluetooth

#define VELOCIDADE 128  // Velocidade para acionar os motores

# if defined(ARDUINO_AVR_UNO)
  // Caso a placa seja um Arduino Uno
  const int rxpin = 11;           // Pino para receber dados do Bluetooth
  const int txpin = 12;           // Pino para enviar dados do Bluetooth
  const int statepin = 13;        // Pino para detectar se o Bluetooth está conectado
# else
  // Caso a placa seja um Arduino Leonardo ou Pro Micro
  const int rxpin = 16;           // Pino para receber dados do Bluetooth
  const int txpin = 14;           // Pino para enviar dados do Bluetooth
  const int statepin = 15;        // Pino para detectar se o Bluetooth está conectado
# endif

SoftwareSerial bluetooth(rxpin, txpin);  // Cria serial virtual "bluetooth" com os pinos

void setup() {
  digitalWrite(PINO_LED_LIGADO, HIGH);

  // Inicializa a serial virtual
  bluetooth.begin(9600);


  /* Inicia declaração dos protótipos das funções */
  
  // Função para ativar o motor 1 para a frente com a velocidade "vel" passada como argumento
  void aceleraMotor1(int vel);
  // Função para ativar o motor 2 para a frente com a velocidade "vel" passada como argumento
  void aceleraMotor2(int vel);

  // Equivalente a desengatar a marcha (ponto-morto) - motor 1
  void paraMotor1();
  // Equivalente a desengatar a marcha (ponto-morto) - motor 2
  void paraMotor2();

  // Função para ativar o motor 1 para trás com a velocidade "vel" passada como argumento
  void reverteMotor1(int vel);
  // Função para ativar o motor 2 para trás com a velocidade "vel" passada como argumento
  void reverteMotor2(int vel);

  // Função para ativar os dois motores simultaneamente, para frente e para trás
  void aceleraDoisMotores(int vel);
  void reverteDoisMotores(int vel);

  // Função auxiliar para escrever PWM com rampa
  void analogWriteRampa(int pino, int valorFinal, int tempoStep);
  // Função auxiliar para escrever PWM com rampa dupla (para dois motores simultâneos)
  void analogWriteRampaDupla(int pino1, int pino2, int valorFinal, int tempoStep);

  // Função para indicar o estado de conexão do Bluetooth
  bool estadoBluetooth();

  /* Declara os pinos digitais como saída (PWM) */
  pinMode(PINO_IN11, OUTPUT);
  pinMode(PINO_IN12, OUTPUT);
  pinMode(PINO_IN21, OUTPUT);
  pinMode(PINO_IN22, OUTPUT); 
}

void loop() {
  bool conectado = estadoBluetooth();
  if (bluetooth.available()) {
    char c = (char)bluetooth.read();
    // Se algum botão for "solto" ou se a conexão com o Bluetooth for perdida
    if (c == '0' || !conectado) {
      paraMotor1();
      paraMotor2();
    }

    // Se o botão "para cima" for pressionado
    if (c == 'F') {
      aceleraDoisMotores(VELOCIDADE);
    }

    // Se o botão "para baixo" for pressionado
    if (c == 'B') {
      reverteDoisMotores(VELOCIDADE);
    }

    // Se o botão "para direita" for pressionado
    if (c == 'R') {
      aceleraMotor1(VELOCIDADE);
      paraMotor2();
    }

    // Se o botão "para esquerda" for pressionado
    if (c == 'L') {
      paraMotor1();
      aceleraMotor2(VELOCIDADE);
    }

    delay(1);
  }
  delay(1);
}

void analogWriteRampa(int pino, int valorFinal, int tempoStep = 5) {
  int valorAtual = 0;

  for (int v = valorAtual; v <= valorFinal; v++) {
    analogWrite(pino, v);
    delay(tempoStep);
  }
}

void analogWriteRampaDupla(int pino1, int pino2, int valorFinal, int tempoStep = 5) {
  int valorAtual = 0;

  for (int v = valorAtual; v <= valorFinal; v++) {
    analogWrite(pino1, v);
    analogWrite(pino2, v);
    delay(tempoStep);
  }
}

void aceleraDoisMotores(int vel) {
  analogWrite(PINO_IN12, 0);
  analogWrite(PINO_IN22, 0);
  analogWriteRampaDupla(PINO_IN11, PINO_IN21, vel);
}

void reverteDoisMotores(int vel) {
  analogWrite(PINO_IN11, 0);
  analogWrite(PINO_IN21, 0);
  analogWriteRampaDupla(PINO_IN12, PINO_IN22, vel);
}

void aceleraMotor1(int vel) {
  analogWriteRampa(PINO_IN11, vel);
  analogWrite(PINO_IN12, 0);
}

void aceleraMotor2(int vel) {
  analogWriteRampa(PINO_IN21, vel);
  analogWrite(PINO_IN22, 0);
}

void paraMotor1() {
  analogWrite(PINO_IN11, 0);
  analogWrite(PINO_IN12, 0);
}

void paraMotor2() {
  analogWrite(PINO_IN21, 0);
  analogWrite(PINO_IN22, 0);
}

void reverteMotor1(int vel) {
  analogWrite(PINO_IN11, 0);
  analogWriteRampa(PINO_IN12, vel);
}

void reverteMotor2(int vel) {
  analogWrite(PINO_IN21, 0);
  analogWriteRampa(PINO_IN22, vel);
}

bool estadoBluetooth() {
  bool estado = digitalRead(statepin);

  if (estado) {
    digitalWrite(PINO_LED_STATUS_BT, HIGH);
  } else {
    digitalWrite(PINO_LED_STATUS_BT, LOW);
  }

  return estado;
}