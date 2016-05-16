#include <Arduino.h>

#include "SPI.h"
#include "Ethernet.h"
#include "sha1.h"
//#include <avr/pgmspace.h>
#include "mysql.h"
#include <SoftwareSerial.h>
#include <Wire.h>
#include <stdlib.h>

#define enderecoI2C 0x68

byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;

byte mac_addr[] = {0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9}; //endereço MAC do arduino
IPAddress server_addr(192,168,0,106);		//endereço de IP do Raspberry Pi

Connector my_conn;            //cria um objeto da conexão, da biblioteca

char user[] = "arduino";				//nome de usuário para acessar a database
char password[] = "senha";				//senha do usuário

SoftwareSerial sSerial(5, 6); //RX, TX

bool flag = false;

//String _query = "";
char _tag[11], tag[12];

void setup(){
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  //Wire.onReceive(receiveEvent);
  Ethernet.begin(mac_addr);
  Wire.begin();
	sSerial.begin(9600);
	delay(1000);
	//Serial.println("Conectando a database...");
	if (my_conn.mysql_connect(server_addr, 3306, user, password)) {
    digitalWrite(7, HIGH);
    //Serial.println("Conectado!");
  	delay(1000);
	}
	else{
  	//Serial.println("Conexao falhou.");
    digitalWrite(6, HIGH);
  }
}

void loop(){
  if(Serial.available()){
    flag = true;
    for(int i = 0; i<11; i++){
      _tag[i] = (char)sSerial.read();
      delay(100);
    }
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }
  if(flag == true){
    //char _query[68];
    //query.toCharArray(_query, sizeof(query) * sizeof(unsigned int));
    /*char _tag[sizeof(tag)];
    for(int i = 0; i<sizeof(tag); i++){
      _tag[i] = 
    }*/
    for(int i = 0; i<11; i++){
      tag[i] = _tag[i];
      if(i == 10)
        tag[i+1] = ')';
      //Serial.print(tag[i]);
    }
    //Serial.println();
    char query[68] = "INSERT INTO dbteste.log2 VALUES ('"; //_query[68];
    digitalWrite(6, HIGH);
    char dttime[20];
    leHora(dttime);
    //leHora(query);
    strcat(query, dttime);
    strcat(query, ", ");
    strcat(query, tag);
    //for(int i = 1; i<67; i++)
      //_query[i] = query[i];
    /*for(int i = 0; i<68; i++){
      Serial.print(query[i]);
    }
    Serial.println();*/
    //Serial.println(String(query));
    my_conn.cmd_query(query);
    digitalWrite(7, HIGH);
    //tag = "";
    //my_conn.cmd_query(query);
    flag = false;
  }
}

void do_query(const char *q) {
  column_names *c; // pointer to column values
  row_values *r;   // pointer to row values

  // First, execute query. If it returns a value pointer,
  // we have a result set to process. If not, we exit.
  if (!my_conn.cmd_query(q)) {
    return;
  }

  // Next, we read the column names and display them.
  //
  // NOTICE: You must *always* read the column names even if
  //         you do not use them. This is so the connector can
  //         read the data out of the buffer. Row data follows the
  //         column data and thus must be read first.
  c = my_conn.get_columns();
  for (int i = 0; i < c->num_fields; i++) {
    Serial.print(c->fields[i]->name);
    if (i < c->num_fields - 1) {
      Serial.print(",");
    }
  }
  Serial.println();

  // Next, we use the get_next_row() iterator and read rows printing
  // the values returned until the get_next_row() returns NULL.
  int num_cols = c->num_fields;
  int rows = 0;
  do {
    r = my_conn.get_next_row();
    if (r) {
      rows++;
      for (int i = 0; i < num_cols; i++) {
        Serial.print(r->values[i]);
        if (i < num_cols - 1) {
          Serial.print(", ");
        }
      }
      Serial.println();
      // Note: we free the row read to free the memory allocated for it.
      // You should do this after you've processed the row.
      my_conn.free_row_buffer();
    }
  } while (r);
  Serial.print(rows);
  Serial.println(" rows in result.");

  // Finally, we are done so we free the column buffers
  my_conn.free_columns_buffer();
}
/*
void receiveEvent(int numBytes){
  flag = true;
  query = "";
  while(Wire.available()){
  //for(int i = 0; i<numBytes; i++){
    //query += (char)Wire.read();
    Serial.print((char)Wire.read());
  }
  Serial.println();
}*/

void leHora(char *_dttime){
    String ajustaSegundo;
    String ajustaMinuto;
    String ajustaHora;
    String ajustaDiaDoMes;
    String ajustaMes;

    char horaC[12], minC[12], segC[12], diaC[12], mesC[12];

    Wire.beginTransmission(enderecoI2C); //Abrindo o modo I2C no modo de gravação.
    Wire.write((byte)0x00); //Redefinindo o ponteiro para o primeiro registro (0x00).
    Wire.endTransmission(); //finalizando o modo de gravação.
    Wire.requestFrom(enderecoI2C, 7);    //Abrindo o modo I2C no modo de leitura.

    segundo = bcdToDec(Wire.read() & 0x7f); //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. 
    minuto = bcdToDec(Wire.read());         //convertendo os minutos. 
    hora = bcdToDec(Wire.read() & 0x3f);    //Alguns dados precisam de máscaras antes 
                                          //da conversão porque certos bits são 
                                          //bits de controle. Essa máscara define o
                                          //relógio para trabalhar no modo de 24h.
    diaDaSemana = bcdToDec(Wire.read());    //dia da semana, onde domingo começa com "0".
    diaDoMes = bcdToDec(Wire.read());       //convertendo o dia do mês.
    mes = bcdToDec(Wire.read());            //convertendo o mês.
    ano = bcdToDec(Wire.read());            //convertendo o ano.
    ajustaHora += ajustaZero(hora);
    //Serial.print(ajustaHora);
    //Serial.print(":");
    ajustaMinuto += ajustaZero(minuto);
    //Serial.print(ajustaMinuto);
    //Serial.print(":");
    ajustaSegundo += ajustaZero(segundo);
    //Serial.print(ajustaSegundo);
    ajustaDiaDoMes += ajustaZero(diaDoMes);
    //Serial.print(" ");
    //Serial.print(ajustaDiaDoMes);
    ajustaMes += ajustaZero(mes);
    //Serial.print("/");
    //Serial.print(ajustaMes);
    //Serial.print("/");
    //Serial.println(ano);
    //strcat(_query, "INSERT INTO dbteste.log2 VALUES ('");
    char anoC[12];
    itoa((int)ano, anoC, 10);
    strcat(_dttime, "20");
    strcat(_dttime, anoC);
    strcat(_dttime, "-");
    ajustaMes.toCharArray(mesC, 2* sizeof(unsigned int));
    strcat(_dttime, mesC);
    strcat(_dttime, "-");
    ajustaDiaDoMes.toCharArray(diaC, 2* sizeof(unsigned int));
    strcat(_dttime, diaC);
    strcat(_dttime, " ");
    ajustaHora.toCharArray(horaC, 2* sizeof(unsigned int));
    strcat(_dttime, horaC);
    strcat(_dttime, ":");
    ajustaMinuto.toCharArray(minC, 2* sizeof(unsigned int));
    strcat(_dttime, minC);
    strcat(_dttime, ":");
    ajustaSegundo.toCharArray(segC, 2* sizeof(unsigned int));
    strcat(_dttime, segC);
    strcat(_dttime, "'");
}

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}
 
/* Função que realiza uma conversão de Binário para Decimal.
   Utilizada na impressão dos dados na tela do Monitor Serial.
*/
byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}

/* Essa função insere o dígito "0" à esquerda dos dados gravados no módulo com 
   apenas um dígito, já que os valores menores que 10 são armazenados no módulo
   com apenas um dígito.  
*/
String ajustaZero(byte dado){
  String dadoAjustado;
  if (dado < 10) 
  {
    dadoAjustado += "0";  //concatena o dígito "0" ao valor da variável.
  }
  dadoAjustado += dado;   //concatena o dígito "0" ao valor do dado.
  
  return dadoAjustado;    //retorna o valor do dado ajustado.
}