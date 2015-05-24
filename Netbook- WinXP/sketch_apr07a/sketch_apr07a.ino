#define  Vd  5
#define  Vm  7

#define  Vcc  53
#define  Gnd  47

#define  Up   49
#define  Ctr  51

int i = 0;
int j = 255;
boolean up,ctr = false;


void setup() {
  pinMode(Vd, OUTPUT);
  pinMode(Vm, OUTPUT);
  pinMode(Vcc, OUTPUT);
  pinMode(Gnd, OUTPUT);
  pinMode(Up, INPUT);
  pinMode(Ctr, INPUT);
  
  digitalWrite(Gnd, LOW);
  digitalWrite(Vcc, HIGH);
}

void loop() {
  up = digitalRead(Up);
  if(up == false){
    digitalWrite(Vm, LOW);
    digitalWrite(Vd, HIGH);
    i = 0;
    j = 255;
    do{      
      up = digitalRead(Up);
      if(i < 255 && j == 255){
        analogWrite(Vd, i);
        i++;
      }
      if(i == 255 && j > 0){
        analogWrite(Vd, j);
        j--;
        if(i == 255 && j == 0){
          i = 0;
          j = 255;
        }
      }
      delay(10);
    } while(up == false);
  }
  else{
    analogWrite(Vd, 0);
  }
  
  ctr = digitalRead(Ctr);
  if(ctr == false){
    digitalWrite(Vd, LOW);
    digitalWrite(Vm, HIGH);
    i = 0;
    j = 255;
    do{
      ctr = digitalRead(Ctr);      
      if(i < 255 && j == 255){
        analogWrite(Vm, i);
        i++;
      }
      if(i == 255 && j > 0){
        analogWrite(Vm, j);
        j--;
        if(i == 255 && j == 0){
          i = 0;
          j = 255;
        }
      }
      delay(10);
    } while(ctr == false);
  }
  else{
    analogWrite(Vm, 0);
  }
}
