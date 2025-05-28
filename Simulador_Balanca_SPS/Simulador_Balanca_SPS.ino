#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Encoder.h>
#include <SoftwareSerial.h>
#include <Bounce2.h>

// === Definições ===
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_BTN 4

#define LIMITE_PESO_PROT3 3100
#define LIMITE_PESO_URANO12 30000
#define TEMPO_INSTABILIDADE 1000
#define TEMPO_ESCOLHA_PROTOCOLO 5000

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);
SoftwareSerial bt(6, 7);
Bounce debouncer = Bounce();
Encoder encoder(ENCODER_CLK, ENCODER_DT);

volatile int peso = 0;
unsigned long ultimaMovimentacao = 0;

enum Protocolo { PROT3, URANO12 };
Protocolo protocoloSelecionado = PROT3;

const char* nomesProtocolos[] = { "PROT 3", "Urano 12" };

int protocoloIndex = 0;
unsigned long inicioEscolha = 0;
bool protocoloConfirmado = false;
long ultimaPosicao = 0;

void escolherProtocolo();
void lerEncoder();
void lerEncoderProtocolo();
void enviarStatus(Stream &serial, char c);
void enviarProt3(Stream &serial, int gramas);
void enviarUrano12(Stream &serial, int gramas);
void atualizarDisplayPeso();

void setup() {
  bt.begin(115200);
  Serial.begin(9600);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  debouncer.attach(ENCODER_BTN);
  debouncer.interval(25);

  display.begin();
  display.fillScreen(0);
  display.setTextColor(0xFFFF);
  display.setTextSize(1);

  escolherProtocolo();

  display.fillScreen(0);
  display.setCursor(0, 0);
  display.print("Protocolo:");
  display.setCursor(0, 10);
  display.print(nomesProtocolos[protocoloSelecionado]);
  delay(2000);
}

void loop() {
  debouncer.update();
  lerEncoder();

  if (debouncer.fell()) {
    peso = 0;
    ultimaMovimentacao = millis();
  }

  atualizarDisplayPeso();

  if (bt.available()) {
    byte recebido = bt.read();
    Serial.print("[BT RX] Byte recebido: 0x"); Serial.println(recebido, HEX);
    if (recebido == 0x05 || recebido == 0x04) {
      if ((protocoloSelecionado == PROT3 && peso > LIMITE_PESO_PROT3) ||
          (protocoloSelecionado == URANO12 && peso > LIMITE_PESO_URANO12)) {
        enviarStatus(bt, 'S');
      } else if (millis() - ultimaMovimentacao < TEMPO_INSTABILIDADE) {
        enviarStatus(bt, 'I');
      } else {
        if (protocoloSelecionado == PROT3) {
          enviarProt3(bt, peso);
        } else {
          enviarUrano12(bt, peso);
        }
      }
    }
  }

  delay(1000);
}

void escolherProtocolo() {
  inicioEscolha = millis();
  protocoloConfirmado = false;
  display.fillScreen(0);
  display.setCursor(0, 0);
  display.print("Selecione:");
  display.setCursor(0, 10);
  display.print(nomesProtocolos[protocoloIndex]);

  while (!protocoloConfirmado && millis() - inicioEscolha < TEMPO_ESCOLHA_PROTOCOLO) {
    debouncer.update();
    lerEncoderProtocolo();
  }

  protocoloSelecionado = static_cast<Protocolo>(protocoloIndex);
}

void lerEncoderProtocolo() {
  static int lastCLK = HIGH;
  static unsigned long ultimaLeitura = 0;

  int currentCLK = digitalRead(ENCODER_CLK);
  int currentDT  = digitalRead(ENCODER_DT);

  if (currentCLK != lastCLK && (millis() - ultimaLeitura) > 100) {
    if (currentDT != currentCLK) {
      protocoloIndex = (protocoloIndex + 1) % 2;
    } else {
      protocoloIndex = (protocoloIndex + 1 + 2) % 2;
    }
    display.fillRect(0, 10, 96, 10, 0);
    display.setCursor(0, 10);
    display.print(nomesProtocolos[protocoloIndex]);
    inicioEscolha = millis();
    ultimaLeitura = millis();
  }

  lastCLK = currentCLK;

  if (debouncer.fell()) {
    protocoloConfirmado = true;
  }
}

void lerEncoder() {
  long novaPosicao = encoder.read() / 4;

  if (novaPosicao != ultimaPosicao) {
    int diff = novaPosicao - ultimaPosicao;
    Serial.print("[ENCODER] Movimento detectado: "); Serial.println(diff);
    peso += diff * 10;
    if (peso < 0) peso = 0;
    ultimaMovimentacao = millis();
    ultimaPosicao = novaPosicao;
  }
}

void atualizarDisplayPeso() {
  display.fillRect(0, 30, 96, 10, 0);
  display.setCursor(0, 30);
  display.print("Peso: ");
  display.print(peso / 1000.0, 2);
  display.print(" kg");
}

void enviarStatus(Stream &serial, char c) {
  Serial.println("[BT] Enviando status...");
  char buffer[7];
  buffer[0] = 0x02;
  for (int i = 1; i <= 5; i++) buffer[i] = c;
  buffer[6] = 0x03;
  serial.flush();
  serial.write((uint8_t*)buffer, 7);
  serial.flush();
  Serial.println("[BT] Status enviado.");
}

void enviarProt3(Stream &serial, int gramas) {
  Serial.print("[BT] START\n");
  char buffer[8]; // 1 byte para 0x02, 5 para peso, 1 para 0x03, 1 para '\0'
  buffer[0] = 0x02;
  sprintf(&buffer[1], "%05d", gramas);
  buffer[6] = 0x03;
  buffer[7] = '\0';
  serial.flush();
  serial.write((uint8_t*)buffer, 7); // envia os 7 bytes (0x02 + 5 dígitos + 0x03)
  serial.flush();
  Serial.print(" -> buffer: "); Serial.println(&buffer[1]);
  Serial.println("[BT] END");
}

void enviarUrano12(Stream &serial, int gramas) {
  float kg = gramas / 1000.0;
  char pesoStr[7];
  sprintf(pesoStr, "%6.3f", kg);

  // Monta todo o comando em um buffer antes de enviar
  char buffer[64];
  int idx = 0;

  // Sequência de comandos de configuração
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "T1", 2); idx += 2;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "A13", 3); idx += 3;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "N0", 2); idx += 2;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "S2", 2); idx += 2;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "D4", 2); idx += 2;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "Q19", 3); idx += 3;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "B", 1); idx += 1;

  // Dados de peso
  char estabilidade = (millis() - ultimaMovimentacao < TEMPO_INSTABILIDADE) ? ' ' : '*';
  char sinal = (peso >= 0) ? ' ' : '=';

  buffer[idx++] = estabilidade;
  buffer[idx++] = sinal;
  memcpy(&buffer[idx], "PESO: ", 6); idx += 6;
  memcpy(&buffer[idx], pesoStr, 6); idx += 6;
  buffer[idx++] = 'k';

  // Finalização
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "E", 1); idx += 1;
  buffer[idx++] = 0x1B; memcpy(&buffer[idx], "P01", 3); idx += 3;

  serial.write((uint8_t*)buffer, idx);

  Serial.print(" -> pesoStr: "); Serial.println(pesoStr);
}