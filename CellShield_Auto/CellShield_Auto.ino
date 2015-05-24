#include <SoftwareSerial.h>
#include <string.h>

//char incoming_char=0;
char vindo[100];
int a = 0;

SoftwareSerial cell(2,3); //Rx,Tx


void setup(){
  
  Serial.begin(9600);
  cell.begin(9600);
  Serial.println("Iniciando...");
  
}

void loop(){
  
  if(cell.available() > 0){
    //while(cell.available()){
    char incoming_char = (char)cell.read();
    Serial.print(incoming_char);
    vindo[a] = incoming_char;
    a++;
  }
  
  if(vindo[0] == '+'){
    if(vindo[1] == 'S'){
      if(vindo[2] == 'I'){
        if(vindo[3] == 'N'){
          if(vindo[4] == 'D'){
            if(vindo[5] == ':'){
              for(int i = 0; i < 6; i++){
                Serial.print(vindo[i]);
              }/*
              if(vindo[6] == 32){
                if(vindo[7] == '1'){
                  if(vindo[8] == '1'){
                    Serial.println("Pronto!");
                  }
                }else{
                  a = 0;
                }
              }*/
            }
          }
        }
      }
    }
  }
  
  if(Serial.available() > 0){
    char incoming_char = Serial.read();
    cell.print(incoming_char);
    a = 0;
  }
  
}
