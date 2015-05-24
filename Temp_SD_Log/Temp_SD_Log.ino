#include <OneWire.h>
#include <SD.h>

File  templog;
OneWire  ds(9);  // on pin 10 (a 4.7K resistor is necessary)
char nome[15];
uint8_t j;
int a = 1;
//char nome[8];
//char csv[] = ".csv";
//char* file_name[1];

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  if (!SD.begin(4)){
    Serial.println("Erro no SD");
    return;
  }
  Serial.println("SD OK");
  initialise();
}

void loop() {
  if(a == 1){
    templog = SD.open(nome, FILE_WRITE);
    if(!templog){
      Serial.println("Erro na criacao do arquivo");
    }
    Serial.println("Arquivo criado");
    a = 0;
  }
  readTemp();
}

/*void readData(){
  String content = "";
  char character;
  delay(5000);
  while(Serial.available()){
      character = Serial.read();
      content.concat(character);
  }
  if(content != ""){
    Serial.println(content);
    content.toCharArray(nome, 8);
  }
  char temp[12];
  for(int i=0; i<8;i++){
    temp[i] = nome[i];
  }
  for(int i=8; i<=11;i++){
    temp[i] = csv[i];
    //imprimir aqui a string armazenada em temp
  }
  file_name[1] = temp;
  myFile = SD.open(file_name[1], FILE_WRITE);  
}*/

void initialise(){
  strcpy(nome, "tmpLog00.txt");
  for(j=0; j<100; j++){
    nome[6] = '0' + j/10;
    nome[7] = '0' + j%10;
    if(!SD.exists(nome)){
      break;
    }
  }
}

void readTemp(){  
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;
  
  if ( !ds.search(addr)) {
    ds.reset_search();
    return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44);
  
  delay(800);
  
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;
  Serial.println(celsius,3);
  //Serial.println(" C");
  if(templog){
    Serial.println("Escrevendo no SD");
    templog.println(celsius,3);
    templog.flush();
    //templog.close();
  } else{
    Serial.println("Erro escrevendo no SD");
  }
}
