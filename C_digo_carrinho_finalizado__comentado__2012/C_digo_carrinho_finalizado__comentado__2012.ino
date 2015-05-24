#include <AFMotor.h>                      //Inclusão da biblioteca do Motor Shield

AF_DCMotor motor1(1, MOTOR12_1KHZ);       //Declaração do motor DC na entrada M1, com frequência à 1 (um) kHz
AF_DCMotor motor2(4);       //Declaração do motor DC na entrada M2, com frequência à 1 (um) kHz

int a = 1;
int bot = 0;
int val = 0;
int valA1 = 0;
int valA2 = 0;
int crsh = 0;
int dntcrsh = 0;
int contE = 1;
int contD = 1;

void setup(){
  motor1.setSpeed(84);                    //Velocidade maior para diminuição do descompasso dos motores DC
  motor2.setSpeed(80);
  Serial.begin(9600);
}

void loop(){
  
  if(a == 1) {
    delay(2000);                          //Delay para posicionamento do carrinho (ocorre apenas no início do código, não do loop em si)
  }
  a = 0;
  
  motor1.run(FORWARD);
  motor2.run(FORWARD);
//  delay(100);
  
  bot = analogRead(1);                    //Primeira verificação do estado do botão
  if(bot > 10){                           //Verificação do pressionamento do botão pela porta analógica
    Serial.println("CRASH - bot");
    crash(); 
  }
  
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  val = analogRead(0);
  valA1 = valA1 + val;
  valA1 = valA1/5;                        //Determinação de uma primeira média a partir de 5 valores lidos pelo sensor
  Serial.print("valA1 = ");
  Serial.print(valA1);
  Serial.print("\n");
  
  delay(500);                             //Delay para garantir uma leitura diferente de valores pelo sensor
  
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  val = analogRead(0);
  valA2 = valA2 + val;
  valA2 = valA2/5;                        //Determinação de uma segunda média a partir de 5 outros valores lidos pelo sensor
  Serial.print("valA2 = ");
  Serial.print(valA2);
  Serial.print("\n");
  
  bot = analogRead(1);                    //Segunda verificação do estado do botão
  if(bot > 10){
    Serial.println("CRASH - bot");
    crash();  
  }
  
  val = analogRead(0);
  
  if(val > 349){                          //Leitura do sensor para casos de proximidade extrema do sensor à algum obstáculo
    Serial.println("CRASH - val");
    crash();
  }
  
  if(valA1 > valA2+20){                   //Verificação de proximidade para distâncias inferiores à 20cm (tolerância de 20 bits da leitura)
    crsh = crsh + 1;                      //Contador para a condição de batida (iminente)
    
    if(crsh > 4){                         //Verificação de possível batida iminente caso a leitura acuse aproximação em distâncias inferiores à
      Serial.println("CRASH - valA");     //20cm, por 5 vezes seguidas
      crash;
      crsh = 0;                           //Zerando o contador
    }
    
   }
   
   else{
     dntcrsh = dntcrsh + 1;               //Contador para a condição de não-batida (iminente)
     
     if(dntcrsh > 4){                     //Verificação de condição de não-batida iminente. Para caso o carrinho se afaste do obstáculo,
       crsh = 0;                          //que antes estava próximo
     }                                    //Zerando o contador de iminência de batida
     
   }
  
  bot = analogRead(1);                    //Terceira verificação do estado do botão
  if(bot > 10){
    Serial.println("CRASH - bot");
    crash();  
  }
  
}

void turn90(int dir){                     //Função para giro do carrinho, com o argumento sendo a direção
  int time = 750;
  float timer = 0;
  motor1.setSpeed(80);
  motor2.setSpeed(80);
  if(dir == 0){                           //Giro à direita (argumento 0)
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(time);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    contD = contD + 1;                    //Contador de giros à direita
    contE = 1;                            //Zerando o contador de giros à esquerda
  }
  if(dir == 1){                           //Giro à esquerda (argumento 1)
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(time);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    contE = contE + 1;                    //Contador de giros à esquerda
    contD = 1;                            //Zerando o contador de giros à direita
  }
  if(dir == 2){                           //Giro de 180 graus
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(time*2);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  } 
}

void crash(){                             //Função para a condição de batida
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE); 
  if((contE < 4) && (contD < 4)){         //Verificação de giros consecutivos à esquerda ou direita
    if(random(1, 11) == 5){               //Geração de um número aleatório de 1 à 10. Entra na condição se igual à 5
      turn90(2);                          //Giro de 180 graus
    }
    else{                                 //Condição para caso o número aleatório seja diferente de 5
      turn90(random(0,2));                //Girar para um lado aleatório (esquerda ou direita) de acordo com outro número aleatório (0 ou 1)
    }
  }
  if(contE == 4){                         //Caso tenha havido 4 giros seguidos à esquerda...
    turn90(0);                            //... girar à direita
    contE = 1;                            //Zerar o contador após a ação
  }
  if(contD == 4){                         //Caso tenha havido 4 giros seguidos à direita...
    turn90(1);                            //... girar à esquerda
    contD = 1;                            //Zerar o contador após a ação
  }
}
