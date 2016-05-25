#include <Arduino.h>

#include <SPI.h>
//#include <Ethernet.h>
//#include <sha1.h>
//#include <avr/pgmspace.h>
//#include <mysql.h>
//#include <stdlib.h>
#include <MFRC522.h>
//#include <Wire.h>
//#include <SoftwareSerial.h>

//#define enderecoI2C 0x68

#define SS_PIN 10
#define RST_PIN 9

//byte segundo, minuto, hora, diaDaSemana, diaDoMes, mes, ano;

/*byte mac_addr[] = {0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9}; //endereço MAC do arduino
IPAddress server_addr(192,168,0,106);		//endereço de IP do Raspberry Pi
char user[] = "arduino";				//nome de usuário para acessar a database
char password[] = "senha";				//senha do usuário

Connector my_conn; 						//cria um objeto da conexão, da biblioteca
*/

//bool flag = false;

MFRC522 mfrc522(SS_PIN, RST_PIN);

//SoftwareSerial sSerial(7, 6); //RX, TX

void setup(){
	SPI.begin();
	//Wire.begin();
	mfrc522.PCD_Init();
	Serial.begin(9600);
	//Ethernet.begin(mac_addr);
	while (!Serial) {
 		; // wait for serial port to connect. Needed for Leonardo only
	}
	//sSerial.begin(9600);
	delay(1000);
	/*Serial.println("Conectando a database...");
	if (my_conn.mysql_connect(server_addr, 3306, user, password)) {
  		delay(1000);
	}
	else
  		Serial.println("Conexao falhou.");
  	*/
}

void loop(){
	if (mfrc522.PICC_IsNewCardPresent()){
	String tag = "";
   	//flag = true;
    if (mfrc522.PICC_ReadCardSerial()){
    	//Mostra UID na serial
      	//Serial.print("UID da tag :");
   	    byte letra;
      	for (byte i = 0; i < mfrc522.uid.size; i++){
        	//Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        	Serial.print(mfrc522.uid.uidByte[i], DEC);
        	//tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        	tag.concat(String(mfrc522.uid.uidByte[i], DEC));
        }
        Serial.println();
    }/*
    char tagC[12];
    char query[69];
    leHora(query);
    tag.toCharArray(tagC, 14* sizeof(unsigned int));
    strcat(query, ", ");
	strcat(query, tagC);
	strcat(query, ")");
	Serial.println(String(query));
	my_conn.cmd_query(query);
	//sSerial.print(String(query));
	//Wire.beginTransmission(4);
	//Wire.write(String(query).c_str());
	//Wire.endTransmission();
	//flag = false;*/
	//sSerial.print(tag);
	delay(1000);
  }
}
/*
void leHora(char *_query){
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
  	strcat(_query, "INSERT INTO dbteste.log2 VALUES ('");
  	char anoC[12];
  	itoa((int)ano, anoC, 10);
  	strcat(_query, "20");
  	strcat(_query, anoC);
  	strcat(_query, "-");
  	ajustaMes.toCharArray(mesC, 2* sizeof(unsigned int));
  	strcat(_query, mesC);
  	strcat(_query, "-");
  	ajustaDiaDoMes.toCharArray(diaC, 2* sizeof(unsigned int));
  	strcat(_query, diaC);
  	strcat(_query, " ");
  	ajustaHora.toCharArray(horaC, 2* sizeof(unsigned int));
  	strcat(_query, horaC);
  	strcat(_query, ":");
  	ajustaMinuto.toCharArray(minC, 2* sizeof(unsigned int));
  	strcat(_query, minC);
  	strcat(_query, ":");
  	ajustaSegundo.toCharArray(segC, 2* sizeof(unsigned int));
  	strcat(_query, segC);
  	strcat(_query, "'");
}*/

/*
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

byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}*/

/* Função que realiza uma conversão de Binário para Decimal.
   Utilizada na impressão dos dados na tela do Monitor Serial.
*/
 /*
byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}*/

/* Essa função insere o dígito "0" à esquerda dos dados gravados no módulo com
   apenas um dígito, já que os valores menores que 10 são armazenados no módulo
   com apenas um dígito.
*/
   /*
String ajustaZero(byte dado){
  String dadoAjustado;
  if (dado < 10)
  {
    dadoAjustado += "0";  //concatena o dígito "0" ao valor da variável.
  }
  dadoAjustado += dado;   //concatena o dígito "0" ao valor do dado.

  return dadoAjustado;    //retorna o valor do dado ajustado.
}*/
