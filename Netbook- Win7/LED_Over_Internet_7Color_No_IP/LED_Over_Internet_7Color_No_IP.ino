#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC9, 0xB9 };
char link[] = "http://dl.dropbox.com/u/10730972/Capturas_Autom%C3%A1ticas/My%20Pic.jpg";
EthernetServer server(80);                                      //server port
EthernetClient client();
int pA = 8;//48;  // LED pin
int pAZ = 7;//47;
int pVD = 6;//46;
int pK = 9;//49;
String readString = String(30); //string for fetching data from address
boolean verm = false;
boolean verd = false;
boolean azul = false;
boolean desl = false;
boolean amal = false;
boolean rosa = false;
boolean bran = false;
boolean ciano = false;
void setup(){
  //Serial.begin(9600);
  Ethernet.begin(mac);
  if(Ethernet.begin(mac) == 0) { // start ethernet using mac & DHCP
    Serial.println("Failed to configure Ethernet using DHCP");
    while(true)  // no point in carrying on, so stay in endless loop:
      ;
  }
  pinMode(pA, OUTPUT);
  pinMode(pAZ, OUTPUT);
  pinMode(pVD, OUTPUT);
  pinMode(pK, OUTPUT);
  delay(1000);
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
            if ((readString.indexOf("L=3") <=0) && (readString.indexOf("L=2") <=0) && (readString.indexOf("L=1") <=0) && (readString.indexOf("L=4") <=0) && (readString.indexOf("L=5") <=0) && (readString.indexOf("L=6") <=0) && (readString.indexOf("L=7") <=0)){
              digitalWrite(pA, LOW);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = true;
              ciano = false;
              bran = false;
              amal = false;
              rosa = false;
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
              ciano = false;
              bran = false;
              amal = false;
              rosa = false;
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
              ciano = false;
              bran = false;
              amal = false;
              rosa = false;
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
              ciano = false;
              bran = false;
              amal = false;
              rosa = false;
            }
            if(readString.indexOf("L=4") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, HIGH);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = false;
              ciano = false;
              bran = false;
              amal = true;
              rosa = false;
            }
            if(readString.indexOf("L=5") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, HIGH);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = false;
              ciano = true;
              bran = false;
              amal = false;
              rosa = false;
            }
            if(readString.indexOf("L=6") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, HIGH);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = false;
              ciano = false;
              bran = false;
              amal = false;
              rosa = true;
            }
            if(readString.indexOf("L=7") >0)//replaces if(readString.contains("L=1"))
            {
              //led has to be turned ON
              digitalWrite(pA, HIGH);    // set the LED on
              digitalWrite(pAZ, LOW);
              digitalWrite(pVD, LOW);
              digitalWrite(pK, LOW);
              //analogWrite(0,255);
              verm = false;
              verd = false;
              azul = false;
              desl = false;
              ciano = false;
              bran = true;
              amal = false;
              rosa = false;
            }
          }
          // now output HTML data starting with standart header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<table border=0><tr><td>");
          client.println("<h2>Controle do LED</h2>");
          //address will look like http://192.168.1.110/?L=1 when submited
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == true && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1 CHECKED>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == true && verd == false && amal == false && ciano == false && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3 CHECKED>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == true && amal == false && ciano == false && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2 CHECKED>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == false && amal == true && ciano == false && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4 CHECKED>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == false && amal == false && ciano == true && rosa ==false && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5 CHECKED>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==true && bran == false){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6 CHECKED>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == true){
            client.println("<form method=get name=Vermelho><input type=radio name=L value=1>Vermelho");
            client.println("<br />");
            client.println("<form method=get name=Verde><input type=radio name=L value=2>Verde");
            client.println("<br />");
            client.println("<form method=get name=Azul><input type=radio name=L value=3>Azul");
            client.println("<br />");
            client.println("<form method=get name=Amarelo><input type=radio name=L value=4>Amarelo");
            client.println("<br />");
            client.println("<form method=get name=Ciano><input type=radio name=L value=5>Ciano");
            client.println("<br />");
            client.println("<form method=get name=Magenta><input type=radio name=L value=6>Magenta");
            client.println("<br />");
            client.println("<form method=get name=Branco><input type=radio name=L value=7 CHECKED>Branco");
            client.println("<br />");
            client.println("<form method=get name=Apagar><input type=radio name=L value=0>Desligar LED?<br><input type=submit value=submit></form>");
            client.println("<br />");
          }
          //printing LED status
          client.print("<font size='5'>Estado do LED: ");
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == false)
              client.println("<font color='gray' size='5'>Desligado");
          if (verm == true && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == false)
              client.println("<font color='red' size='5'>Vermelho");
          if (verm == false && azul == true && verd == false && amal == false && ciano == false && rosa ==false && bran == false)
              client.println("<font color='blue' size='5'>Azul");
          if (verm == false && azul == false && verd == true && amal == false && ciano == false && rosa ==false && bran == false)
              client.println("<font color='green' size='5'>Verde");
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==false && bran == true)
              client.println("<font color='black' size='5'>Branco");
          if (verm == false && azul == false && verd == false && amal == false && ciano == false && rosa ==true && bran == false)
              client.println("<font color='magenta' size='5'>Magenta");
          if (verm == false && azul == false && verd == false && amal == false && ciano == true && rosa ==false && bran == false)
              client.println("<font color='cyan' size='5'>Ciano");
          if (verm == false && azul == false && verd == false && amal == true && ciano == false && rosa ==false && bran == false)
              client.println("<font color='yellow' size='5'>Amarelo");
          client.println("</td><td>");
          client.print("<img src=");
          client.print(link);
          client.print(" width=45% hight=45%/>");
          client.println("</td></tr></table>");
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
