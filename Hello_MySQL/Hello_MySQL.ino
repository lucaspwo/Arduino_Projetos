#include <SPI.h>
#include <Ethernet.h>
#include <sha1.h>
#include <mysql.h>

/* Setup for Ethernet Library */
byte mac_addr[] = {0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9};
IPAddress server_addr(189,124,161,43);
IPAddress ip(192,168,1,118);

/* Setup for the Connector/Arduino */
Connector my_conn;    //The Connector/Arduino reference
char user[] = "root";
char password[] = "231091";
char INSERT_SQL[] = "INSERT INTO test_arduino.hello VALUES ('Hello from Arduino!', NULL)";

void setup(){
  Ethernet.begin(mac_addr,ip);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting...");
  if(my_conn.mysql_connect(server_addr, 3306, user, password)){
    delay(500);
    /* Write Hello, to MySQL table test_arduino.hello */
    my_conn.cmd_query(INSERT_SQL);
    Serial.println("Query Success!");
  }
  else
    Serial.println("Connection failed.");
}

void loop(){
}
