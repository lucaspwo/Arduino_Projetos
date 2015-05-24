#include <Wire.h>
#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9 };
byte ip[] = { 192,168,1,118 };
byte gateway[] = { 192, 168, 1, 1 };
byte subnet[] = { 255, 255, 255, 0 };
EthernetServer server(8283);

void i2c(int);

String readString = String(30);

boolean cmd1 = false;
boolean cmd2 = false;
boolean cmd3 = false;
//boolean cmd_a = false;

void setup()
{
  Ethernet.begin(mac, ip, gateway, subnet);
  Wire.begin();
}

byte x = 0;

void loop()
{
  
  
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
        //Serial.print(c);
        //if HTTP request has ended
        if (c == '\n') {
          //dirty skip of "GET /favicon.ico HTTP/1.1"
          if (readString.indexOf("?") <0)
          {
            //skip everything
          }
          else
          //lets check if LED should be lighted
        if(readString.indexOf("L=1") >0)//replaces if(readString.contains("L=1"))
        {
          //led has to be turned ON
          //digitalWrite(ledPin, HIGH);    // set the LED on
          //LEDON = true;
          i2c(1);
          cmd1 = true;
          cmd2 = false;
          cmd3 = false;             
         }
        if(readString.indexOf("L=2") >0)//replaces if(readString.contains("L=1"))
        {
          //led has to be turned ON
          //digitalWrite(ledPin, HIGH);    // set the LED on
          //LEDON = true;
          i2c(2);
          cmd2 = true;
          cmd1 = false;
          cmd3 = false;             
         }
        if(readString.indexOf("L=3") >0)//replaces if(readString.contains("L=1"))
        {
          //led has to be turned ON
          //digitalWrite(ledPin, HIGH);    // set the LED on
          //LEDON = true;
          i2c(3);
          cmd3 = true;
          cmd2 = false;
          cmd1 = false;            
         } 
        /*if(readString.indexOf("L=0") >0)//replaces if(readString.contains("L=1"))
        {
          //led has to be turned ON
          //digitalWrite(ledPin, HIGH);    // set the LED on
          //LEDON = true;
          i2c(2);
          cmd_a = true;
         }else{
           //led has to be turned OFF
           //digitalWrite(ledPin, LOW);    // set the LED OFF
           cmd_a = false;             
         }*/
         // now output HTML data starting with standart header
         client.println("HTTP/1.1 200 OK");
         client.println("Content-Type: text/html");
         client.println();
         client.println("<h1>Lista de comandos</h1>");
         //address will look like http://192.168.1.110/?L=1 when submited
         if (cmd1 == true && cmd2 == false && cmd3 == false){
           client.println("<form method=get name=LED><input type=radio name=L value=1 CHECKED>Comando 1");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=2>Comando 2");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=3>Comando 3<br><input type=submit value=Enviar></form>");
           client.println("<br />");
         }
         if (cmd1 == false && cmd2 == true && cmd3 == false){
           client.println("<form method=get name=LED><input type=radio name=L value=1>Comando 1");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=2 CHECKED>Comando 2");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=3>Comando 3<br><input type=submit value=Enviar></form>");
           client.println("<br />");
         }
         if (cmd1 == false && cmd2 == false && cmd3 == true){
           client.println("<form method=get name=LED><input type=radio name=L value=1>Comando 1");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=2>Comando 2");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=3 CHECKED>Comando 3<br><input type=submit value=Enviar></form>");
           client.println("<br />");
         }
         if (cmd1 == false && cmd2 == false && cmd3 == false){
           client.println("<form method=get name=LED><input type=radio name=L value=1>Comando 1");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=2>Comando 2");
           client.println("<br />");
           client.println("<form method=get name=LED><input type=radio name=L value=3>Comando 3<br><input type=submit value=Enviar></form>");
           client.println("<br />");
         }
         //printing LED status
         client.print("<font size='5'>Estado do servo: ");
         if (cmd1 == true && cmd2 == false && cmd3 == false)
           client.println("<font size='5'>180 graus"); 
         if (cmd1 == false && cmd2 == true && cmd3 == false)
           client.println("<font size='5'>0 graus");
         if (cmd1 == false && cmd2 == false && cmd3 == true)
           client.println("<font size='5'>90 graus");
         if (cmd1 == false && cmd2 == false && cmd3 == false)
           client.println("<font size='5'>- graus");
         client.println("</body></html>");
         //clearing string for next read
         readString="";
         //stopping client
         client.stop();
        }
      }
    }
  }
  
  
  /*if(digitalRead(ctr) == false)
  {
    i2c(2);
  }
  if(digitalRead(up) == false)
  {
    i2c(1);
  }*/
  
}

void i2c(int num)
{
  /*if(num == 1)
  {
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write("x is ");        // sends five bytes
    Wire.write(x);              // sends one byte  
    Wire.endTransmission();    // stop transmitting
  
    x++;
    delay(500);
  }
  if(num == 2)
  {
    Wire.beginTransmission(4);
    Wire.write("x is ");
    Wire.write(5);
    Wire.endTransmission();
  }*/
  
  if(num == 1)
  {
    x = 5;
    Wire.beginTransmission(4);
    Wire.write(x);
    Wire.endTransmission();
    
    delay(150);
  }
  if(num == 2)
  {
    x = 10;
    Wire.beginTransmission(4);
    Wire.write(x);
    Wire.endTransmission();

    delay(150);
  }
  if(num == 3)
  {
    x = 15;
    Wire.beginTransmission(4);
    Wire.write(x);
    Wire.endTransmission();
    
    delay(150);
  }
}
