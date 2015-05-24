#define  ldr1  2//  \
#define  ldr2  3//   \ Pinos digitais D2, D3, D4 e D5
#define  ldr3  4//   /
#define  ldr4  5//  /

float t0, t1, t2, t3;  // Variáveis para armazenar o tempo em segundos

void setup(){
  Serial.begin(9600);
  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(ldr3, INPUT);
  pinMode(ldr4, INPUT);
}

void loop(){
  t0 = pulseIn(ldr1, LOW);  //duracao = pulseIn(pino, estado, timeout);
  t1 = pulseIn(ldr2, LOW);
  t2 = pulseIn(ldr3, LOW);
  t3 = pulseIn(ldr4, LOW);
}
