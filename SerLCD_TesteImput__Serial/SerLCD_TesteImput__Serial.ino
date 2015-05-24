char str[16];
char str2[34];
int cont = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Iniciando...");
  Serial.println();
}

void loop(){
  if(Serial.available()){
    char c = (char)Serial.read();
    cont++;
    str2[cont] = c;
    if(int(c) == 8){
      for(int i=1;i<cont;i++){
        Serial.print(str2[i-1]);
      }
      Serial.println();
      cont = cont - 2;
    }
    if(cont > 16 && cont <= 32){
      str[cont-17] = c;
    }
    if(cont > 32){
      for(int i = 0;i<16;i++){
        Serial.print(str[i]);
      }
      Serial.println();
      cont = 17;
      str[0] = c;
    }
    if(c == '$'){
      Serial.println();
      cont = 0;
    }
    else{
      Serial.print(c);
    }
  }
}
