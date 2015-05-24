#include <SPI.h>
#include <Client.h>
#include <Ethernet.h>
#include <Server.h>
#include <Udp.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9 }; //physical mac address
byte ip[] = { 192,168,1,118 };			// ip in lan
byte gateway[] = { 192, 168, 1, 1 };			// internet access via router
byte subnet[] = { 255, 255, 255, 0 };                   //subnet mask
EthernetServer server(8283);                                      //server port            
int ledPin = 11;  // LED pin
String readString = String(30); //string for fetching data from address
boolean LEDON = false; //LED status flag
void setup(){
//start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
//Set pin 4 to output
  pinMode(ledPin, OUTPUT);  
//enable serial datada print  
  //Serial.begin(9600);
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
          else
          //lets check if LED should be lighted
        if(readString.indexOf("L=1") >0)//replaces if(readString.contains("L=1"))
           {
             //led has to be turned ON
             digitalWrite(ledPin, HIGH);    // set the LED on
             LEDON = true;
           }else{
             //led has to be turned OFF
             digitalWrite(ledPin, LOW);    // set the LED OFF
             LEDON = false;             
           }
          // now output HTML data starting with standart header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<h1>LED control</h1>");
          //address will look like http://192.168.1.110/?L=1 when submited
          if (LEDON)
          client.println("<form method=get name=LED><input type=checkbox name=L value=1 CHECKED>LED<br><input type=submit value=submit></form>");
          else
          client.println("<form method=get name=LED><input type=checkbox name=L value=1>LED<br><input type=submit value=submit></form>");      
          client.println("<br />");
          //printing LED status
          client.print("<font size='5'>LED status: ");
          if (LEDON)
              client.println("<font color='green' size='5'>ON"); 
          else
              client.println("<font color='grey' size='5'>OFF");
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






