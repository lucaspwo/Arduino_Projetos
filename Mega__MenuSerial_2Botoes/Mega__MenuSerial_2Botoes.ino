#define  Vd  5
#define  Vm  7

#define  Vcc  53
#define  Gnd  47

#define  Up   49
#define  Ctr  51

int count = 0;
int a = 0;

boolean btnC, btnU = false;

//char* prgm[] = {"Programa 1", "Programa 2", "Programa 3"};
char* led[] = {"Verde", "Vermelho", "Apagado"};

void setup(){
  Serial.begin(9600);
  pinMode(Vd, OUTPUT);
  pinMode(Vm, OUTPUT);
  pinMode(Vcc, OUTPUT);
  pinMode(Gnd, OUTPUT);
  pinMode(Up, INPUT);
  pinMode(Ctr, INPUT);
  
  digitalWrite(Gnd, LOW);
  digitalWrite(Vcc, HIGH);
}

void loop(){
  if((digitalRead(Ctr) == false)){
    btnC = true;
    while(true){
      while(a == 0){
        Serial.print("***Controles:\nPressione 'UP' para mudar de programa.\nPressione 'CTR' para selecionar.***\n\n");
        delay(500);
        //Serial.print("\nPressione 'CTR' para continuar.***\n\n");
        a++;
        Serial.println("Escolha o programa desejado:");
        //delay(250);
        btnC = false;
      }
      
      if(digitalRead(Up) == false){
        if(count < 3){
          count++;
          btnU = true;
          delay(250);
        }
        else{
        count = 1;
        delay(500);
        }
        Serial.println(led[count-1]);
        btnU = true;
        delay(250);
        //Serial.println(prgm[count-1]); //Substituir linha por "Switch...Case"
      }
      
      if(btnU == true && btnC == false){  
        if(digitalRead(Ctr) == false){
          if(count == 1){
            Serial.println("Verde selecionado");
            //Serial.println("Programa 1 selecionado");
            
            digitalWrite(Vd, LOW);
            digitalWrite(Vm, HIGH);
            btnU = false;
          }
          else if(count == 2){
            Serial.println("Vermelho selecionado");
            //Serial.print(prgm[count-1]);
            //Serial.println(" selecionado");
            
            digitalWrite(Vd, HIGH);
            digitalWrite(Vm, LOW);
            btnU = false;
          }
          else if(count == 3){
            Serial.println("Apagado selecionado");
            digitalWrite(Vd, LOW);
            digitalWrite(Vm, LOW);
            btnU = false;
          }
        }
      }
    }
  }
}
