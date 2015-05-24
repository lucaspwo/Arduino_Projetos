#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>
/*
	Simple Ethernet Test
        Arduino server outputs simple text to browser
	The circuit:
	* Arduino Duemilanove
        * Arduino Ethernet shield
        * Basic FTDI breakout 5V
        *LED connected to GND and digital pin 4 via resistor
        http://www.sciencprog.com/
        Created: 2009.11.18
        By Minde
        Modified: 2011.04.06
          1. Changed obsolete Wstring.h functions to String.h
          2. Changed includes to match Ethernet library.
          3. Fixed LED control
        By Minde
*/

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9 }; //physical mac address
byte ip[] = { 75,4,203,7 };			// ip in lan
byte gateway[] = { 192, 168, 1, 254 };			// internet access via router
byte subnet[] = { 255, 255, 255, 0 };                   //subnet mask
EthernetServer server(80);                                      //server port
byte sampledata=50;            //some sample data - outputs 2 (ascii = 50 DEC)             
int pA = 48;  // LED pin
int pAZ = 47;
int pVD = 46;
int pK = 49;
String readString = String(30); //string for fetching data from address
//boolean LEDON = false; //LED status flag
boolean verm = false;
boolean verd = false;
boolean azul = false;
boolean desl = false;
void setup(){
//start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
//Set pin 4 to output
  pinMode(pA, OUTPUT);
  pinMode(pAZ, OUTPUT);
  pinMode(pVD, OUTPUT);
  pinMode(pK, OUTPUT);
//enable serial datada print  
  Serial.begin(9600);
}
void loop(){
// Create a client connection
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //read char by char HTTP request
        if (readString.length() < 100) 
        {
          //store characters to string 
          readString += c; //replaces readString.append(c);
        }  
        //output chars to serial port
        Serial.print(c);
        //if HTTP request has ended
        if (c == '\n') {
          //dirty skip of "GET /favicon.ico HTTP/1.1"
          if (readString.indexOf("?") <0)
          {
            //skip everything
          }
          else{
          //lets check if LED should be lighted          
            if ((readString.indexOf("L=3") <=0) && (readString.indexOf("L=2") <=0) && (readString.indexOf("L=1") <=0)){
              digitalWrite(pA, LOW);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = true;
            }
            if(readString.indexOf("L=1") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, HIGH);
              digitalWrite(pVD, HIGH);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = true;
              verd = false;
              azul = false;
              desl = false;
            }
            if(readString.indexOf("L=2") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, HIGH);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, HIGH);
              //analogWrite(0,255);
              verm = false;
              verd = true;
              azul = false;
              desl = false;
            }
            if(readString.indexOf("L=3") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, HIGH);
              digitalWrite(pK, HIGH);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = true;
              desl = false;
            }
          }
          // now output HTML data starting with standart header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h2>Controle do LED</h2>");
          //address will look like http://192.168.1.110/?L=1 when submited
          if (verm == false && azul == false && verd == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == true && azul == false && verd == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1 CHECKED>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == true && verd == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3 CHECKED>Azul");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == true){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2 CHECKED>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          //printing LED status
          client.print("<font size='5'>Estado do LED: ");
          if (verm == false && azul == false && verd == false)
              client.println("<font color='gray' size='5'>Desligado");
          if (verm == true && azul == false && verd == false)
              client.println("<font color='red' size='5'>Vermelho");
          if (verm == false && azul == true && verd == false)
              client.println("<font color='blue' size='5'>Azul");
          if (verm == false && azul == false && verd == true)
              client.println("<font color='green' size='5'>Verde");
          client.println("</body></html>");
          //clearing string for next read
          readString="";
          //stopping client
          client.stop();
        }
      }
    }
  }
}     






