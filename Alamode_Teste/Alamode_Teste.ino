#include <SD.h>

char txt[] = ".txt";
File myFile;

void setup(){
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  if(!SD.begin())
    return;
  Serial.print('d');
  char input = Serial.read();
  char* nome[8] = {(input + txt)};
  myFile = SD.open(nome[8], FILE_WRITE);
}

void loop(){
  if (myFile){
    for(int i=0; i<5; i++){
      Serial.print('h');
      char hora = Serial.read();
      myFile.write(hora);
      delay(1000);
    }
  }
  myFile.close();
  while (true)
    ;
}
