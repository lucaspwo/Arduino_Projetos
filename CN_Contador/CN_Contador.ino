#include <StopWatch.h>  // Inclusão da biblioteca do contador

StopWatch SW;  // Declaração do contador SW (nome do stopwatch)
char c;  // Variável para armazenar o comando da serial
float tempo;  // Float para armazenar o tempo contado
float t_old = 0;  // Float para armazenar um valor anterior ao atual

void setup(){
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() >0){  // Monitoramento da serial
    c = Serial.read();  // Leitura
    if(c == '1'){
      SW.start();  // Inicialização do contador
    }
    if(c == '2'){
      tempo = SW.elapsed();  // Leitura do valor decorrido
      tempo = tempo/1000;  // Transformação do valor lido de milisegundos para segundos
      Serial.println((tempo - t_old)); // Exibição do tempo parcial (volta)
      t_old = tempo;
    }
    if(c == '0'){
      SW.stop();  // Pausa do contador
      tempo = SW.elapsed();
      tempo = tempo/1000;
      Serial.println(tempo);
      SW.reset();  // Reset do contador
      t_old = 0;
    }
  }
}
