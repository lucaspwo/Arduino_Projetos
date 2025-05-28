#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);
  bt.begin(115200); // Baudrate padrão do RN-42 (BlueSMiRF Silver)

  Serial.println("Iniciando configuração Bluetooth...");
  delay(1000);

  // Entrar no modo comando
  bt.print("$$$");
  delay(500); // Aguardar resposta "CMD"
  Serial.println("Enviado: $$$ (modo comando)");

  // Mudar o nome
  bt.println("SN,BT_URANO");
  delay(200);
  Serial.println("Enviado: SN,BT_URANO");

  // Salvar e sair
  bt.println("---");
  Serial.println("Enviado: --- (sair do modo comando)");

  Serial.println("Configuração finalizada.");
}

void loop() {
  // Exibir qualquer retorno do módulo no Monitor Serial
  if (bt.available()) {
    Serial.write(bt.read());
  }
}
