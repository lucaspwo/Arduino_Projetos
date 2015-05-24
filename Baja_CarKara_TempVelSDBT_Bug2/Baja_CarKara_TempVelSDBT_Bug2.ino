#include  <OneWire.h>
#include  <SD.h>

#define  REFRESH_TIME 1000

long  lastRefresh;
float  circMetric = 0.16;
int  speedk;
long  loopCount;

File  datalog;
char  nome[15];
OneWire  ds(9);
int celsius;
const int  SDCS = 4;

uint8_t  j;
int  a = 1;
int  b = 0;

void setup(){
  attachInterrupt(0, speedCalc, RISING);
  loopCount = 0;
  lastRefresh = millis();
  speedk = 0.0;
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(53, OUTPUT);
  if(!SD.begin(SDCS)){
    Serial.println("Erro no SD");
    return;
  } else{ 
    Serial.println("SD ok");
  }
  inicialize();
}

void loop(){
  if(a == 1){
    datalog = SD.open(nome, FILE_WRITE);
    if(!datalog){
      Serial.println("Erro na criacao do arquivo");
    } else{
      Serial.println("Arquivo criado");
    }
    a = 0;
  }
  while(Serial2.read() != 10){
    leiaTemp();
    if(b==1)
      gravaTemp();
    if(b==2)
      leiaVel();
    if(b==3)
      gravaVel();
  }
  leiaTemp();
  gravaTemp();
  enviaTemp();
  leiaVel();
  gravaVel();
  enviaVel();
}

void inicialize(){
  strcpy(nome, "bkpLog00.txt");
  for(j=0; j<100; j++){
    nome[6] = '0' + j/10;
    nome[7] = '0' + j%10;
    if(!SD.exists(nome)){
      break;
    }
  }
}

void leiaTemp(){  
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  
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
  Serial.print("Temp.: ");
  Serial.println(celsius);
  b = 1;
}

void enviaTemp(){
  Serial2.write(celsius);
}

void gravaTemp(){
  if(datalog){
    Serial.println("Escrevendo a temp. no SD");
    datalog.print(celsius);
  } else{
    Serial.println("Erro escrevendo a temp. no SD");
  }
  b = 2;
}

void speedCalc(){
  loopCount++;
}

void leiaVel(){
  if(b == 1){
    if (millis() - lastRefresh >= REFRESH_TIME)
    {
      speedk = (3600*circMetric*loopCount)/(millis() - lastRefresh);
      loopCount = 0;
      lastRefresh = millis();
    } 
      
    Serial.print("Vel.: ");
    Serial.println(speedk);
    b = 3;
  }
}

void enviaVel(){
  Serial2.write(speedk);
}

void gravaVel(){
  if(datalog){
     Serial.println("Escrevendo a vel. no SD");
     datalog.print(",");
     datalog.println(speedk);
     datalog.flush();
   } else{
     Serial.println("Erro escrevendo a vel. no SD");
   }
   b = 4;
}
