#include <Servo.h>
#include <SoftwareSerial.h>

#define input1   11    //Pino PWM
#define input4   6     //Pino PWM
#define enable1  13
#define enable2  4

const int rx = 2;
const int tx = 3;
SoftwareSerial blth(rx, tx);

Servo mservo;
int pos = 90;
int cont = 0;


void setup(){
  pinMode(input1, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(enable2, OUTPUT);
  
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
      ligaSobe();
    }
  }
}

void ligaFrente(){
  digitalWrite(enable2, HIGH);      //Habilitando o motor 1
  digitalWrite(enable1, HIGH);      //Habilitando o motor 2
  analogWrite(input4,250);          //Setando o valor do PWM para a velocidade do motor 2 (associado ao enable 2)
  analogWrite(input1,250);          //Setando o valor do PWM para a velocidade do motor 1 (associado ao enable 1)
  delay(2000);
  analogWrite(input4,0);            //Desligando os dois motores
  analogWrite(input1,0);
  digitalWrite(enable2, LOW);       //Desabilitando os dois motores
  digitalWrite(enable1, LOW);
  return;
}

void ligaDireita(){
  digitalWrite(enable1, HIGH);
  digitalWrite(enable2, HIGH);
  analogWrite(input1,250);          //Setando a velocidade do motor 1 maior do que a do motor 2 (considerando o motor 1 estando do lado direito)
  analogWrite(input4,100);
  delay(2000);
  analogWrite(input1,0);
  analogWrite(input4,0);
  digitalWrite(enable1, LOW);
  digitalWrite(enable2, LOW);
  return;
}

void ligaEsquerda(){
  digitalWrite(enable1, HIGH);
  digitalWrite(enable2, HIGH);
  analogWrite(input1,100);          //Setando a velocidade do motor 2 maior do que a do motor 1 (considerando o motor 2 estando do lado esquerdo)
  analogWrite(input4,250);
  delay(2000);
  analogWrite(input1,0);
  analogWrite(input4,0);
  digitalWrite(enable1, LOW);
  digitalWrite(enable2, LOW);
  return;
}

void ligaSobe(){
  for(cont = 1; cont<=45; cont++){        //Controle do servo. Saindo de uma posição de 90 para 135...
    mservo.write(90+cont);
    delay(15);
  }
  ligaFrente();                          //... acionamento dos motores...
  for(cont = 1; cont<=45; cont++){       //... retorna o servo para a posição 90
    mservo.write(135-cont);
    delay(15);
  }
  return;
}
