#include <Servo.h>
#include <SoftwareSerial.h>

/* Pinos para teste das funções
#define  ledF  4
#define  ledD  5
#define  ledE  6
#define  ledS  7
*/

//Código de Júlio
#define input1   11    //Pino PWM
#define input4   6    //Pino PWM
#define enable1  13
#define enable2  4
//Código de Júlio

const int rx = 2;
const int tx = 3;
SoftwareSerial blth(rx, tx);

Servo mservo;
int pos = 90;
int cont = 0;


void setup(){
  //Código de Júlio
  pinMode(input1, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(enable2, OUTPUT);
  //Código de Júlio
  
  /* Para teste das funções
  pinMode(ledF, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(ledE, OUTPUT);
  pinMode(ledS, OUTPUT);
  */
  
  blth.begin(115200);
  mservo.attach(10);        //Usando o pino 10 para controlar o servo
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
        mservo.write(90+cont);
        delay(15);
      }
      ligaSobe();
      for(cont = 1; cont<=45; cont++){
        mservo.write(135-cont);
        delay(15);
      }
    }
  }
}

void ligaFrente(){
  /*digitalWrite(ledF, HIGH);
  delay(2500);
  digitalWrite(ledF, LOW);*/
  digitalWrite(enable2, HIGH);
  digitalWrite(enable1, HIGH);
  analogWrite(input4,250);
  analogWrite(input1,250);
  delay(2000);
  analogWrite(input4,0);
  analogWrite(input1,0);
  digitalWrite(enable2, LOW);
  digitalWrite(enable1, LOW);
  return;
}

void ligaDireita(){
  /*digitalWrite(ledD, HIGH);
  delay(2500);
  digitalWrite(ledD, LOW);*/
  analogWrite(input1,250);
  digitalWrite(enable1, HIGH);
  analogWrite(input4,100);
  digitalWrite(enable2, HIGH);
  delay(2000);
  analogWrite(input1,0);
  digitalWrite(enable1, LOW);
  analogWrite(input4,0);
  digitalWrite(enable2, LOW);
  return;
}

void ligaEsquerda(){
  /*digitalWrite(ledE, HIGH);
  delay(2500);
  digitalWrite(ledE, LOW);*/
  analogWrite(input1,100);
  digitalWrite(enable1, HIGH);
  analogWrite(input4,250);
  digitalWrite(enable2, HIGH);
  delay(2000);
  analogWrite(input1,0);
  digitalWrite(enable1, LOW);
  analogWrite(input4,0);
  digitalWrite(enable2, LOW);
  return;
}

void ligaSobe(){
  /*digitalWrite(ledS, HIGH);
  delay(2500);
  digitalWrite(ledS, LOW);*/
  ligaFrente();
  return;
}
