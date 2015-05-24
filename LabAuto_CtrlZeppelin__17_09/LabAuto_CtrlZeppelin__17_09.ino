#include <Servo.h>
#include <SoftwareSerial.h>

#define  ledF  4
#define  ledD  5
#define  ledE  6
#define  ledS  7

const int rx = 2;
const int tx = 3;
SoftwareSerial blth(rx, tx);

Servo mservo;
int pos = 90;
int cont = 0;


void setup(){
  pinMode(ledF, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);
  pinMode(ledS, OUTPUT);
  blth.begin(115200);
  mservo.attach(10);
  mservo.write(pos);
  blth.println("Iniciando...");
}

void loop(){
  if(blth.available()){
    char c = (char)blth.read();
    if(c == 'f'){          //Comando para ir para frente
      ligaFrente();
    }
    if(c == 'd'){          //Comando para ir para direita
      ligaDireita();
    }
    if(c == 'e'){          //Comando para ir para esquerda
      ligaEsquerda();
    }
    if(c == 's'){          //Comando para subir
      for(cont = 1; cont<=45; cont++){
        mservo.write(90-cont);
        delay(15);
      }
      ligaSubir();
      for(cont = 1; cont<=45; cont++){
        mservo.write(45+cont);
        delay(15);
      }
    }
  }
}

void ligaFrente(){
  digitalWrite(ledF, HIGH);
  delay(2500);
  digitalWrite(ledF, LOW);
  return;
}

void ligaDireita(){
  digitalWrite(ledD, HIGH);
  delay(2500);
  digitalWrite(ledD, LOW);
  return;
}

void ligaEsquerda(){
  digitalWrite(ledE, HIGH);
  delay(2500);
  digitalWrite(ledE, LOW);
  return;
}

void ligaSubir(){
  digitalWrite(ledS, HIGH);
  delay(2500);
  digitalWrite(ledS, LOW);
  return;
}
