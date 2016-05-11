/**
* Example: Hello, MySQL!
*
* This code module demonstrates how to create a simple
* database-enabled sketch.
*/
#include "SPI.h"
#include "Ethernet.h"
#include "sha1.h"
#include "mysql.h"

/* Setup for Ethernet Library */
byte mac_addr[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9 };
IPAddress server_addr(192, 168, 0, 106);

/* Setup for the Connector/Arduino */
Connector my_conn; // The Connector/Arduino reference
char user[] = "arduino";
char password[] = "senha";

void setup() {
 Ethernet.begin(mac_addr);
 Serial.begin(9600);
 while (!Serial);
 delay(1000);
 Serial.println("Connecting...");
 if (my_conn.mysql_connect(server_addr, 3306, user, password)){
 Serial.println("Success!");
 } else {
 Serial.println("Connection failed.");
 }
}

void loop() {
}
