#include  <OneWire.h>    //Para a leitura do termômetro
#include  <SD.h>        //Para a escrita no cartão SD

#define  REFRESH_TIME 1000    //Tempo de refresh  do sensor de efeito Hall

long  lastRefresh;   
float radius = 0.12/2; //Raio de um DVD em metros
float  circMetric = 2*3.14*radius; 
float  speedk;            
long  loopCount;         

File  datalog;
char  nome[15];    //Para o funcionamento do cartão SD
const int  SDCS = 53;

OneWire  ds(17);    //A porta do sensor de temperatura


uint8_t  j;    //Para a função initialise()
int  a = 1;    //Variável para executar a função initialise() apenas uma vez
int  b = 1;    //Variável para controlar a quantidade de vezes que o código de Caio é acessado em um loop

void setup(){
  attachInterrupt(4, speedCalc, RISING);
  loopCount = 0;
  lastRefresh = millis();                //Para o código de Caio
  speedk = 0.0;
  
  Serial.begin(9600);    //Para debug no PC
  Serial3.begin(9600);    //Para o envio no APC
  pinMode(53, OUTPUT);    //Inicialização da porta para a biblioteca SD.h
  
  if(!SD.begin(SDCS)){
    Serial.println("Erro no SD");
    return;                        //Inicialização do cartão SD
  } else{
    Serial.println("SD ok");
  }
  initialise();    //Chama a função que lida com a nomenclatura dos arquivos
}

void loop(){
  if(a == 1){
    datalog = SD.open(nome, FILE_WRITE);
    if(!datalog){
      Serial.println("Erro na criacao do arquivo");    //Criação do arquivo (uma vez a cada inicialização da placa)
    } else{
      Serial.println("Arquivo criado");
    }
    a = 0;
  }
  readTemp();    //Chama a função que lê, envia e armazena a temperatura
  readVel();    //Chama a função que lê, envia e armazena a velocidade
}

void initialise(){
  strcpy(nome, "bkpLog00.txt");
  for(j=0; j<100; j++){
    nome[6] = '0' + j/10;        //Função para lidar com a nomenclatura dos arquivos
    nome[7] = '0' + j%10;
    if(!SD.exists(nome)){
      break;
    }
  }
}

void readTemp(){    //Função para tratar a temperatura
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
  ds.write(0xBE);
  for ( i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3;
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;
    else if (cfg == 0x20) raw = raw & ~3;
    else if (cfg == 0x40) raw = raw & ~1;
  }
  celsius = (float)raw / 16.0;    //Armazena a temperatura num float
  Serial3.print(celsius);    //Envia a temperatura como string
  Serial.println(celsius);
  if(datalog){
    Serial.println("Escrevendo a temp. no SD");
    datalog.print(celsius);    //Armazena a temperatura no cartão
  } else{
    Serial.println("Erro escrevendo a temp. no SD");
  }
  b = 1;
}

void speedCalc(){    //Código de Caio
  loopCount++;
}

void readVel(){    //Função para ler a velocidade
  if(b == 1){
    if (millis() - lastRefresh >= REFRESH_TIME)
    {
      speedk = (3600*circMetric*loopCount)/(millis() - lastRefresh);
      loopCount = 0;
      lastRefresh = millis();
    }
     Serial3.print(",");
     Serial3.println(speedk);    //Envio da velocidade como uma string
     Serial.println(speedk);
   if(datalog){
     Serial.println("Escrevendo a vel. no SD");
     datalog.print(",");          //Separando os valores com uma vírgula, no cartão SD
     datalog.println(speedk);    //Armazenando a velocidade no cartão
     datalog.flush();
   } else{
     Serial.println("Erro escrevendo a vel. no SD");
   }
   b = 0;
  }
  Serial.println();
}
